use std::marker::PhantomData;

trait Operator {
    fn calculate(lhs: u64, rhs: u64) -> u64;
    fn identity() -> u64;
}

struct Add {}
struct Mul {}

impl Operator for Add {
    fn calculate(lhs: u64, rhs: u64) -> u64 {
        lhs + rhs
    }

    fn identity() -> u64 {
        0_u64
    }
}

impl Operator for Mul {
    fn calculate(lhs: u64, rhs: u64) -> u64 {
        lhs * rhs
    }

    fn identity() -> u64 {
        1_u64
    }
}

#[derive(Debug)]
struct MathProblem<T: Operator> {
    operands: Vec<u64>,
    operator: PhantomData<fn() -> T>,
}

impl<T: Operator> MathProblem<T> {
    fn new(operands_in: Vec<&str>) -> Self {
        MathProblem {
            operands: operands_in
                .iter()
                .map(|oper_str| {
                    oper_str
                        .parse::<u64>()
                        .unwrap_or_else(|err| panic!("Invalid input with error {:?}", err))
                })
                .collect(),
            operator: PhantomData,
        }
    }

    fn evaluate(self) -> u64 {
        self.operands
            .iter()
            .fold(T::identity(), |acc, oper| T::calculate(acc, *oper))
    }
}

pub(crate) fn solve_problem1(input: &str) -> u64 {
    let problem_as_vectors: Vec<Vec<_>> = input
        .lines()
        .map(|line| line.split_whitespace().collect::<Vec<_>>())
        .collect();

    let operators = problem_as_vectors.last().unwrap();
    let num_of_problems = operators.len();

    println!("Operators: {:?}", operators);
    0
}

#[cfg(test)]
mod solution_unittest {
    use std::marker::PhantomData;

    use super::{Add, MathProblem, Mul};
    use googletest::prelude::*;

    #[gtest]
    fn verify_parse_mathproblem() -> Result<()> {
        let input = vec!["42", "32", "1"];
        let math_problem = MathProblem::<Add>::new(input);
        verify_that!(math_problem.operands, eq(&vec![42_u64, 32_u64, 1_u64]))
    }

    #[gtest]
    fn verify_math_problem_evaluation() -> Result<()> {
        let math_problem = MathProblem::<Add> {
            operands: vec![1, 2, 3],
            operator: PhantomData,
        };

        verify_that!(math_problem.evaluate(), eq(6))
    }

    #[gtest]
    fn verify_mul_problem_evaluation() -> Result<()> {
        let math_problem = MathProblem::<Mul> {
            operands: vec![1, 2, 3],
            operator: PhantomData,
        };

        verify_that!(math_problem.evaluate(), eq(6))
    }
}
