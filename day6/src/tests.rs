use crate::solution;
use googletest::prelude::*;

const EXAMPLE_INPUT: &str = "123 328  51 64\n\
     45 64  387 23\n\
     6 98  215 314\n\
     *   +   *   +  ";

#[gtest]
fn test_problem1solution() -> Result<()> {
    let result = solution::solve_problem1(EXAMPLE_INPUT);
    verify_that!(result, eq(4277556))
}

#[gtest]
fn test_problem2solution() -> Result<()> {
    let result = solution::solve_problem2(EXAMPLE_INPUT);
    verify_that!(result, eq(3263827))
}
