pub mod solution;
use aoclibs::aoc_main;

aoc_main!(
    solution::find_sum_invalid_product_ids,
    solution::find_sum_invalid_product_ids_v2
);

#[cfg(test)]
mod tests;
