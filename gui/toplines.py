from .parseLines import LineParser
from .randomLines import allSlopes
import py_lines as pl

def toplines(lines):
    """
    lines is a list of strings 
    """
    parser = LineParser(lines)
    parsed = []
    parsed = parser.getLines()
    return parsed, pl.intersecting_lines(parsed)

def trails(numTrails, numLines, jitter, separate):
    lines = allSlopes(jitter, numLines)
    return lines, pl.trails(lines, numTrails, separate)
