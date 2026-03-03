#include "solution.h"

#include <algorithm>
#include <cassert>
#include <functional>
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

    template <typename comparator_t>
    class GraphBuilder {
     public:
      using EdgesQueue_t = std::priority_queue<Edge, std::vector<Edge>, comparator_t>;
      GraphBuilder() = default;

      /**
       * @brief creates a queue of edges sorted in order specified by comparator_t.
       *
       *
       */
      static std::pair<id_t, EdgesQueue_t> createGraphEdges(std::string_view nodeList) {
        auto nodeData = cviews::split(nodeList, '\n')
                        | cviews::transform([](auto&& data) { return parseNodeData(data); })
                        | cviews::transform(Node::fromNodeData)
                        | cranges::to<Node::PtrVec_t>();

        std::priority_queue<Edge, std::vector<Edge>, comparator_t> edgesQueue;
        for (id_t i : cviews::iota(0u, nodeData.size())) {
          for (id_t j : cviews::iota(i + 1, nodeData.size())) {
            auto& node1 = nodeData.at(i);
            auto& node2 = nodeData.at(j);
            auto length = node1->calcDistanceTo(*node2);
            edgesQueue.push(Edge{.node1Id = i, .node2Id = j, .length = length});
          }
        }

        return std::make_pair<>(nodeData.size(), edgesQueue);
      }
    };

    auto createCircuits(id_t numberOfNodes)
        -> std::pair<std::vector<Circuit::Ptr_t>, std::unordered_map<id_t, Circuit::Ptr_t>> {
      auto circuits = cviews::iota(0u, numberOfNodes)
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

  }  // namespace internal

  std::uint32_t solveProblem1(std::string_view input, std::uint32_t nWires) {
    auto [numberOfNodes, edges] = internal::GraphBuilder<std::greater<>>().createGraphEdges(input);
    auto [circuits, idToCircuits] = internal::createCircuits(numberOfNodes);

    while (not edges.empty() && nWires > 0) {
      auto& [id1, id2, _] = edges.top();
      auto circuit1 = idToCircuits[id1];
      auto circuit2 = idToCircuits[id2];

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

    cranges::sort(circuits, [](const auto& circuit1, const auto& circuit2) {
      return circuit1->getNodes().size() > circuit2->getNodes().size();
    });

    return cranges::fold_left(circuits | cviews::take(3) | cviews::transform([](auto&& circuit) {
                                return circuit->getNodes().size();
                              }),
                              1,
                              std::multiplies{});
  }

  std::uint32_t solveProblem2(std::string_view /*input*/) {
    return 0;
  }
}  // namespace solution
