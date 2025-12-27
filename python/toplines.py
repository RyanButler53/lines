import parseLines
import randomLines
import py_lines as pl

def toplines(lines):
    """
    lines is a list of strings 
    """
    parser = parseLines.LineParser(lines)
    parsed = parser.getLines()
    return parsed, pl.intersecting_lines(parsed)

def trails(numTrails, numLines, jitter, separate):
    lines = randomLines.allSlopes(jitter, numLines)
    return lines, pl.trails(lines, numTrails, separate)