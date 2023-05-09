#pragma once
#include <string>
#include <iostream>
#include <limits.h>
#include <numeric>

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
        int gcd(int, int) const;
        long long abs(long long) const;
        int compareTo(const Fraction &) const;
        void handle_overflow(long long, long long) const;


    public:
        // constructors
        Fraction();
         Fraction(int, int);
         Fraction(float);

        // getters
        int getNumerator() const;
        int getDenominator() const;

        // overload plus operator
        Fraction operator+(const Fraction &) const;
        
        // overload minus operator
        Fraction operator-(const Fraction &) const;

        // overload multiplication operator
        Fraction operator*(const Fraction &) const;

        // overload division operator
        Fraction operator/(const Fraction &) const;

        // overload increase by one opertor
        Fraction operator++();    // prefix
        Fraction operator++(int); // postfix

        // overload decrease by one opertor
        Fraction operator--();    // prefix
        Fraction operator--(int); // postfix

        // overload equality operator
        bool operator==(const Fraction &) const;

        // overload greater-then operator
        bool operator>(const Fraction &) const;

        // overload less-then operator
        bool operator<(const Fraction &) const;

        // overload greater-then or equal to operator
        bool operator>=(const Fraction &) const;

        // overload less-then or equal to operator
        bool operator<=(const Fraction &) const;

        // input/output operator
        friend istream &operator>>(istream &, Fraction &);
        friend ostream &operator<<(ostream &, const Fraction &);
    };

}
