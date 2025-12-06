#include "solution.h"

#include <algorithm>
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

    uint64_t findMaxJoltage(const std::vector<uint32_t>& batteryBank, uint16_t noBatsToActivate)
    {
      size_t startPos{0u};

      std::vector<uint16_t> chosenDigits;
      chosenDigits.reserve(noBatsToActivate);

      for (size_t remaining = noBatsToActivate; remaining > 0; remaining -= 1)
      {
        auto endPos = batteryBank.size() - remaining + 1;
        auto remainingBats = batteryBank | std::views::enumerate | std::views::drop(startPos) |
                             std::views::take(endPos - startPos);

        auto maxValue = [](const auto& lhs, const auto& rhs)
        {
          auto& [index1, value1] = lhs;
          auto& [index2, value2] = rhs;
          return value1 < value2;
        };

        auto result = std::ranges::max_element(remainingBats, maxValue);
        const auto& [idx, value] = *result;

        startPos = idx + 1;
        chosenDigits.push_back(value);
      }
      auto result =
          std::ranges::fold_left(chosenDigits, uint64_t{0}, [](auto accumulator, auto current)
                                 { return accumulator * 10 + current; });

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
