import re
import py_lines as pl

class InvalidLineException(Exception):
    """Raise an Invalid Line Exception"""

# class Fraction():
#     """Class to handle Fractions"""
#     def __init__(self,num,den) -> None:
#         assert(den)
#         self.num = num
#         self.den = den

#     def __repr__(self) -> str:
#         if (self.den == 1):
#             return str(self.num)
#         else:
#             return f"{self.num}/{self.den}"
    
#     def reduce(self):
#         gcd = math.gcd(self.num,self.den)
#         self.num //= gcd
#         self.den //= gcd
#         return Fraction(self.num, self.den)

#     def __eq__(self, other: object) -> bool:
#         return self.num * other.den == self.den*other.num
    
class LineParser():

    def __init__(self, strings):
        #remove all spaces
        self.clearSpaces(strings)
    
    def clearSpaces(self,strings):
        """Removes all spaces from the lines"""
        self.strings = []
        for s in strings:
            noSpace = re.sub(r' ',"",s)
            self.strings.append(noSpace)
        
    def getLines(self):
        """Parses all the strings and sends them to intersecting_lines"""
        lines = []
        for s in self.strings:
            slope,intercept = self.parseString(s)
            print(slope, intercept, s, type(slope), type(intercept))
            lines.append(pl.Line(slope, intercept))
        return lines

    def getSlopeOrInt(self, string, regex):
        """Gets the slope or intercept. 
        Returns the updated string and the slope/intercept value"""
        slope_int_match = re.match(regex,string)
        slope_int = pl.Fraction(0)
        if slope_int_match:
            # gets slope or intercept part of string
            slope_int_str = slope_int_match.group(0)
            slope_int_str = slope_int_str.rstrip("x")

            # Check fraction, decimal or integer
            if '/' in slope_int_str:
                num,den = [int(x) for x in slope_int_str.split("/")]
                if den == 0:
                    raise InvalidLineException("Denominator must be nonzero")
                slope_int = pl.Fraction(num,den)
            elif '.' in slope_int_str:
                num,dec = slope_int_str.split(".")
                if num in '+-': #Get proper signs on decimal conversion
                    num+="0"
                slope_int = decToFrac(num,dec)
            else:
                if (slope_int_str == '-' or slope_int_str==""):
                    slope_int_str+="1"
                slope_int = pl.Fraction(int(slope_int_str))

            # chop off the match part
            string = string[slope_int_match.end():]
        return slope_int, string


    def parseString(self,string):
        """Parses a string and returns slope and intercept as a fraction.
         If there is an error, slope or intercept becomes zero """
        slope_regex = r'^-?((\d{0,4}\.\d{1,4})|\d{1,4}|(\d{1,4}\/\d{1,4}))?x'
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
    frac = pl.Fraction(num,den)
    frac.simplify()
    return frac
