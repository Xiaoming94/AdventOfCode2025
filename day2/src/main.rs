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

pub mod solution;
fn main() {
    let input = read_input();
    println!("Puzzle input: {input}");
    println!(
        "problem1 solution: {}",
        solution::find_sum_invalid_product_ids(input.as_str())
    );
}

#[cfg(test)]
mod tests;
