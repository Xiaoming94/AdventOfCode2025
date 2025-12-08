def merge_ranges(unmerged_ranges: list[tuple[int, int]]) -> list[tuple[int, int]]:
    has_merges = True
    merged_ranges = unmerged_ranges.copy()
    while has_merges:
        has_merges = False
        ranges_copy = merged_ranges.copy()
        merged_ranges.clear()
        ranges_copy_mutable = ranges_copy.copy()
        for i, r_fresh in enumerate(ranges_copy):
            if not r_fresh in ranges_copy_mutable:
                break

            n_ranges = len(ranges_copy_mutable)
            for j in range(i+1, n_ranges):
                lower1, upper1 = r_fresh
                r_fresh2 = ranges_copy_mutable[j]
                lower2, upper2 = r_fresh2
                if not (upper1 < lower2 or lower1 > upper2): # Check weather they are overlapping
                    r_fresh = (min(lower1, lower2), max(upper1, upper2))
                    ranges_copy_mutable.remove(r_fresh2)
                    has_merges = True

            merged_ranges.append(r_fresh)

    return merged_ranges


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
