import random
import numpy as np
import py_lines as pl

def allSlopes(jitterFactor, n):
    slopes = range(-50,50,2)
    slopes = random.sample(slopes,n)
    intercepts = [-1*n * (abs(s)* abs(s-1))//2 for s in slopes]
    slopes = [s +int(np.random.normal(0,jitterFactor)) for s in slopes]
    return [pl.Line(s, i) for s, i in zip(slopes, intercepts)]
