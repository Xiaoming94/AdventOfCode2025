#include <gtest/gtest.h>

#include "solution.h"

constexpr auto EXAMPLE_INPUT{
    "162,817,812\n"
    "57,618,57\n"
    "906,360,560\n"
    "592,479,940\n"
    "352,342,300\n"
    "466,668,158\n"
    "542,29,236\n"
    "431,825,988\n"
    "739,650,466\n"
    "52,470,668\n"
    "216,146,977\n"
    "819,987,18\n"
    "117,168,530\n"
    "805,96,715\n"
    "346,949,466\n"
    "970,615,88\n"
    "941,993,340\n"
    "862,61,35\n"
    "984,92,344\n"
    "425,690,689"};

TEST(Aoc2025day8Test, problem1Solution) {
  const auto result = solution::solveProblem1(EXAMPLE_INPUT, 10u);
  EXPECT_EQ(40u, result);
}

TEST(Aoc2025day8Test, problem2Solution) {
  const auto result = solution::solveProblem2(EXAMPLE_INPUT);
  EXPECT_EQ(25272u, result);
}

TEST(Problem1Test, findSimpleCircuit) {
  constexpr auto input{"4,2,5\n5,1,3"};
  EXPECT_EQ(2u, solution::solveProblem1(input, 1));
}

TEST(Problem1Test, findCircuitOfSize3) {
  constexpr auto input{"4,2,5\n5,1,3\n3,2,5"};
  EXPECT_EQ(3u, solution::solveProblem1(input, 2));
}

TEST(Problem1Test, findCircuitOfSize3With3Wires) {
  constexpr auto input{"4,2,5\n5,1,3\n3,2,5"};
  EXPECT_EQ(3u, solution::solveProblem1(input, 3));
}
