import math
import regex


class Fraction():
    def __init__(self,num,den) -> None:
        assert(den)
        self.num = num
        self.den = den

    def __repr__(self) -> str:
        if (self.den == 1):
            return str(self.num)
        else:
            return f"{self.num}/{self.den}"
    
    def reduce(self):
        gcd = math.gcd(self.num,self.den)
        self.num //= gcd
        self.den //= gcd
        return Fraction(self.num, self.den)

    def __eq__(self, other: object) -> bool:
        return self.num * other.den == self.den*other.num
    