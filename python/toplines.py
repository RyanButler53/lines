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

def trails(numTrails = 4, numLines=30, jitter = 7, separate = True):
    lines = randomLines.allSlopes(jitter, numLines)
    return lines, pl.trails(lines, numTrails, separate)