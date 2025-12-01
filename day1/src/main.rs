pub mod solution;
use std::io::{self, BufRead};

fn read_input() -> String {
    let stdin = io::stdin();
    stdin
        .lock()
        .lines()
        .fold("".to_string(), move |input, line| {
            input + line.unwrap().as_str() + "\n"
        })
}

fn main() {
    let input = read_input();
    println!("Puzzle input: {input}");
    println!(
        "problem1 solution: {}",
        solution::solve_puzzle(input.as_str())
    );
}

#[cfg(test)]
mod tests;
