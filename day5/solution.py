def merge_ranges(unmerged_ranges: list[tuple[int, int]]) -> list[tuple[int, int]]:
    unmerged_ranges.sort(key=lambda id_range: id_range[0])
    merged = list()

    current_lower, current_upper = unmerged_ranges[0]
    for next_lower, next_upper in unmerged_ranges[1:]:
        if current_upper >= next_lower: # These two are overlapping
            current_upper = max(current_upper, next_upper)
        else:

            #no overlaps, adding them to merged
            merged.append((current_lower, current_upper))
            current_lower, current_upper = next_lower, next_upper

    merged.append((current_lower, current_upper))
    return merged

def create_ranges(ranges_str: str) -> list[tuple[int, int]]:
    def create_fresh_range(ranges_line: str) -> tuple[ int, int ]:
        [lower, upper] = ranges_line.split('-')
        return int(lower), int(upper)

    initial_ranges = [create_fresh_range(line) for line in ranges_str.split('\n')]

    return merge_ranges(initial_ranges)


def transform_to_int_ids(ingredient_liststr: str) -> list[int]:
    return [int(ingredient_id) for ingredient_id in ingredient_liststr.split('\n')]

def find_fresh_ingredients(fresh_ids: list[tuple[int, int]], ingredients_ids: list[int]) -> int:
    def check_if_id_is_fresh(id: int, fresh_ids: list[tuple[int, int]]):
        for (lower, upper) in fresh_ids:
            if id >= lower and id <= upper:
                return 1

        return 0

    return sum(check_if_id_is_fresh(id, fresh_ids) for id in ingredients_ids)

def solve_problem1(input: str):
    [ranges_str, ingredient_liststr] = input.split('\n\n')
    ranges = create_ranges(ranges_str)
    ingredient_ids = transform_to_int_ids(ingredient_liststr)

    return find_fresh_ingredients(ranges, ingredient_ids)
