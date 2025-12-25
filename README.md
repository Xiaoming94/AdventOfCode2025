Advent Of Code 2025 - Ming
=========
Repository for my Advent of Code 2025 solutions.

For this year, I'm attempting the same challenge as last year: solve the puzzle using a different language per day.
However, what I found cumbersome last year was that since I included so many languages, it became cumbersome to learn and relearn how to setup a new project and build system for them.
And also setup a system to write tests.

So for this year I'm just using the following languages and buildsystem:
- C++ (Meson with Ninja and Clang, testing using GoogleTest),
- Rust (Cargo with GoogleTest for testing),
- Java (Gradle with JUnit5 for testing),
- Python with python unittest (is there something like a makefile for python?)

## General structure of this repo
Each day have it's own project or build system files locally to them.
To run the tests, you can just go to those directories and run the testing command.

The `utils/` directory contains stuff like library code.

Each `dayN/` directory also includes a small readme detailing my thought process when solving the problem if any.

## Calendar day solution table

| Day | Language |
|------|---------|
| 1   | rust |
| 2 | rust |
| 3 | c++ |
| 4 | java |
| 5 | python |
| 6 | rust |
