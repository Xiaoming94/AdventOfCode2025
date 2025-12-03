mod inputreader;

pub fn unimplemented_solution(_input: &str) -> &str {
    "not implemented yet"
}

pub fn read_input() -> String {
    inputreader::read_input()
}

#[macro_export]
macro_rules! aoc_main {
    ($solution_fn: expr) => {
        aoc_main!($solution_fn, aoclibs::unimplemented_solution);
    };
    ($solution1_fn: expr, $solution2_fn: expr) => {
        fn main() {
            let input = aoclibs::read_input();

            println!("Puzzle input: {input}");

            println!("problem1 solution: {}", $solution1_fn(input.as_str()));

            println!("problem2 solution: {}", $solution2_fn(input.as_str()));
        }
    };
}
