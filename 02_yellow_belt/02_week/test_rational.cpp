#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        }
        catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
        catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

//class Rational {
//public:
//    // Вы можете вставлять сюда различные реализации,
//    // чтобы проверить, что ваши тесты пропускают корректный код
//    // и ловят некорректный
//
//    Rational();
//    Rational(int numerator, int denominator) {
//    }
//
//    int Numerator() const {
//    }
//
//    int Denominator() const {
//    }
//};

void TestRational() {
    Rational r(4, 9);
    AssertEqual(r.Numerator(), 4, "check rational");
    AssertEqual(r.Denominator(), 9, "check rational");
}

void TestDefaultConstructor() {
    Rational r;
    AssertEqual(r.Numerator(), 0, "check default numerator equal to 0");
    AssertEqual(r.Denominator(), 1, "check default denominator equal to 0");
}

void TestShortenNumbers() {
    Rational r(4, 6);
    AssertEqual(r.Numerator(), 2, "check shorten numerator");
    AssertEqual(r.Denominator(), 3, "check shoretn denominator");
}

void TestNegativeNumerator() {
    Rational r(-4, 6);
    AssertEqual(r.Numerator(), -2, "check negative numerator - numerator");
    AssertEqual(r.Denominator(), 3, "check negative numerator - denominator");
}

void TestNegativeDenominator() {
    Rational r(4, -6);
    AssertEqual(r.Numerator(), -2, "check negative denominator - numerator");
    AssertEqual(r.Denominator(), 3, "check negative denominator - denominator");
}

void TestNegativeBoth() {
    Rational r(-4, -6);
    AssertEqual(r.Numerator(), 2, "check both negative - numerator");
    AssertEqual(r.Denominator(), 3, "check both negative - denominator");
}

void TestZeroNumerator() {
    Rational r(0, 5);
    AssertEqual(r.Numerator(), 0, "check zero numerator - numerator");
    AssertEqual(r.Denominator(), 1, "check zero numerator - denominator");
}

int main() {
    TestRunner runner;
    // добавьте сюда свои тесты
    runner.RunTest(TestRational, "TestRational");
    runner.RunTest(TestDefaultConstructor, "TestDefaultConstructor");
    runner.RunTest(TestShortenNumbers, "TestShortenNumbers");
    runner.RunTest(TestNegativeNumerator, "TestNegativeNumerator");
    runner.RunTest(TestNegativeDenominator, "TestNegativeDenominator");
    runner.RunTest(TestNegativeBoth, "TestNegativeBoth");
    runner.RunTest(TestZeroNumerator, "TestZeroNumerator");

    return 0;
}
