#include "solution.h"

#include <algorithm>
#include <cstdint>
#include <ranges>
#include <vector>

namespace solution
{

std::vector<uint32_t> toIntegers(std::span<const char> batterBank)
{
  return batterBank |
         std::views::transform([](const char val) { return static_cast<uint32_t>(val - '0'); }) |
         std::ranges::to<std::vector>();
}

uint32_t findMaxJoltage(const std::vector<uint32_t>& batteryBank)
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

uint32_t findTotalMaxJoltage(std::string_view batteryBanks)
{
  return std::ranges::fold_left(std::views::split(batteryBanks, '\n') |
                                    std::views::transform(toIntegers) |
                                    std::views::transform(findMaxJoltage),
                                0, std::plus{});
}
}  // namespace solution
