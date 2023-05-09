#include "Fraction.hpp"                                                            
using namespace ariel;

// constructors
Fraction::Fraction()
{
    this->numerator_ = 0;
    this->denominator_ = 1;
}
Fraction::Fraction(int numerator, int denominator)
{
    // first, check if the fraction is valid
    if (denominator == 0)
    {
        throw invalid_argument("");
    }

    this->numerator_ = numerator;
    this->denominator_ = denominator;
    reduce();
}
Fraction::Fraction(float number)
{
    this->numerator_ = number * 1000;
    this->denominator_ = 1000;
    reduce();
}

// helper functions
void Fraction::reduce()
{
    int gcdNum = gcd(this->denominator_, this->numerator_);
    this->numerator_ /= gcdNum;
    this->denominator_ /= gcdNum;
    // raise the minus the the numerator
    if (this->denominator_ < 0)
    {
        this->numerator_ *= -1;
        this->denominator_ *= -1;
    }
}
long long Fraction::abs(long long number) const
{
    if (number < 0)
        return (-1) * number;

    return number;
}
int Fraction::compareTo(const Fraction &otherFraction) const
{
    // first, find the common divider:
    int gcdNum = gcd(this->denominator_, otherFraction.denominator_);
    int mult = this->denominator_ * otherFraction.denominator_;
    int lcm = mult / gcdNum;
    // then, multiply both fructions by the commonDivider
    int thisnumerator = this->numerator_ * (lcm / this->denominator_);
    int otherNumerator = otherFraction.numerator_ * (lcm / otherFraction.denominator_);
    // compare the numerators
    if (thisnumerator > otherNumerator)
        return 1;

    if (thisnumerator < otherNumerator)
        return -1;

    return 0;
}

// out function
void handle_overflow(long long numerator, long long denominator)
{
    if (numerator < INT_MIN || INT_MAX < numerator || denominator < INT_MIN || INT_MAX < denominator)
        throw std::overflow_error("The result fraction is overflow");
}

// getters
int Fraction::getNumerator() const
{
    return this->numerator_;
}
int Fraction::getDenominator() const
{
    return this->denominator_;
}

// overload arithmetic operators
const Fraction ariel::operator+(const Fraction &fraction1, const Fraction &fraction2)
{
    // first, find the common divider:
    int gcdNum = gcd(fraction1.denominator_, fraction2.denominator_);
    long long mult = (long long)(fraction1.denominator_) * (long long)(fraction2.denominator_);
    mult = abs(mult);
    long long lcm = mult / gcdNum;
    // then, multiply both fructions by the commonDivider
    long long numerator1 = (long long)(fraction1.numerator_) * (lcm / fraction1.denominator_);
    long long numerator2 = (long long)(fraction2.numerator_) * (lcm / fraction2.denominator_);
    // sum the numerators
    long long sumNumerator = numerator1 + numerator2;
    // check overflow case
    handle_overflow(sumNumerator, lcm);
    // build a new fraction
    Fraction sumFraction((int)(sumNumerator), (int)(lcm));
    return sumFraction;
}
const Fraction ariel::operator-(const Fraction &fraction1, const Fraction &fraction2)
{
    // first, find the common divider:
    int gcdNum = gcd(fraction1.denominator_, fraction2.denominator_);
    long long mult = (long long)(fraction1.denominator_) * (long long)(fraction2.denominator_);
    mult = abs(mult);
    long long lcm = mult / gcdNum;
    // then, multiply both fructions by the commonDivider
    long long numerator1 = (long long)(fraction1.numerator_) * (lcm / fraction1.denominator_);
    long long numerator2 = (long long)(fraction2.numerator_) * (lcm / fraction2.denominator_);
    // sum the numerators
    long long subNumerator = numerator1 - numerator2;
    // check overflow case
    handle_overflow(subNumerator, lcm);
    // build a new fraction
    Fraction subFraction((int)(subNumerator), (int)(lcm));
    return subFraction;
}
const Fraction ariel::operator*(const Fraction &fraction1, const Fraction &fraction2)
{
    long long numerator = (long long)(fraction1.numerator_) * (long long)(fraction2.numerator_);
    long long denominator = (long long)(fraction1.denominator_) * (long long)(fraction2.denominator_);
    // check overflow case
    handle_overflow(numerator, denominator);
    // build a new fraction
    Fraction multFraction(numerator, denominator);
    return multFraction;
}
const Fraction ariel::operator/(const Fraction &fraction1, const Fraction &fraction2)
{
    // first, check if the fraction is valid
    if (fraction2.numerator_ == 0)
    {
        throw runtime_error("0 can't be in the denominator");
    }
    Fraction inverseFraction(fraction2.denominator_, fraction2.numerator_);
    return fraction1 * inverseFraction;
}

// overload increase by one opertor
Fraction Fraction::operator++()
{
    this->numerator_ += this->denominator_;
    return *this;
}
Fraction Fraction::operator++(int num)
{
    Fraction temp(this->numerator_, this->denominator_);
    this->numerator_ += this->denominator_;
    return temp;
}

// overload decrease by one opertor
Fraction Fraction::operator--()
{
    this->numerator_ -= this->denominator_;
    return *this;
}
Fraction Fraction::operator--(int num)
{
    Fraction temp(this->numerator_, this->denominator_);
    this->numerator_ -= this->denominator_;
    return temp;
}

// overload comparison operations operators
bool ariel::operator==(const Fraction &fraction1, const Fraction &fraction2)
{
    if (fraction1.compareTo(fraction2) == 0)
        return true;
    return false;
}
bool ariel::operator>(const Fraction &fraction1, const Fraction &fraction2)
{
    if (fraction1.compareTo(fraction2) == 1)
        return true;
    return false;
}
bool ariel::operator<(const Fraction &fraction1, const Fraction &fraction2)
{
    if (fraction1.compareTo(fraction2) == -1)
        return true;
    return false;
}
bool ariel::operator<=(const Fraction &fraction1, const Fraction &fraction2)
{
    return (fraction1 < fraction2) || (fraction1 == fraction2);
}
bool ariel::operator>=(const Fraction &fraction1, const Fraction &fraction2)
{
    return (fraction1 > fraction2) || (fraction1 == fraction2);
}

// input/output operator
istream &ariel::operator>>(istream &input, Fraction &otherFraction)
{
    int numerator, denominator;
    input >> numerator >> denominator;
    otherFraction.numerator_ = numerator;
    otherFraction.denominator_ = denominator;
    if (input.fail())
    {
        throw runtime_error("invalid argument");
    }
    if (denominator == 0)
    {
        throw runtime_error("0 can't be in the denominator");
    }

    otherFraction.reduce();

    return input;
}
ostream &ariel::operator<<(ostream &output, const Fraction &otherFraction)
{
    output << otherFraction.numerator_ << '/' << otherFraction.denominator_;
    return output;
}