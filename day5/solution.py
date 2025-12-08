def create_ranges(ranges_str: str) -> set[int]:
    def create_range(line: str) -> set[int]:
        [lower_str, upper_str] = line.split('-')
        upper = int(upper_str) + 1
        lower = int(lower_str)
        return set(range(lower,upper))

    ranges = [create_range(line) for line in ranges_str.splitlines()]
    return set.union(*ranges)

def transform_to_int_ids(ingredient_liststr: str) -> list[int]:
    return [int(ingredient_id) for ingredient_id in ingredient_liststr.split('\n')]

def find_fresh_ingredients(fresh_ids: set[int], ingredients_ids: list[int]) -> int:
    return sum(1 for id in ingredients_ids if id in fresh_ids)

def solve_problem1(input: str):
    [ranges_str, ingredient_liststr] = input.split('\n\n')
    ranges = create_ranges(ranges_str)
    ingredient_ids = transform_to_int_ids(ingredient_liststr)

    return find_fresh_ingredients(ranges, ingredient_ids)
