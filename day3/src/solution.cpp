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

    uint32_t findMaxJoltage(const std::vector<uint32_t>& batteryBank, uint16_t)
    {
      auto numberOfBatteries = batteryBank.size();
      uint32_t currentLargestJoltage = 0u;
      for (const auto& [index, batPower1] :
           std::views::zip(std::views::iota(size_t{1}, numberOfBatteries + 1u), batteryBank))
      {
        for (auto batPower2 : batteryBank | std::views::drop(index))
        {
          auto currentJoltage = batPower1 * 10u + batPower2;
          currentLargestJoltage = std::max(currentLargestJoltage, currentJoltage);
        }
      }

      return currentLargestJoltage;
    }

    template <typename N>
    auto findTotalMaxJoltage(std::string_view batteryBanks, uint16_t numberOfBatteries)
    {
      static_assert(std::is_integral_v<N>);
      auto findMaxJoltageLocal = [numberOfBatteries](const auto& line)
      { return findMaxJoltage(line, numberOfBatteries); };
      return static_cast<N>(std::ranges::fold_left(std::views::split(batteryBanks, '\n') |
                                                       std::views::transform(toIntegers) |
                                                       std::views::transform(findMaxJoltageLocal),
                                                   0, std::plus{}));
    }

  }  // namespace internal

  uint32_t findTotalMaxJoltage(std::string_view batteryBanks)
  {
    return internal::findTotalMaxJoltage<uint32_t>(batteryBanks, 2);
  }

  uint64_t findTotalMaxJoltageTwelveBats(std::string_view)
  {
    return 0;
  }

}  // namespace solution
