#include "solution.h"

#include <algorithm>
#include <cassert>
#include <memory>
#include <print>
#include <queue>
#include <ranges>
#include <vector>

namespace solution {
  constexpr auto DIMENSIONS{3u};
  namespace cviews = std::views;
  namespace cranges = std::ranges;
  namespace internal {
    class Node {
     public:
      using Ptr_sp = std::unique_ptr<Node>;
      using PtrVec_t = std::vector<Ptr_sp>;
      Node(std::uint32_t x, std::uint32_t y, std::uint32_t z)
        : m_x(x)
        , m_y(y)
        , m_z(z) {}

      static auto fromNodeData(std::vector<std::uint32_t>&& nodeData) -> Ptr_sp {
        return std::make_unique<Node>(nodeData[0], nodeData[1], nodeData[2]);
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

      void use() { m_used = true; }

      bool isUsed() const { return m_used; }

      auto operator<=>(const Node&) const = default;

     private:
      std::int32_t m_x;
      std::int32_t m_y;
      std::int32_t m_z;
      bool m_used{false};
    };

    struct Edge {
      std::uint32_t node1Id;
      std::uint32_t node2Id;
      std::int64_t length;

      auto operator<=>(const Edge& other) const { return length <=> other.length; }
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

    using EdgeQueue_t = std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>;

    struct ProblemData {
      Node::PtrVec_t nodes;
      EdgeQueue_t edges;
    };

    ProblemData createProblemDataFrom(std::string_view nodeList) {
      auto nodeData = cviews::split(nodeList, '\n')
                      | cviews::transform([](auto&& data) { return parseNodeData(data); })
                      | cviews::transform(Node::fromNodeData)
                      | cranges::to<Node::PtrVec_t>();

      EdgeQueue_t edges;
      for (size_t i : cviews::iota(0u, nodeData.size())) {
        for (size_t j : cviews::iota(i + 1, nodeData.size())) {
          auto& node1 = nodeData[i];
          auto& node2 = nodeData[j];
          auto length = node1->calcDistanceTo(*node2);
          edges.push(Edge{.node1Id = static_cast<uint32_t>(i),
                          .node1Id = static_cast<uint32_t>(j),
                          .length = length});
        }
      }

      return ProblemData{.nodes = std::move(nodeData), .edges = std::move(edges)};
    }

  }  // namespace internal

  std::uint32_t solveProblem1(std::string_view input, std::uint32_t nWires) {
    std::println("input is:\n{}", input);
    auto problemData = internal::createProblemDataFrom(input);
    return 0;
  }
}  // namespace solution
