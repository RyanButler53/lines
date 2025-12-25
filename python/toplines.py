import parseLines
import py_lines as pl

def toplines(lines):
    """
    lines is a list of strings 
    """
    parser = parseLines.LineParser(lines)
    parsed = parser.getLines()
    return parsed, pl.intersecting_lines(parsed)
