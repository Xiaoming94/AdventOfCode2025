#include <aoclibs.h>

#include <print>

namespace aoclibs {
  void runSolution(std::string_view input,
                   solutionFunction_t solveProblem1,
                   solutionFunction_t solveProblem2) {
    std::print("Input is:\n{}", input);

    std::print("Solution for problem 1: {}", solveProblem1(input));
    std::print("Solution for problem 2: {}", solveProblem2(input));
  }
}  // namespace aoclibs
