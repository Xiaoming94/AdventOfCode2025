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

impl Add<(u32, i32)> for Instruction {
    type Output = (u32, i32);

    fn add(self, other: (u32, i32)) -> (u32, i32) {
        let (result, acc) = other;
        let total_steps = match self {
            Instruction::Right(steps) => acc + steps,
            Instruction::Left(steps) => acc - steps,
        };

        let rotations = (total_steps / MAXIMUM).abs() as u32;
        return (
            result + rotations + ((total_steps <= 0 && acc != 0) as u32),
            self + acc,
        );
    }
}

const START: i32 = 50;

pub fn solve_puzzle(document: &str) -> u32 {
    let (result, _) = document.lines().map(Instruction::from).fold(
        (0, START),
        |(res, acc), instruction: Instruction| {
            let new_acc = instruction + acc;
            if new_acc == 0 {
                (res + 1, new_acc)
            } else {
                (res, new_acc)
            }
        },
    );

    return result;
}

pub fn solve_puzzle_new_instructions(document: &str) -> u32 {
    let (result, _) = document
        .lines()
        .map(Instruction::from)
        .fold((0, START), |acc, instruction: Instruction| {
            instruction + acc
        });

    return result;
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
    fn test_convert_to_left_instruction() -> Result<()> {
        let left_instruction: Instruction = "L32".into();
        verify_that!(
            left_instruction,
            matches_pattern!(Instruction::Left(eq(&32)))
        )
    }

    #[gtest]
    fn test_convert_to_right_instruction() -> Result<()> {
        let right_instruction: Instruction = "R42".into();
        verify_that!(
            right_instruction,
            matches_pattern!(Instruction::Right(eq(&42)))
        )
    }
}
