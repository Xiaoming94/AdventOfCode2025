#!/bin/env python

import solution
import sys
from functools import reduce
import operator

input = reduce(operator.add, sys.stdin, "").rstrip('\n')

print("input is: %s" % input)
print("Solution for problem 1: %d" % solution.solve_problem1(input))
