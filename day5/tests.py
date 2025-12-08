import unittest
import solution

class TestAoc2025Day5(unittest.TestCase):
    input = ("3-5\n"
             "10-14\n"
             "16-20\n"
             "12-18\n"
             "\n"
             "1\n"
             "5\n"
             "8\n"
             "11\n"
             "17\n"
             "32")

    def test_problem1solution(self):
        result = solution.solve_problem1(self.input)
        self.assertEqual(result, 3)

    def test_problem2solution(self):
        result = solution.solve_problem2(self.input)
        self.assertEqual(result, 14)

if __name__ == '__main__':
    unittest.main()
