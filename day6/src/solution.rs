pub(crate) fn solve_problem1(input: &str) -> u64 {
    let problem_as_vectors: Vec<Vec<_>> = input
        .lines()
        .map(|line| line.split_whitespace().collect::<Vec<_>>())
        .collect();

    let operators = problem_as_vectors.last().unwrap();

    println!("Operators: {:?}", operators);
    0
}
