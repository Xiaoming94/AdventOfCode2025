#include <gtest/gtest.h>

#include "solution.h"

constexpr auto EXAMPLE_INPUT =
    "987654321111111\n"
    "811111111111119\n"
    "234234234234278\n"
    "818181911112111";

TEST(AdventOfCode2025, test_day3problem1)
{
  auto result = solution::findTotalMaxJoltage(EXAMPLE_INPUT);
  EXPECT_EQ(357, result);
}

TEST(AdventOfCode2025, test_day3problem2)
{
  auto result = solution::findTotalMaxJoltageTwelveBats(EXAMPLE_INPUT);
  EXPECT_EQ(3121910778619u, result);
}
