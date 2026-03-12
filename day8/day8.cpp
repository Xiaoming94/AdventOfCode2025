#define PROJECT_NAME "day8"

#include <aoclibs.h>

#include "solution.h"

int main() {
  constexpr auto nWires{1000};
  auto solution1Function = [](std::string_view input) {
    return solution::solveProblem1(input, nWires);
  };
  aoclibs::aocMain(solution1Function, &solution::solveProblem2);
}
