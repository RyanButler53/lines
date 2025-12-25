#include "fraction.hpp"
#include <algorithm>
#include <numeric>
#include <ostream>
#include <cassert>

using namespace std;

Fraction::Fraction(long long num, long long den) :
 num_{num}, den_{den}
{
    assert(den_); // Cannot have denominators be zero!
}

Fraction::Fraction(long long num):
 num_{num}, den_{1}
{
    assert(den_); // Cannot have denominators be zero!
}

Fraction::Fraction(string s){
    size_t slashInd = s.find("/");
    if (slashInd != string::npos){
        num_ = stoll(s.substr(0, slashInd));
        den_ = stoll(s.substr(slashInd+1));
    } else {
        num_ = stoll(s);
        den_ = 1;
    }
}

float Fraction::toFloat() const{
    return float(num_) / float(den_);
}

std::ostream &operator<<(std::ostream &os, const Fraction &f){
    if (f.den_ == 1){
        os << f.num_;
    } else {
        os << f.num_ << "/" << f.den_;
    }
    return os;
}

void Fraction::simplify(){
    long long gcd = std::gcd(num_, den_);
    num_ = num_ / gcd;
    den_ = den_ / gcd;
}

bool Fraction::operator<(const Fraction& f) const{
    return num_ * f.den_ < den_ * f.num_;
}

bool Fraction::operator>(const Fraction& f) const{
    return num_ * f.den_ > den_ * f.num_;
}

bool Fraction::operator<=(const Fraction& f) const{
    return (*this == f) or (*this < f);
}

bool Fraction::operator>=(const Fraction& f) const{
    return (*this == f) or (*this > f);
}

bool Fraction::operator==(const Fraction &f) const{
    return num_ * f.den_ == den_ * f.num_;
}

bool Fraction::operator!=(const Fraction &f) const{
    return !(*this == f);
}

Fraction operator+(const Fraction &left, const Fraction &right){
    long long commonDen = std::lcm(left.den_, right.den_);
    long long leftFactor = commonDen / left.den_;
    long long rightFactor = commonDen / right.den_;
    long long num = left.num_ * leftFactor + right.num_ * rightFactor;
    return Fraction{num,commonDen};
}

Fraction operator-(const Fraction &left, const Fraction &right){
    long long commonDen = std::lcm(left.den_, right.den_);
    long long leftFactor = commonDen / left.den_;
    long long rightFactor = commonDen / right.den_;
    long long num = left.num_ * leftFactor - right.num_ * rightFactor;
    return Fraction{num,commonDen};
}

Fraction operator*(const Fraction &left, const Fraction &right){
    Fraction product{left.num_ * right.num_, left.den_ * right.den_};
    product.simplify();
    return product;
}

Fraction operator/(const Fraction &left, const Fraction &right){
    assert(right.num_ != 0); // No dividing by zero
    Fraction flipped{right.den_, right.num_};
    return left * flipped;
}
