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

fn parse_to_vectors(input: &str) -> Vec<Vec<&str>> {
    input
        .lines()
        .map(|line| line.split_whitespace().collect::<Vec<_>>())
        .collect()
}

pub(crate) fn solve_problem1(input: &str) -> u64 {
    let problem_as_vectors = parse_to_vectors(input);
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
    let problem_as_vectors = parse_to_vectors(input);
    let operators = problem_as_vectors.last().unwrap();
    let number_of_operands = problem_as_vectors.len() - 1;

    0
    //operators
    //    .into_iter()
    //    .enumerate()
    //    .map(|(i, op)| {
    //        let operands_str: Vec<&str> = problem_as_vectors[0..number_of_operands]
    //            .iter()
    //            .map(|line| line[i])
    //            .collect();
    //        let operands: Vec<&str> = read_cnstyle_operands(operands_str)
    //            .iter()
    //            .map(|operand| operand.as_str())
    //            .collect();
    //        parse_problem(op, operands)
    //    })
    //    .map(|problem| problem.evaluate())
    //    .sum()
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
