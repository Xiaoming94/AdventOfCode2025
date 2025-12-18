use std::fmt::Debug;
use std::ops::{Add, Mul};

trait MathProblem {
    fn create_problem(operands: Vec<u64>) -> Self
    where
        Self: Sized;
    fn evaluate(&self) -> u64;
}

type MathProblemPtr = Box<dyn MathProblem>;

#[derive(Debug)]
struct AddProblem {
    operands: Vec<u64>,
    identity: u64,
}

impl MathProblem for AddProblem {
    fn create_problem(operands: Vec<u64>) -> Self {
        AddProblem {
            operands: operands,
            identity: 0,
        }
    }

    fn evaluate(&self) -> u64 {
        self.operands.iter().fold(self.identity, Add::add)
    }
}

struct MulProblem {
    operands: Vec<u64>,
    identity: u64,
}

impl MathProblem for MulProblem {
    fn create_problem(operands: Vec<u64>) -> Self {
        MulProblem {
            operands: operands,
            identity: 1,
        }
    }

    fn evaluate(&self) -> u64 {
        self.operands.iter().fold(self.identity, Mul::mul)
    }
}

fn parse_problem(op: &str, operands: Vec<u64>) -> MathProblemPtr {
    match op {
        "+" => Box::new(AddProblem::create_problem(operands)),
        "*" => Box::new(MulProblem::create_problem(operands)),
        _ => panic!("Invalid operator"),
    }
}

fn read_operands(input: &str, lines_to_read: usize) -> Vec<Vec<u64>> {
    let mut operands_per_problem: Vec<Vec<u64>> = Vec::new();
    let char_matrix = input
        .lines()
        .map(|line| line.chars().collect::<Vec<char>>())
        .collect::<Vec<Vec<char>>>();

    let n_columns: usize = char_matrix.first().unwrap().len();

    if char_matrix.iter().any(|line| line.len() != n_columns) {
        panic!("Bad Input format");
    }

    const RADIX: u32 = 10;
    let mut operands: Vec<u64> = Vec::new();
    for col in (0..n_columns).rev() {
        let column: Vec<char> = (0..lines_to_read)
            .map(|row_i| char_matrix[row_i][col])
            .collect();

        if column.iter().all(|c| *c == ' ') {
            operands_per_problem.push(operands.clone());
            operands.clear();
        } else {
            let operand = column
                .into_iter()
                .filter(|c| *c != ' ')
                .map(|c| c.to_digit(RADIX).map(u64::from).unwrap())
                .fold(0, |acc, dig| acc * 10 + dig);
            operands.push(operand);
        }
    }
    operands_per_problem.push(operands);

    operands_per_problem.into_iter().rev().collect()
}

pub(crate) fn solve_problem1(input: &str) -> u64 {
    let problem_as_vectors: Vec<Vec<&str>> = input
        .lines()
        .map(|line| line.split_whitespace().collect())
        .collect();

    let operators = problem_as_vectors.last().unwrap();
    let number_of_operands = problem_as_vectors.len() - 1;

    operators
        .into_iter()
        .enumerate()
        .map(|(i, op)| {
            let operands: Vec<u64> = problem_as_vectors[0..number_of_operands]
                .iter()
                .map(|line| line[i].parse::<u64>().unwrap())
                .collect();
            parse_problem(op, operands)
        })
        .map(|problem| problem.evaluate())
        .sum()
}

pub(crate) fn solve_problem2(input: &str) -> u64 {
    let operators: Vec<&str> = input
        .lines()
        .next_back()
        .unwrap_or_else(|| panic!("Invalid input"))
        .split_whitespace()
        .collect();

    let lines_to_read = input.lines().count() - 1;
    let operands: Vec<Vec<u64>> = read_operands(input, lines_to_read);

    std::iter::zip(operators, operands)
        .map(|(op, operand)| parse_problem(op, operand))
        .map(|problem| problem.evaluate())
        .sum()
}

#[cfg(test)]
mod unittests {

    use googletest::prelude::*;

    use super::*;

    #[gtest]
    fn test_parse_add_problem() -> Result<()> {
        let operands: Vec<u64> = vec![5, 4, 2];
        let operator = "+";
        let problem = parse_problem(operator, operands);
        verify_that!(problem.evaluate(), eq(11))
    }

    #[gtest]
    fn test_parse_mul_problem() -> Result<()> {
        let operands: Vec<u64> = vec![5, 4, 2];
        let operator = "*";
        let problem = parse_problem(operator, operands);
        verify_that!(problem.evaluate(), eq(40))
    }
}
