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

fn find_invalid_product_ids<F: Fn(&u64) -> bool>(
    (idr_start, idr_end): (u64, u64),
    is_invalid_id: F,
) -> Vec<u64> {
    (idr_start..=idr_end).filter(is_invalid_id).collect()
}

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

fn is_invalid_subrange_id(id: &u64) -> bool {
    let length = id.checked_ilog10().unwrap_or(0) + 1;
    if length < 2 {
        return false;
    }

    let half_length = length / 2;
    fn is_invalid_chunk_id(mut id: u64, view_size: u32) -> bool {
        let view_divider = 10u64.pow(view_size);
        let chunk = id % view_divider;
        id = id / view_divider;
        while id != 0 {
            let next_chunk = id % view_divider;
            if next_chunk != chunk {
                return false;
            }
            id = id / view_divider;
        }
        return true;
    }

    for view_size in (1..=half_length).filter(|view_size| length % view_size == 0) {
        if is_invalid_chunk_id(*id, view_size) {
            return true;
        };
    }
    return false;
}

fn internal_sum_invalid_product_ids(id_ranges: &str, use_subrange: bool) -> u64 {
    let invalid_product_id_fun = if use_subrange {
        |id_range: (u64, u64)| find_invalid_product_ids(id_range, is_invalid_subrange_id)
    } else {
        |id_range: (u64, u64)| find_invalid_product_ids(id_range, is_invalid_id)
    };

    id_ranges
        .split(',')
        .map(parse_id_range)
        .map(invalid_product_id_fun)
        .flatten()
        .sum()
}

pub fn find_sum_invalid_product_ids(id_ranges: &str) -> u64 {
    internal_sum_invalid_product_ids(id_ranges, false)
}

pub fn find_sum_invalid_product_ids_v2(id_ranges: &str) -> u64 {
    internal_sum_invalid_product_ids(id_ranges, true)
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
        let invalid_ids = find_invalid_product_ids((11, 22), is_invalid_id);
        verify_that!(invalid_ids[..], eq([11, 22]))
    }

    #[gtest]
    fn verify_finding_invalid_id_with_subranges() -> Result<()> {
        let invalid_ids = find_invalid_product_ids((11, 22), is_invalid_subrange_id);
        verify_that!(invalid_ids[..], eq([11, 22]))
    }

    #[gtest]
    fn verify_finding_invalid_id_with_subranges2() -> Result<()> {
        let invalid_ids = find_invalid_product_ids((998, 1012), is_invalid_subrange_id);
        verify_that!(invalid_ids[..], eq([999, 1010]))
    }
}
