#pragma once
#include <string>
#include <iostream>
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
        int abs(int) const;
        int compareTo(const Fraction &) const;

    public:
        // constructors
        Fraction();
        explicit Fraction(int, int);
        explicit Fraction(float);

        // Fraction(const Fraction&);
        // Fraction &operator= (const Fraction&);
        //~Fraction();

        // getters
        int getNumerator() const;
        int getDenominator() const;

        // overload plus operator
        Fraction operator+(const Fraction &) const;
        Fraction operator+(float) const;
        friend Fraction operator+(float, const Fraction &);

        // overload minus operator
        Fraction operator-(const Fraction &) const;
        Fraction operator-(float) const;
        friend Fraction operator-(float, const Fraction &);

        // overload multiplication operator
        Fraction operator*(const Fraction &) const;
        Fraction operator*(float) const;
        friend Fraction operator*(float, const Fraction &);

        // overload division operator
        Fraction operator/(const Fraction &) const;
        Fraction operator/(float) const;
        friend Fraction operator/(float, const Fraction &);

        // overload increase by one opertor
        Fraction operator++();    // prefix
        Fraction operator++(int); // postfix

        // overload decrease by one opertor
        Fraction operator--();    // prefix
        Fraction operator--(int); // postfix

        // overload equality operator
        bool operator==(const Fraction &) const;
        bool operator==(float) const;
        friend bool operator==(float, const Fraction &);

        // overload greater-then operator
        bool operator>(const Fraction &) const;
        bool operator>(float) const;
        friend bool operator>(float, const Fraction &);

        // overload less-then operator
        // overload less-then operator
        bool operator<(const Fraction &) const;
        bool operator<(float) const;
        friend bool operator<(float, const Fraction &);

        // overload greater-then or equal to operator
        bool operator>=(const Fraction &) const;
        bool operator>=(float) const;
        friend bool operator>=(float, const Fraction &);

        // overload less-then or equal to operator
        bool operator<=(const Fraction &) const;
        bool operator<=(float) const;
        friend bool operator<=(float, const Fraction &);

        // input/output operator
        friend istream &operator>>(istream &, Fraction &);
        friend ostream &operator<<(ostream &, const Fraction &);
    };

}
