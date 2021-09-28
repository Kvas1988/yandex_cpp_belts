#include <iostream>
using namespace std;

class Rational {
public:
    Rational() {
        // Реализуйте конструктор по умолчанию
        p = 0;
        q = 1;
    }

    Rational(int numerator, int denominator) {
        // Реализуйте конструктор
        int grcd = gcd(numerator, denominator);
        p = numerator / grcd;
        q = denominator / grcd;
    }

    int Numerator() const {
        // Реализуйте этот метод
        return p;
    }

    int Denominator() const {
        // Реализуйте этот метод
        return q;
    }

    int gcd(int a, int b) {
        if (b != 0)
            return gcd(b, a % b);
        else
            return a;
    }

private:
    // Добавьте поля
    int p;
    int q;
};

// Реализуйте для класса Rational операторы ==, + и -
bool operator ==(Rational r1, Rational r2) {
    return r1.Numerator() / r1.Denominator() == r2.Numerator() / r2.Denominator();
}

Rational operator +(Rational r1, Rational r2) {
    int p1 = r1.Numerator() * r2.Denominator();
    int q1 = r1.Denominator() * r2.Denominator();
    int p2 = r2.Numerator() * r1.Denominator();

    return Rational{ p1 + p2, q1 };
}

Rational operator -(Rational r1, Rational r2) {
    int p1 = r1.Numerator() * r2.Denominator();
    int q1 = r1.Denominator() * r2.Denominator();
    int p2 = r2.Numerator() * r1.Denominator();

    return Rational{ p1 - p2, q1 };
}

int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
