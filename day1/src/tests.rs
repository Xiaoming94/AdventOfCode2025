use super::solution;

use googletest::prelude::*;

const EXAMPLE_INPUT: &str = "L68\n\
    L30\n\
    R48\n\
    L5\n\
    R60\n\
    L55\n\
    L1\n\
    L99\n\
    R14\n\
    L82";
#[test]
fn day1problem1_test() -> Result<()> {
    let result = solution::solve_puzzle(EXAMPLE_INPUT);
    verify_that!(result, eq(3))
}
