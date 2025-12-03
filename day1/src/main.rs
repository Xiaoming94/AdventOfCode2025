pub mod solution;
use aoclibs::aoc_main;

aoc_main!(
    solution::solve_puzzle,
    solution::solve_puzzle_new_instructions
);

#[cfg(test)]
mod tests;
