# Goal: Generate random "fractions" or numbers to make cool artwork
import random
import numpy as np
import sys

def allSlopes(jitterFactor,n):
    slopes = range(-50,50,2)
    slopes = random.sample(slopes,n)
    intercepts = [-1*n * (abs(s)* abs(s-1))//2 for s in slopes]
    slopes = [s +int(np.random.normal(0,jitterFactor)) for s in slopes]
    for s,i in zip(slopes,intercepts):
        print(s,i)

if len(sys.argv) == 1:
    allSlopes(7,30)
else:
    numLines = int(sys.argv[1])
    jitter = int(sys.argv[2])
    allSlopes(jitter,numLines)
