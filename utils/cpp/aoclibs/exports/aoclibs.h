#pragma once

#ifdef BUILDING_AOCLIBS
#define AOCLIBS_PUBLIC __attribute__((visibility("default")))
#else
#define AOCLIBS_PUBLIC
#endif

#include <functional>
#include <iostream>
#include <string>
#include <string_view>

namespace aoclibs {
  using str_t = std::string;

  /**
   * @brief Function for reading the input from a stream.
   *
   * @par This function is meant to be used for reading the input from std::cin,
   * but changed to accept anytype specified by stream_t.
   *
   * @param source the stream from which the input is read from.
   * In most cases, this chould be system in (i.e. std::cin)
   *
   * @return a string with the content from the stream of multiple lines
   */
  template <typename stream_t>
  str_t readInput(stream_t&& source = std::cin) {
    str_t input{""};
    for (str_t line; std::getline(source, line);) {
      input += line + "\n";
    }

    // Remove trailing newline
    if (input.back() == '\n') {
      input.pop_back();
    }
    return input;
  }

  using solutionFunction_t = std::function<str_t(std::string_view)>;
  str_t unimplemented(std::string_view) {
    return "unimplemented";
  }

  /**
   * @brief Function that is meant to run and display the solutions.
   *
   * Prints the solution in the form of
   *  - "Solution for problem 1 : ---"
   *  - "Solution for problem 2 : ---"
   */
  AOCLIBS_PUBLIC void runSolution(std::string_view input,
                                  solutionFunction_t solveProblem1,
                                  solutionFunction_t solveProblem2 = &unimplemented);

}  // namespace aoclibs
