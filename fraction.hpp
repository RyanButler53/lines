#include <string>

#ifndef FRACTION_HPP_INCLUDED
#define FRACTION_HPP_INCLUDED
struct Fraction{

    long long num_;
    long long den_;

    // Constructors
    Fraction(long long num, long long den);
    Fraction(long long num);
    Fraction(std::string s);
    Fraction(const Fraction &other) = default;
    ~Fraction() = default;

    // Operators

    // Comparison
    bool operator<(const Fraction &f) const;
    bool operator>(const Fraction &f) const;
    bool operator<=(const Fraction &f) const;
    bool operator>=(const Fraction &f) const;
    bool operator!=(const Fraction &f) const;
    bool operator==(const Fraction &f) const;

    void simplify(); // use gcd
};

Fraction operator+(const Fraction &left, const Fraction &right);
Fraction operator-(const Fraction &left, const Fraction &right);
Fraction operator*(const Fraction &left, const Fraction &right);
Fraction operator/(const Fraction &left, const Fraction &right);

std::ostream &operator<<(std::ostream &os, const Fraction &f);

#endif // FRACTION_HPP_INCLUDED