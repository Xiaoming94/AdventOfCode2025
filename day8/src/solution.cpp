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
      using Ptr_sp = std::shared_ptr<Node>;
      using PtrVec_t = std::vector<Ptr_sp>;
      Node(std::uint32_t x, std::uint32_t y, std::uint32_t z)
        : m_x(x)
        , m_y(y)
        , m_z(z) {}

      static auto fromNodeData(std::vector<std::uint32_t>&& nodeData) -> Ptr_sp {
        return std::make_shared<Node>(nodeData[0], nodeData[1], nodeData[2]);
      }

      std::uint32_t getX() const { return m_x; }

      std::uint32_t getY() const { return m_y; }

      std::uint32_t getZ() const { return m_z; }

      auto calcDistanceTo(const Node& other) const {
        std::uint64_t dx = m_x - other.getX();
        std::uint64_t dy = m_y - other.getY();
        std::uint64_t dz = m_z - other.getZ();

        // Distance formula
        return (dx * dx) + (dy * dy) + (dz * dz);
      }

      void use() { m_used = true; }

      bool isUsed() const { return m_used; }

      auto operator<=>(const Node&) const = default;

     private:
      std::uint32_t m_x;
      std::uint32_t m_y;
      std::uint32_t m_z;
      bool m_used{false};
    };

    struct Edge {
      Node::Ptr_sp node1;
      Node::Ptr_sp node2;
      std::uint64_t length;

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
    EdgeQueue_t parseTextCreateEdgeQueue(std::string_view nodeList) {
      auto nodeData = cviews::split(nodeList, '\n')
                      | cviews::transform([](auto&& data) { return parseNodeData(data); })
                      | cviews::transform(Node::fromNodeData)
                      | cranges::to<Node::PtrVec_t>();

      EdgeQueue_t edges;
      for (size_t i : cviews::iota(0u, nodeData.size())) {
        for (size_t j : cviews::iota(i + 1, nodeData.size())) {
          edges.push(Edge{.node1 = nodeData.at(i),
                          .node2 = nodeData.at(j),
                          .length = nodeData[i]->calcDistanceTo(*nodeData[j])});
        }
      }

      return edges;
    }

  }  // namespace internal
  std::uint32_t solveProblem1(std::string_view input, std::uint32_t nWires) {
    std::println("input is:\n{}", input);
    auto edges = internal::parseTextCreateEdgeQueue(input);
    return 0;
  }
}  // namespace solution
