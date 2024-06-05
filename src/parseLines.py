import math
import re
import sys

class InvalidLineException(Exception):
    """Raise an Invalid Line Exception"""

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
    
class LineParser():

    def __init__(self, strings):
        
        #remove all spaces
        self.checkStrings(strings)
    
    def checkStrings(self,strings):
        self.strings = []
        for s in strings:
            s = re.sub(r' ',"",s)
            if s[:2] != "y=":
                raise InvalidLineException()
            self.strings.append(s[2:])
        
    def __call__(self):
        parsed = []
        for s in self.strings:
            slope,intercept = self.parseString(s)
            print(slope,intercept)

    def getSlopeOrInt(self, string, regex):
        """Gets the slope or intercept. 
        Returns the updated string and the slope/intercept value"""
        slope_int_match = re.match(regex,string)
        slope_int = 0
        if slope_int_match:
            slope_int_str = slope_int_match.group(0)
            # print(slope_int_str)
            slope_int_str = slope_int_str.rstrip("x")
            if '/' in slope_int_str:
                num,den = [int(x) for x in slope_int_str.split("/")]
                if den == 0:
                    raise InvalidLineException("Denominator must be nonzero")
                slope_int = Fraction(num,den)
            elif '.' in slope_int_str:
                num,den = slope_int_str.split(".")
                if num in '+-': #Get proper signs on decimal conversion
                    num+="0"
                slope_int = decToFrac(num,den)
            else:
                slope_int = int(slope_int_str)

            # chop off the match part
            string = string[slope_int_match.end():]
        return slope_int, string


    def parseString(self,string):
        """Parses a string and returns slope and intercept as a fraction. """
        slope_regex = r'^-?((\d{0,4}\.\d{1,4})|\d{1,4}|(\d{1,4}\/\d{1,4}))x'
        intercept_regex = r'^[+-]?((\d{0,4}\.\d{1,4})|\d{1,4}|(\d{1,4}\/\d{1,4}))$'
        slope = 0
        intercept = 0
        slope,string = self.getSlopeOrInt(string, slope_regex)
        intercept,string = self.getSlopeOrInt(string, intercept_regex)
        return slope,intercept
        

def decToFrac(number:str,decimal:str):
    """Converts a decimal to a fraction"""
    den = 10**(len(decimal))
    if (number[0] == '-'):
        num = int(number)*den - int(decimal)
    else:
        num = int(number)*den + int(decimal)
    return Fraction(num,den).reduce()

l = LineParser(["y=2x-3", "y=15.2x-14.3", "y=19x", "y=3/4", "y=12x-16/3", "y=1.9x-7/3"])
