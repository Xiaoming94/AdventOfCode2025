#pragma once

#ifdef BUILDING_AOCLIBS
#define AOCLIBS_PUBLIC __attribute__((visibility("default")))
#else
#define AOCLIBS_PUBLIC
#endif

#include <functional>
#include <string>
#include <string_view>

namespace aoclibs {
  using str_t = std::string;

  template <typename stream_t>
  str_t readInput(stream_t&& source) {
    return "";
  }

  using solutionFunction_t = std::function<str_t(std::string_view)>;
  str_t unimplemented(std::string_view) {
    return "unimplemented";
  }

  AOCLIBS_PUBLIC void runSolution(std::string_view input,
                                  solutionFunction_t solveProblem1,
                                  solutionFunction_t solveProblem2 = &unimplemented);
}  // namespace aoclibs
