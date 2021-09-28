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

bool IsPalindrom(const string& str) {
    // Вы можете вставлять сюда различные реализации функции,
    // чтобы проверить, что ваши тесты пропускают корректный код
    // и ловят некорректный
}

void TestPalindrom() {
    //true
    Assert(IsPalindrom(""), "check empty string");
    Assert(IsPalindrom("f"), "check one word");
    Assert(IsPalindrom("assa"), "check even len word");
    Assert(IsPalindrom("qwe ewq"), "check space");
    Assert(IsPalindrom("qwertyuiop[]][poiuytrewq"), "check large word");
    Assert(IsPalindrom("madam"), "check odd len");
    Assert(IsPalindrom(" level "), "test spaces on both side");
    Assert(IsPalindrom("  LEVEL  "), "test two spaces on both side plus upper");
    Assert(IsPalindrom(" l e V e l "), "test spaces between chars");
    //false
    Assert(!IsPalindrom("XlevelY"), "test if first and last char check missing");
    Assert(!IsPalindrom("asXYsa"), "check in mid chars missing");
    Assert(!IsPalindrom("Xlevel"), "test if first char check missing");
    Assert(!IsPalindrom("levelX"), "test if last char check missing");
    Assert(!IsPalindrom("levelX"), "test if last char check missing");
    Assert(!IsPalindrom("levXel"), "test if last char check missing");
    Assert(!IsPalindrom("qwer tyu iop[]][poi uytre wq"), "check random spaces in a true palindrom");   
    Assert(!IsPalindrom(" madam"), "test left space");
    Assert(!IsPalindrom("  madam"), "test two left space");
    Assert(!IsPalindrom("madam "), "test right space");
    Assert(!IsPalindrom("madam  "), "test two right space");
}



int main() {
    TestRunner runner;
    // добавьте сюда свои тесты
    runner.RunTest(TestPalindrom, "TestPalindrom");
    return 0;
}
