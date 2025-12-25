# import pytest
import py_lines as pl
import os.path
import pathlib

INPUT_DIR=os.path.join(pathlib.Path(__file__).parent.parent, "inputs")
# problem_file = f"{INPUT_DIR}/4lines2.txt"
# soln_file = f"{INPUT_DIR}/4lines2-soln.txt"

# solution = pl.toplines(soln_file)
# lines = pl.lines_from_file(problem_file)
# solve = pl.intersecting_lines(lines)

def check(problem, solution):
    problem_file = f"{INPUT_DIR}/{problem}.txt"
    soln_file = f"{INPUT_DIR}/{solution}.txt"
    lines = pl.lines_from_file(problem_file)
    solution = pl.TopLines(soln_file)
    solve = pl.intersecting_lines(lines)
    return solve == solution

def test_TripleOverlap():
    assert check("4lines2", "4lines2-soln")

def test_Recursive4Lines():
    assert check("4lines", "4lines-soln")

def test_Recursive9Lines():
    assert check("9lines", "9lines-soln")
