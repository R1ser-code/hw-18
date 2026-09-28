#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>

class Fraction {
private:
    int numerator;
    int denominator;

    int gcd(int a, int b) {
        if (a < 0) {
            a = -a;
        }

        if (b < 0) {
            b = -b;
        }

        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }

        return a;
    }

    void reduce() {
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }

        int divisor = gcd(numerator, denominator);

        if (divisor != 0) {
            numerator /= divisor;
            denominator /= divisor;
        }
    }

public:
    Fraction(int numerator, int denominator) {
        if (denominator == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }

        this->numerator = numerator;
        this->denominator = denominator;

        reduce();
    }

    std::string dump() const {
        return std::to_string(numerator) + "/" + std::to_string(denominator);
    }

    bool operator==(const Fraction& other) const {
        return numerator == other.numerator &&
            denominator == other.denominator;
    }

    bool operator!=(const Fraction& other) const {
        return !(*this == other);
    }

    bool operator<(const Fraction& other) const {
        return numerator * other.denominator <
            other.numerator * denominator;
    }

    bool operator>(const Fraction& other) const {
        return other < *this;
    }

    bool operator<=(const Fraction& other) const {
        return !(*this > other);
    }

    bool operator>=(const Fraction& other) const {
        return !(*this < other);
    }

    Fraction operator+(const Fraction& other) const {
        return Fraction(
            numerator * other.denominator +
            other.numerator * denominator,
            denominator * other.denominator
        );
    }

    Fraction operator-(const Fraction& other) const {
        return Fraction(
            numerator * other.denominator -
            other.numerator * denominator,
            denominator * other.denominator
        );
    }

    Fraction operator*(const Fraction& other) const {
        return Fraction(
            numerator * other.numerator,
            denominator * other.denominator
        );
    }

    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            throw std::invalid_argument("Division by zero");
        }

        return Fraction(
            numerator * other.denominator,
            denominator * other.numerator
        );
    }

    Fraction operator-() const {
        return Fraction(-numerator, denominator);
    }

    Fraction& operator++() {
        numerator += denominator;
        reduce();

        return *this;
    }

    Fraction operator++(int) {
        Fraction old = *this;

        numerator += denominator;
        reduce();

        return old;
    }

    Fraction& operator--() {
        numerator -= denominator;
        reduce();

        return *this;
    }

    Fraction operator--(int) {
        Fraction old = *this;

        numerator -= denominator;
        reduce();

        return old;
    }
};

int main() {
    {
        Fraction f1(3, 4);
        Fraction f2(4, 5);

        assert(f1.dump() == "3/4");
        assert(f2.dump() == "4/5");
    }

    {
        Fraction f1(4, 3);
        Fraction f2(6, 11);

        assert(!(f1 == f2));
        assert(f1 != f2);
        assert(!(f1 < f2));
        assert(f1 > f2);
        assert(!(f1 <= f2));
        assert(f1 >= f2);
    }

    {
        Fraction f1(4, 3);
        Fraction f2(8, 6);

        assert(f1 == f2);
        assert(!(f1 != f2));
        assert(!(f1 < f2));
        assert(!(f1 > f2));
        assert(f1 <= f2);
        assert(f1 >= f2);
    }

    {
        Fraction f1(3, 4);
        Fraction f2(4, 5);

        assert((f1 + f2).dump() == "31/20");
        assert((f1 - f2).dump() == "-1/20");
        assert((f1 * f2).dump() == "3/5");
        assert((f1 / f2).dump() == "15/16");

        assert((++f1 * f2).dump() == "7/5");
        assert(f1.dump() == "7/4");

        assert((f1-- * f2).dump() == "7/5");
        assert(f1.dump() == "3/4");
    }

    {
        Fraction f1(2, 3);
        Fraction f2(-2, 3);

        assert((-f1).dump() == "-2/3");
        assert((-f2).dump() == "2/3");
        assert((-f1) == f2);
    }

    {
        Fraction f1(4, 8);
        Fraction f2(2, 4);
        Fraction f3(1, 2);

        assert(f1.dump() == "1/2");
        assert(f2.dump() == "1/2");
        assert(f3.dump() == "1/2");

        assert(f1 == f2);
        assert(f2 == f3);
    }

    {
        Fraction f1(-3, 4);
        Fraction f2(3, -4);
        Fraction f3(-3, -4);

        assert(f1.dump() == "-3/4");
        assert(f2.dump() == "-3/4");
        assert(f3.dump() == "3/4");

        assert(f1 == f2);
        assert(f1 != f3);
    }

    std::cout << "All tests passed!" << std::endl;

    return 0;
}