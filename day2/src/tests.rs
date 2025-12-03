use crate::solution;
use googletest::prelude::*;

const EXAMPLE_INPUT: &str = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,\
    1698522-1698528,446443-446449,38593856-38593862,565653-565659,\
    824824821-824824827,2121212118-2121212124";

#[gtest]
fn test_day1problem1example() -> Result<()> {
    let solution: u64 = solution::find_sum_invalid_product_ids(EXAMPLE_INPUT);
    verify_that!(solution, eq(1227775554))
}

#[gtest]
fn test_day2problem2example() -> Result<()> {
    let solution: u64 = solution::find_sum_invalid_product_ids_v2(EXAMPLE_INPUT);
    verify_that!(solution, eq(4174379265))
}
