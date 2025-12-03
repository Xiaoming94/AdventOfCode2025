fn parse_id_range(id_range: &str) -> (u64, u64) {
    let (start_str, end_str) = id_range.split_once('-').unwrap_or_else(|| {
        panic!("Invalid product id_range: {}", id_range);
    });

    return (
        start_str
            .trim()
            .parse::<u64>()
            .unwrap_or_else(|_| panic!("Invalid start_str: {}", start_str)),
        end_str
            .trim()
            .parse::<u64>()
            .unwrap_or_else(|_| panic!("Invalid end_str: {}", end_str)),
    );
}

fn find_invalid_products((idr_start, idr_end): (u64, u64)) -> Vec<u64> {
    fn is_invalid_id(id: &u64) -> bool {
        let length = id.checked_ilog10().unwrap_or(0) + 1;
        if length < 2 || length % 2 != 0 {
            return false;
        }
        let half_length = length / 2;
        let first_half = id / (10u64.pow(half_length));
        let second_half = id % (10u64.pow(half_length));
        return first_half == second_half;
    }
    (idr_start..=idr_end).filter(is_invalid_id).collect()
}

pub fn find_sum_invalid_product_ids(id_ranges: &str) -> u64 {
    id_ranges
        .split(',')
        .map(parse_id_range)
        .map(find_invalid_products)
        .flatten()
        .sum()
}

#[cfg(test)]
mod tests {
    use super::*;
    use googletest::prelude::*;

    #[gtest]
    fn verify_id_range_parser() -> Result<()> {
        let (start, stop) = parse_id_range("11-22");
        verify_that!(start, eq(11))?;
        verify_that!(stop, eq(22))
    }

    #[gtest]
    fn verify_finding_invalid_id() -> Result<()> {
        let invalid_ids = find_invalid_products((11, 22));
        verify_that!(invalid_ids[..], eq([11, 22]))
    }
}
