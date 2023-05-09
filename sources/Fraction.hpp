#pragma once
#include <string>
#include <iostream>
#include <limits.h>
#include <numeric>
#include <cmath>

using namespace std;

namespace ariel
{

    class Fraction
    {
    private:
        // variebles
        int numerator_;
        int denominator_;

        // helper functions
        void reduce();
        long long abs(long long) const;
        int compareTo(const Fraction &) const;

    public:
        // constructors
        Fraction();
        Fraction(int, int);
        Fraction(float);

        // getters
        int getNumerator() const;
        int getDenominator() const;

        // overload arithmetic operators
        const friend Fraction operator+(const Fraction &, const Fraction &);
        const friend Fraction operator-(const Fraction &, const Fraction &);
        const friend Fraction operator*(const Fraction &, const Fraction &);
        const friend Fraction operator/(const Fraction &, const Fraction &);

        // overload increase by one opertor
        Fraction operator++();    // prefix
        Fraction operator++(int); // postfix

        // overload decrease by one opertor
        Fraction operator--();    // prefix
        Fraction operator--(int); // postfix

        // overload comparison operations operators
        friend bool operator==(const Fraction &, const Fraction &);
        friend bool operator>(const Fraction &, const Fraction &);
        friend bool operator<(const Fraction &, const Fraction &);
        friend bool operator>=(const Fraction &, const Fraction &);
        friend bool operator<=(const Fraction &, const Fraction &);

        // overload input/output operator
        friend istream &operator>>(istream &, Fraction &);
        friend ostream &operator<<(ostream &, const Fraction &);
    };

}
