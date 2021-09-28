#include <iostream>
using namespace std;

class Rational {
public:
    Rational() {
        // ���������� ����������� �� ���������
        p = 0;
        q = 1;
    }

    Rational(int numerator, int denominator) {
        // ���������� �����������
        int grcd = gcd(numerator, denominator);
        p = numerator / grcd;
        q = denominator / grcd;
    }

    int Numerator() const {
        // ���������� ���� �����
        return p;
    }

    int Denominator() const {
        // ���������� ���� �����
        return q;
    }

    int gcd(int a, int b) {
        if (b != 0)
            return gcd(b, a % b);
        else
            return a;
    }

private:
    // �������� ����
    int p;
    int q;
};


// �������� ���� ���������� operator == ��� ������ Rational �� ������ �����
// ���������� ��� ������ Rational ��������� ==, + � -
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

// ���������� ��� ������ Rational ��������� * � /
Rational operator *(Rational r1, Rational r2) {
    int p = r1.Numerator() * r2.Numerator();
    int q = r1.Denominator() * r2.Denominator();

    return Rational{ p, q };
}

// ���������� ��� ������ Rational ��������� * � /
Rational operator /(Rational r1, Rational r2) {
    int p = r1.Numerator() * r2.Denominator();
    int q = r1.Denominator() * r2.Numerator();

    return Rational{ p, q };
}

int main() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}
