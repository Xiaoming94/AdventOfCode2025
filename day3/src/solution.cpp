#include "solution.h"

#include <algorithm>
#include <print>
#include <ranges>
#include <type_traits>
#include <vector>

namespace solution
{

  namespace internal
  {
    std::vector<uint32_t> toIntegers(std::span<const char> batterBank)
    {
      return batterBank |
             std::views::transform([](const char val)
                                   { return static_cast<uint32_t>(val - '0'); }) |
             std::ranges::to<std::vector>();
    }

    uint32_t findMaxJoltage(const std::vector<uint32_t>& batteryBank, uint16_t noBatsToActivate)
    {
      size_t largestPos{0u};

      std::vector<uint16_t> chosenDigits;
      chosenDigits.reserve(noBatsToActivate);

      for (auto remaining : std::views::iota(size_t{0}, noBatsToActivate) | std::views::reverse)
      {
        std::println("remaining to find: {}", remaining);
        auto remainingBats = batteryBank | std::views::enumerate | std::views::drop(largestPos) |
                             std::views::reverse | std::views::drop(remaining) |
                             std::views::reverse;
        auto maxValue = [](auto lhs, auto rhs) { return std::get<1>(lhs) < std::get<1>(rhs); };
        auto result = std::ranges::max_element(remainingBats, maxValue);
        const auto& [idx, value] = *result;
        largestPos = idx + 1;
        chosenDigits.emplace_back(value);
      }
      auto result =
          std::ranges::fold_left(chosenDigits, uint32_t{0}, [](auto accumulator, auto current)
                                 { return accumulator * 10 + current; });

      std::println("Found result: {}", result);
      return result;
    }

    template <typename N>
    auto findTotalMaxJoltage(std::string_view batteryBanks, uint16_t noBatsToActivate)
    {
      static_assert(std::is_integral_v<N>);
      auto findMaxJoltageLocal = [noBatsToActivate](const auto& line)
      { return findMaxJoltage(line, noBatsToActivate); };
      return static_cast<N>(std::ranges::fold_left(std::views::split(batteryBanks, '\n') |
                                                       std::views::transform(toIntegers) |
                                                       std::views::transform(findMaxJoltageLocal),
                                                   static_cast<N>(0), std::plus{}));
    }

  }  // namespace internal

  uint32_t findTotalMaxJoltage(std::string_view batteryBanks)
  {
    return internal::findTotalMaxJoltage<uint32_t>(batteryBanks, 2);
  }

  uint64_t findTotalMaxJoltageTwelveBats(std::string_view batteryBanks)
  {
    return internal::findTotalMaxJoltage<uint64_t>(batteryBanks, 12);
  }

}  // namespace solution
