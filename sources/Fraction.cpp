#include "Fraction.hpp"
#include <cmath>

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
int Fraction::gcd(int number1, int number2) const
{
    int absNum1 = abs(number1);
    int absNum2 = abs(number2);
    int minNum = min(absNum1, absNum2);
    for (int i = minNum; i > 0; i--)
    {
        if ((absNum1 % i == 0) && (absNum2 % i == 0))
        {
            return i;
        }
    }
    return 1;
}
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
void Fraction::handle_overflow(long long numerator, long long denominator) const
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

// overload plus operator
Fraction Fraction::operator+(const Fraction &otherFraction) const
{
    // first, find the common divider:
    int gcdNum = gcd(this->denominator_, otherFraction.denominator_);
    long long mult = (long long)(this->denominator_) * (long long)(otherFraction.denominator_);
    mult = abs(mult);
    long long lcm = mult / gcdNum;
    // then, multiply both fructions by the commonDivider
    long long numerator1 = (long long)(this->numerator_) * (lcm / this->denominator_);
    long long numerator2 = (long long)(otherFraction.numerator_) * (lcm / otherFraction.denominator_);
    // sum the numerators
    long long sumNumerator = numerator1 + numerator2;
    // check overflow case
    handle_overflow(sumNumerator, lcm);
    // build a new fraction
    Fraction sumFraction((int)(sumNumerator), (int)(lcm));
    return sumFraction;
}
Fraction Fraction::operator+(float number) const
{
    // first, convert the number to fraction
    int numerator = number * 1000;
    int denominator = 1000;
    Fraction floatFrac(numerator, denominator);

    return floatFrac + *this;
}
Fraction ariel::operator+(float number, const Fraction &otherFraction)
{
    return otherFraction + number;
}

// overload minus operator
Fraction Fraction::operator-(const Fraction &otherFraction) const
{
    // first, find the common divider:
    int gcdNum = gcd(this->denominator_, otherFraction.denominator_);
    long long mult = (long long)(this->denominator_) * (long long)(otherFraction.denominator_);
    mult = abs(mult);
    long long lcm = mult / gcdNum;
    // then, multiply both fructions by the commonDivider
    long long numerator1 = (long long)(this->numerator_) * (lcm / this->denominator_);
    long long numerator2 = (long long)(otherFraction.numerator_) * (lcm / otherFraction.denominator_);
    // sub the numerators
    long long subNumerator = numerator1 - numerator2;
    // check overflow case
    handle_overflow(subNumerator, lcm);
    // build a new fraction
    Fraction subFraction((int)(subNumerator), (int)(lcm));
    return subFraction;
}
Fraction Fraction::operator-(float number) const
{
    // first, convert the number to fraction
    Fraction const floatFrac(number);
    return *this - floatFrac;
}
Fraction ariel::operator-(float number, const Fraction &otherFraction)
{
    // first, convert the number to fraction
    Fraction const floatFrac(number);
    return floatFrac - otherFraction;
}

// overload multiplication operator
Fraction Fraction::operator*(const Fraction &otherFraction) const
{
    long long numerator = (long long)(this->numerator_) * (long long)(otherFraction.numerator_);
    long long denominator = (long long)(this->denominator_) * (long long)(otherFraction.denominator_);
    // check overflow case
    handle_overflow(numerator, denominator);
    // build a new fraction
    Fraction multFraction(numerator, denominator);
    return multFraction;
}
Fraction Fraction::operator*(float number) const
{
    // first, convert the number to fraction
    Fraction const floatFrac(number);
    return floatFrac * (*this);
}
Fraction ariel::operator*(float number, const Fraction &otherFraction)
{
    return otherFraction * number;
}

// overload division operator
Fraction Fraction::operator/(const Fraction &otherFraction) const
{
    // first, check if the fraction is valid
    if (otherFraction.numerator_ == 0)
    {
        throw runtime_error("0 can't be in the denominator");
    }
    Fraction inverseFraction(otherFraction.denominator_, otherFraction.numerator_);
    return (*this) * inverseFraction;
}
Fraction Fraction::operator/(float number) const
{
    // first, convert the number to fraction
    Fraction const floatFrac(number);
    return (*this) / floatFrac;
}
Fraction ariel::operator/(float number, const Fraction &otherFraction)
{
    Fraction inverseFraction(otherFraction.denominator_, otherFraction.numerator_);
    return inverseFraction * number;
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

// overload equality operator
bool Fraction::operator==(const Fraction &otherFraction) const
{
    if (this->compareTo(otherFraction) == 0)
        return true;
    return false;
}
bool Fraction::operator==(float number) const
{
    // first, convert the number to fraction
    Fraction const floatFrac(number);
    return floatFrac == (*this);
}
bool ariel::operator==(float number, const Fraction &otherFraction)
{
    return otherFraction == number;
}

// overload greater-then operator
bool Fraction::operator>(const Fraction &otherFraction) const
{
    if (this->compareTo(otherFraction) == 1)
        return true;
    return false;
}
bool Fraction::operator>(float number) const
{
    // first, convert the number to fraction
    Fraction const floatFrac(number);
    return (*this) > floatFrac;
}
bool ariel::operator>(float number, const Fraction &otherFraction)
{
    // first, convert the number to fraction
    Fraction const floatFrac(number);
    return floatFrac > otherFraction;
}

// overload less-then operator
bool Fraction::operator<(const Fraction &otherFraction) const
{
    if (this->compareTo(otherFraction) == -1)
        return true;
    return false;
}
bool Fraction::operator<(float number) const
{
    // first, convert the number to fraction
    Fraction const floatFrac(number);
    return (*this) < floatFrac;
}
bool ariel::operator<(float number, const Fraction &otherFraction)
{
    // first, convert the number to fraction
    Fraction const floatFrac(number);
    return floatFrac < otherFraction;
}

// overload less-then or equal to operator
bool Fraction::operator<=(const Fraction &otherFraction) const
{
    return (*this < otherFraction) || (*this == otherFraction);
}
bool Fraction::operator<=(float number) const
{
    return (*this < number) || (number == *this);
}
bool ariel::operator<=(float number, const Fraction &otherFraction)
{
    return (number < otherFraction) || (number == otherFraction);
}

// overload greater-then or equal to operator
bool Fraction::operator>=(const Fraction &otherFraction) const
{
    return (*this > otherFraction) || (*this == otherFraction);
}
bool Fraction::operator>=(float number) const
{
    return (*this > number) || (number == *this);
}
bool ariel::operator>=(float number, const Fraction &otherFraction)
{
    return (number > otherFraction) || (number == otherFraction);
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