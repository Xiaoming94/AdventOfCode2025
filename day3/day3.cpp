#define PROJECT_NAME "day3"

#include <iostream>
#include <print>
#include <string>

#include "solution.h"
int main()
{
  std::string input = "";
  for (std::string line; std::getline(std::cin, line);)
  {
    input += line + "\n";
  }
  if (input.back() == '\n')
  {
    input.pop_back();
  }
  std::println("Problem input is: \n{}", input);
  std::println("Problem 1 solution is: {}", solution::findTotalMaxJoltage(input));
  std::println("problem 2 solution is: {}", solution::findTotalMaxJoltageTwelveBats(input));
}
