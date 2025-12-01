use std::ops::Add;

const MAXIMUM: i32 = 100;

#[derive(Debug, Eq, PartialEq, Clone)]
enum Instruction {
    Left(i32),
    Right(i32),
}

impl From<&str> for Instruction {
    fn from(rhs: &str) -> Instruction {
        let (direction, steps_str) = rhs.split_at(1);
        let steps = steps_str.parse::<i32>().unwrap_or(0);
        match direction {
            "L" => Instruction::Left(steps),
            "R" => Instruction::Right(steps),
            _ => panic!("Invalid instruction"),
        }
    }
}

impl Add<i32> for Instruction {
    type Output = i32;

    fn add(self, other: i32) -> i32 {
        match self {
            Instruction::Right(steps) => (other + steps) % MAXIMUM,
            Instruction::Left(steps) => (other - steps).rem_euclid(MAXIMUM),
        }
    }
}

pub fn solve_puzzle(document: &str) -> u32 {
    println!("{document}");
    0
}

#[cfg(test)]
mod solution_unittest {
    use googletest::prelude::*;

    use super::*;
    #[gtest]
    fn test_add_instruction_left() -> Result<()> {
        let counter = 50;
        let result = Instruction::Left(68) + counter;
        verify_that!(result, eq(82))
    }

    #[gtest]
    fn test_add_instruction_right() -> Result<()> {
        let counter = 50;
        let result = Instruction::Right(68) + counter;
        verify_that!(result, eq(18))
    }

    #[gtest]
    fn test_convert_to_instruction() -> Result<()> {
        let left_instruction: Instruction = "L32".into();
        verify_that!(
            left_instruction,
            matches_pattern!(Instruction::Left(eq(&32)))
        )
    }
}
