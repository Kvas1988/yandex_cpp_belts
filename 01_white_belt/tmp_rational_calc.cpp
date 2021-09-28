#include <iostream>
#include <sstream>
#include <exception>
#include <stdexcept>
using namespace std;

class Rational {
public:
    Rational() {
        p = 0;
        q = 1;
    }

    Rational(int numerator, int denominator) {
        if (denominator == 0) {
            throw invalid_argument("Invalid argument");
            return;
        }
        int grcd = gcd(numerator, denominator);
        p = numerator / grcd;
        q = denominator / grcd;

        if ((p < 0 && q < 0) || (q < 0)) {
            p *= -1;
            q *= -1;
        }
    }

    int Numerator() const {
        return p;
    }

    int Denominator() const {
        return q;
    }

    int gcd(int a, int b) {
        if (b != 0)
            return gcd(b, a % b);
        else
            return a;
    }

private:
    int p;
    int q;
};


bool operator ==(const Rational& r1, const Rational& r2) {
    // return r1.Numerator() / r1.Denominator() == r2.Numerator() / r2.Denominator();
    return (r1.Numerator() == r2.Numerator() && r1.Denominator() == r2.Denominator());
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

Rational operator *(Rational r1, Rational r2) {
    int p = r1.Numerator() * r2.Numerator();
    int q = r1.Denominator() * r2.Denominator();

    return Rational{ p, q };
}

Rational operator /(Rational r1, Rational r2) {
    int p = r1.Numerator() * r2.Denominator();
    int q = r1.Denominator() * r2.Numerator();
    if (q == 0) {
        throw domain_error("Division by zero");
    }

    return Rational{ p, q };
}

istream& operator >>(istream& stream, Rational& r) {
    int n, d;
    char c;
    stream >> n >> c >> d;
    if (stream && c == '/') {
        r = Rational(n, d);
    }
    return stream;
}

ostream& operator <<(ostream& stream, const Rational& r) {
    stream << r.Numerator() << '/' << r.Denominator();
    return stream;

}

// Реализуйте для класса Rational оператор(ы), необходимые для использования его
// в качестве ключа map'а и элемента set'а
bool operator <(const Rational& r1, const Rational& r2) {
    int p1 = r1.Numerator() * r2.Denominator();
    int p2 = r2.Numerator() * r1.Denominator();
    return p1 < p2;
}

int main() {
    //istringstream ex1("1/2 + 1/3");
    //istringstream ex2("1/2 + 5/0");
    //istringstream ex3("4/5 / 0/8");

    Rational r1, r2;
    char op;

    try {
        cin >> r1 >> op >> r2;
    }
    catch (exception& e) {
        cout << e.what();
        return 0;
    }

    if (op == '+') {
        cout << r1 + r2;
    }
    else if (op == '-') {
        cout << r1 - r2;
    }
    else if (op == '/') {
        try {
            cout << r1 / r2;
        }
        catch (exception& e) {
            cout << e.what();
            return 0;
        }
    }
    else if (op == '*') {
        cout << r1 * r2;
    }


    return 0;
}
