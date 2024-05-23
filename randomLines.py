# Goal: Generate random "fractions" or numbers to make cool artwork
import random
import numpy as np
import math

DENOMINATOR_RANGE = [1,2,3,4,5,6,7,8,9,10]

class Fraction():
    def __init__(self,num,den) -> None:
        assert(den)
        self.num = num
        self.den = den

    def __repr__(self) -> str:
        return f"{self.num}/{self.den}"
    
    def reduce(self):
        gcd = math.gcd(self.num,self.den)
        self.num //= gcd
        self.den //= gcd
        return Fraction(self.num, self.den)

    def __hash__(self) -> int:
        return hash(self.num) ^ hash(self.den)

    def __eq__(self, other: object) -> bool:
        return self.num * other.den == self.den*other.num
    
def randomFrac():
    num = random.choice(range(-20, 20))
    den = random.choice(DENOMINATOR_RANGE)
    return Fraction(num,den)

def gaussFrac(n=100):
    assert(n)
    num = np.random.normal()
    num = int(n*num)
    return Fraction(num,n).reduce()

def randomEverything():

    numerators = random.sample(range(-20, 20),20)
    # numerators = set([gaussFrac(30) for _ in range(20)])
    denominators = [random.choice(DENOMINATOR_RANGE) for _ in range(20)]

    slopes = set([Fraction(n,d).reduce() for n,d in zip(numerators,denominators)])

    for s in slopes:
        i = randomFrac()
        print(s,i)

def gaussSlopes():
    slopes = set([gaussFrac(30) for _ in range(20)])
    for s in slopes:
        i = gaussFrac(5)
        i.num *= 5
        print(s,i)

def transformSlope(s,jitterFactor):
    """Add some jittering"""
    jitter = int(np.random.normal(0,jitterFactor))
    jitter *= s.den
    return Fraction(s.num+jitter, s.den)


def allSlopes(jitterFactor=1):
    slopes = [Fraction(x,10) for x in range(-80,80)]
    slopes = random.sample(slopes,30)
    intercepts = [transformSlope(s,jitterFactor) for s in slopes]
    for s,i in zip(slopes,intercepts):
        print(s,i)

# gaussSlopes()
allSlopes(15)
