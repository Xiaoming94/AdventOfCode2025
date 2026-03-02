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

    Edge::Vec_t createProblemDataFrom(std::string_view nodeList, std::uint32_t nWires) {
      auto nodeData = cviews::split(nodeList, '\n')
                      | cviews::transform([](auto&& data) { return parseNodeData(data); })
                      | cviews::transform(Node::fromNodeData)
                      | cranges::to<Node::PtrVec_t>();

      std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> edgesQueue;
      for (id_t i : cviews::iota(0u, nodeData.size())) {
        for (id_t j : cviews::iota(i + 1, nodeData.size())) {
          auto& node1 = nodeData.at(i);
          auto& node2 = nodeData.at(j);
          auto length = node1->calcDistanceTo(*node2);
          edgesQueue.push(Edge{.node1Id = i, .node2Id = j, .length = length});
        }
      }

      Edge::Vec_t edges;
      while (not edgesQueue.empty() && nWires > 0) {
        const auto& edge = edgesQueue.top();
        edges.emplace_back(edge);
        edgesQueue.pop();
        nWires -= 1;
      }

      return edges;
    }

    static std::uint32_t circuitIds{0};

    class Circuit {
     public:
      using Ptr_t = std::shared_ptr<Circuit>;
      Circuit()
        : m_id(circuitIds++) {}

      auto getId() const { return m_id; }

      auto getNodes() { return m_nodes; }

      void merge(Circuit& other) { m_nodes.merge(other.getNodes()); }

      auto add(id_t newNodeId) { return m_nodes.insert(newNodeId); }

      auto operator<=>(const Circuit& other) const { return m_id <=> other.getId(); }

     private:
      std::uint32_t m_id;
      std::unordered_set<id_t> m_nodes;
    };

  }  // namespace internal

  std::uint32_t solveProblem1(std::string_view input, std::uint32_t nWires) {
    auto edges = internal::createProblemDataFrom(input, nWires);
    using internal::Circuit;
    std::vector<Circuit::Ptr_t> circuits;
    std::unordered_map<id_t, Circuit::Ptr_t> idToCircuits;

    for (const auto& [node1Id, node2Id, _] : edges) {
      auto node1InCircuit = idToCircuits.contains(node1Id);
      auto node2InCircuit = idToCircuits.contains(node2Id);

      // Merging two circuits
      if (node1InCircuit and node2InCircuit) {
        auto circuit1 = idToCircuits[node1Id];
        auto circuit2 = idToCircuits[node2Id];
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

      } else if (node1InCircuit) {
        idToCircuits[node1Id]->add(node2Id);
        idToCircuits[node2Id] = idToCircuits[node1Id];
      } else if (node2InCircuit) {
        idToCircuits[node2Id]->add(node1Id);
        idToCircuits[node1Id] = idToCircuits[node2Id];
      } else {
        auto newCircuit = std::make_shared<Circuit>();
        newCircuit->add(node1Id);
        newCircuit->add(node2Id);
        idToCircuits[node1Id] = newCircuit;
        idToCircuits[node2Id] = newCircuit;
        circuits.emplace_back(newCircuit);
      }
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
