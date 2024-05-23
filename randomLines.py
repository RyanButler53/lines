# Goal: Generate random "fractions" or numbers to make cool artwork
import random
import math

class Fraction():
    def __init__(self,num,den) -> None:
        assert(den != 0)
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
    den = random.choice(denRange)
    return Fraction(num,den)
        
denRange = list([1,2,3,4,5,6])

numerators = random.sample(range(-40, 40),20)
denominators = [random.choice(denRange) for _ in range(20)]

slopes = set([Fraction(n,d).reduce() for n,d in zip(numerators,denominators)])

for s in slopes:
    i = randomFrac()
    print(s,i)

