#include <iostream>
#include <string>
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
    int numerator1;
    int denominator1;
    int numerator2;
    int denominator2;

    std::cout << "Enter numerator of fraction 1: ";
    std::cin >> numerator1;

    std::cout << "Enter denominator of fraction 1: ";
    std::cin >> denominator1;

    std::cout << "Enter numerator of fraction 2: ";
    std::cin >> numerator2;

    std::cout << "Enter denominator of fraction 2: ";
    std::cin >> denominator2;

    try {
        Fraction f1(numerator1, denominator1);
        Fraction f2(numerator2, denominator2);

        std::cout << std::endl;

        std::cout << "Fraction 1 = " << f1.dump() << std::endl;
        std::cout << "Fraction 2 = " << f2.dump() << std::endl;

        std::cout << std::endl;

        std::cout << "Comparison:" << std::endl;

        std::cout << "f1"
            << ((f1 == f2) ? " == " : " not == ")
            << "f2" << std::endl;

        std::cout << "f1"
            << ((f1 != f2) ? " != " : " not != ")
            << "f2" << std::endl;

        std::cout << "f1"
            << ((f1 < f2) ? " < " : " not < ")
            << "f2" << std::endl;

        std::cout << "f1"
            << ((f1 > f2) ? " > " : " not > ")
            << "f2" << std::endl;

        std::cout << "f1"
            << ((f1 <= f2) ? " <= " : " not <= ")
            << "f2" << std::endl;

        std::cout << "f1"
            << ((f1 >= f2) ? " >= " : " not >= ")
            << "f2" << std::endl;

        std::cout << std::endl;

        std::cout << "Arithmetic:" << std::endl;

        std::cout << f1.dump() << " + " << f2.dump()
            << " = " << (f1 + f2).dump() << std::endl;

        std::cout << f1.dump() << " - " << f2.dump()
            << " = " << (f1 - f2).dump() << std::endl;

        std::cout << f1.dump() << " * " << f2.dump()
            << " = " << (f1 * f2).dump() << std::endl;

        std::cout << f1.dump() << " / " << f2.dump()
            << " = " << (f1 / f2).dump() << std::endl;

        std::cout << std::endl;

        std::cout << "Unary minus:" << std::endl;

        std::cout << "-" << f1.dump()
            << " = " << (-f1).dump() << std::endl;

        std::cout << "-" << f2.dump()
            << " = " << (-f2).dump() << std::endl;

        std::cout << std::endl;

        std::string oldF1 = f1.dump();

        Fraction prefixResult = ++f1;

        std::cout << "++" << oldF1
            << " = " << prefixResult.dump() << std::endl;

        std::cout << "Fraction 1 = "
            << f1.dump() << std::endl;

        oldF1 = f1.dump();

        Fraction postfixResult = f1--;

        std::cout << oldF1 << "-- returns "
            << postfixResult.dump() << std::endl;

        std::cout << "Fraction 1 = "
            << f1.dump() << std::endl;
    }
    catch (const std::invalid_argument& error) {
        std::cout << "Error: " << error.what() << std::endl;
    }

    return 0;
}