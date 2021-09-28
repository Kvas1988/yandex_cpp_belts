#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <vector>
using namespace std;

class Rational {
public:
    Rational() {
        p = 0;
        q = 1;
    }

    Rational(int numerator, int denominator) {
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

    return Rational{ p, q };
}


//istream& operator >>(istream& stream, Rational& r) {
//    // input1("1*2"), input2("1/"), input3("/4")
//    if (stream.eof()) {
//        return stream;
//    }
//    else {
//        int n, d;
//        stream >> n;      
//        stream.ignore(1);        
//        stream >> d;
//        r = Rational{ n, d };
//
//        return stream;
//    }
//}

istream& operator >>(istream& stream, Rational& r) {
    int n, d;
    char c;
    stream >> n >> c >>d;
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
    //    if (r1.Numerator()/r1.Denominator() < r2.Numerator()/r2.Denominator())
    //    {
    //        return true;
    //    }
    //    else {
    //        return false;
    //    }

    int p1 = r1.Numerator() * r2.Denominator();
    //    int q1 = r1.Denominator() * r2.Denominator();
    int p2 = r2.Numerator() * r1.Denominator();
    return p1 < p2;

}

int main() {    
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("");
        Rational r;
        //cout << input.peek();
        bool correct = !(input >> r);
        // cout << r; // test
        // cout << correct << endl;
        if (!correct) {
            cout << "Read from empty stream works incorrectly" << endl;
            return 3;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 4;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 5;
        }
    }

    {
        istringstream input1("1*2"), input2("1/"), input3("/4");
        Rational r1, r2, r3;
        input1 >> r1;
        input2 >> r2;
        input3 >> r3;
        bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
        if (!correct) {
            cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
                << r1 << " " << r2 << " " << r3 << endl;

            return 6;
        }
    }

    // map test
    {
        const set<Rational> rs = { {1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2} };
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{ {1, 25}, { 1, 2 }, { 3, 4 }}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
