#include "solution.h"

#include <algorithm>
#include <cassert>
#include <functional>
#include <limits>
#include <memory>
#include <queue>
#include <ranges>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace solution {
  constexpr auto DIMENSIONS{3u};
  namespace cviews = std::views;
  namespace cranges = std::ranges;

  using id_t = size_t;

  namespace internal {
    class Node {
     public:
      using Ptr_up = std::unique_ptr<Node>;
      using PtrVec_t = std::vector<Ptr_up>;
      Node(std::uint32_t x, std::uint32_t y, std::uint32_t z)
        : m_x(x)
        , m_y(y)
        , m_z(z) {}

      static auto fromNodeData(std::vector<std::uint32_t>&& nodeData) -> Ptr_up {
        return std::make_unique<Node>(nodeData.at(0), nodeData.at(1), nodeData.at(2));
      }

      std::int32_t getX() const { return m_x; }

      std::int32_t getY() const { return m_y; }

      std::int32_t getZ() const { return m_z; }

      auto calcDistanceTo(const Node& other) const {
        std::int64_t dx = m_x - other.getX();
        std::int64_t dy = m_y - other.getY();
        std::int64_t dz = m_z - other.getZ();

        // Distance formula
        return (dx * dx) + (dy * dy) + (dz * dz);
      }

      auto operator<=>(const Node&) const = default;

     private:
      std::int32_t m_x;
      std::int32_t m_y;
      std::int32_t m_z;
    };

    struct Edge {
      id_t node1Id;
      id_t node2Id;
      std::int64_t length;

      auto operator<=>(const Edge& other) const { return length <=> other.length; }
      using Vec_t = std::vector<Edge>;
    };

    class Circuit {
     public:
      using Ptr_t = std::shared_ptr<Circuit>;
      using Vec_t = std::vector<Ptr_t>;
      Circuit(id_t circuitId)
        : m_id(circuitId) {}

      auto getId() const { return m_id; }

      auto getNodes() { return m_nodes; }

      void merge(Circuit& other) { m_nodes.merge(other.getNodes()); }

      auto add(id_t newNodeId) { return m_nodes.insert(newNodeId); }

     private:
      id_t m_id;
      std::unordered_set<id_t> m_nodes;
    };

    std::vector<std::uint32_t> parseNodeData(auto&& data) {
      std::vector<std::uint32_t> nodeData;
      nodeData.reserve(DIMENSIONS);
      for (auto&& subdata : cviews::split(data, ',')) {
        nodeData.push_back(cranges::fold_left(subdata, 0u, [](std::uint32_t acc, auto&& c) {
          std::uint32_t val = c - '0';
          return acc * 10 + val;
        }));
      }
      if (!nodeData.empty()) {
        assert(nodeData.size() == DIMENSIONS && "Invalid Input format");
      }
      return nodeData;
    }

    class Graph {
     public:
      using EdgesQueue_t = std::priority_queue<Edge, std::vector<Edge>, std::greater<>>;
      static auto buildNodes(std::string_view nodeList) -> Node::PtrVec_t {
        return cviews::split(nodeList, '\n')
               | cviews::transform([](auto&& data) { return parseNodeData(data); })
               | cviews::transform(Node::fromNodeData)
               | cranges::to<Node::PtrVec_t>();
      }

      explicit Graph(std::string_view nodeList)
        : m_nodes(buildNodes(nodeList)) {}

      EdgesQueue_t createGraphEdges() {
        std::priority_queue<Edge, std::vector<Edge>, std::greater<>> edgesQueue;
        for (id_t i : cviews::iota(0u, m_nodes.size())) {
          for (id_t j : cviews::iota(i + 1, m_nodes.size())) {
            auto& node1 = m_nodes.at(i);
            auto& node2 = m_nodes.at(j);
            auto length = node1->calcDistanceTo(*node2);
            edgesQueue.push(Edge{.node1Id = i, .node2Id = j, .length = length});
          }
        }

        return edgesQueue;
      }

      Node& getNode(id_t id) const { return *m_nodes.at(id); }

      std::pair<Edge, Circuit::Vec_t> mergeCircuits(std::uint32_t nWires) {
        auto edges = createGraphEdges();
        auto [circuits, idToCircuits] = createCircuit();
        auto finalEdge = internal::Edge{.node1Id = 1u, .node2Id = 1u, .length = 0u};
        while (not edges.empty() && nWires > 0 && circuits.size() > 1u) {
          finalEdge = edges.top();
          auto circuit1 = idToCircuits.at(finalEdge.node1Id);
          auto circuit2 = idToCircuits.at(finalEdge.node2Id);

          if (circuit1 != circuit2) {
            for (id_t nodeId : circuit2->getNodes()) {
              idToCircuits[nodeId] = circuit1;
            }
            circuit1->merge(*circuit2);
            auto it = std::find_if(circuits.begin(), circuits.end(), [&circuit2](auto&& circuit) {
              return circuit->getId() == circuit2->getId();
            });
            if (it != circuits.end()) {
              circuits.erase(it);
            }
            circuit2.reset();
          }
          nWires -= 1;
          edges.pop();
        }

        return std::make_pair<>(finalEdge, circuits);
      }

     private:
      auto createCircuit()
          -> std::pair<std::vector<Circuit::Ptr_t>, std::unordered_map<id_t, Circuit::Ptr_t>> {
        auto circuits = cviews::iota(0u, m_nodes.size())
                        | cviews::transform([](auto&& id) {
                            auto circuit = std::make_shared<Circuit>(id);
                            circuit->add(id);
                            return circuit;
                          })
                        | cranges::to<std::vector<Circuit::Ptr_t>>();

        std::unordered_map<id_t, Circuit::Ptr_t> idToCircuits;
        for (auto&& [id, circuit] : circuits | cviews::enumerate) {
          idToCircuits[id] = circuit;
        }

        return std::make_pair<>(circuits, idToCircuits);
      }
      Node::PtrVec_t m_nodes;
    };

  }  // namespace internal

  std::uint32_t solveProblem1(std::string_view input, std::uint32_t nWires) {
    internal::Graph graph(input);
    auto edges = graph.createGraphEdges();
    auto circuits = graph.mergeCircuits(nWires).second;

    cranges::sort(circuits, [](const auto& circuit1, const auto& circuit2) {
      return circuit1->getNodes().size() > circuit2->getNodes().size();
    });

    return cranges::fold_left(circuits | cviews::take(3) | cviews::transform([](auto&& circuit) {
                                return circuit->getNodes().size();
                              }),
                              1,
                              std::multiplies{});
  }

  std::uint32_t solveProblem2(std::string_view input) {
    internal::Graph graph(input);
    auto edges = graph.createGraphEdges();
    auto finalEdge = graph.mergeCircuits(std::numeric_limits<uint32_t>{}.max()).first;

    auto& node1 = graph.getNode(finalEdge.node1Id);
    auto& node2 = graph.getNode(finalEdge.node2Id);

    return node1.getX() * node2.getX();
  }
}  // namespace solution
