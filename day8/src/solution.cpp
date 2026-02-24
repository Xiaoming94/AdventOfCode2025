#include "solution.h"

#include <cassert>
#include <charconv>
#include <cmath>
#include <optional>
#include <queue>
#include <ranges>
#include <vector>

namespace {
  constexpr auto err = 0.001f;
}

namespace solution {
  namespace internal {
    class Node {
     public:
      Node(std::uint32_t x, std::uint32_t y, std::uint32_t z)
        : m_x(x)
        , m_y(y)
        , m_z(z) {}

      static std::optional<Node> fromString(std::string_view nodeStr) {
        if (nodeStr.empty()) {
          return std::nullopt;
        }
        auto coordinates
            = std::views::split(nodeStr, ",")
              | std::views::transform([](auto&& range) {
                  std::string_view strView(&*range.begin(), std::ranges::distance(range));
                  std::uint32_t coord;
                  std::from_chars(strView.data(), strView.data() + strView.size(), coord);
                  return coord;
                })
              | std::ranges::to<std::vector<std::uint32_t>>();

        assert(coordinates.size() == 3 && "Invalid coordinate arg string");
        return Node(coordinates[0], coordinates[1], coordinates[2]);
      }

      std::uint32_t getX() const { return m_x; }

      std::uint32_t getY() const { return m_y; }

      std::uint32_t getZ() const { return m_z; }

      float calcDistanceTo(const Node& other) const {
        float dx = m_x - other.getX();
        float dy = m_y - other.getY();
        float dz = m_z - other.getZ();

        // Distance formula
        return std::sqrt(std::pow(dx, 2.0f) + std::pow(dy, 2.0f) + std::pow(dz, 2.0f));
      }

     private:
      std::uint32_t m_x;
      std::uint32_t m_y;
      std::uint32_t m_z;
    };

    struct Edge {
      Node node1;
      Node node2;
      float length;

      auto operator<=>(const Edge& other) const {
        // Check for equality using IEEE methodology
        if (std::abs(length - other.length) < err) {
          return std::partial_ordering::equivalent;
        }
        return length <=> other.length;
      }
    };

    using EdgeQueue_t = std::priority_queue<Edge>;
    EdgeQueue_t parseTextCreateEdgeQueue(std::string_view nodeList) {
      auto nodes = std::views::split(nodeList, "\n")
                   | std::views::transform([](auto&& range) {
                       return std::string_view(&*range.begin(), std::ranges::distance(range));
                     })
                   | std::views::transform(Node::fromString)
                   | std::views::filter([](auto node) { return node.has_value(); })
                   | std::views::transform([](auto node) { return node.value(); })
                   | std::ranges::to<std::vector<Node>>();
      EdgeQueue_t edges;
      for (size_t i{0u}; i < nodes.size(); i += 1) {
        for (size_t j{i + 1}; j < nodes.size(); j += 1) {
          Edge edge{.node1 = nodes[i],
                    .node2 = nodes[j],
                    .length = nodes[i].calcDistanceTo(nodes[j])};
          edges.push(edge);
        }
      }
      return edges;
    }

  }  // namespace internal
  std::uint32_t solveProblem1(std::string_view input, std::uint32_t nWires) {
    auto edges = internal::parseTextCreateEdgeQueue(input);
    return 0;
  }
}  // namespace solution
