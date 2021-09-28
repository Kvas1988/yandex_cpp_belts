#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <exception>

using namespace std;

template <typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& m, Key k) {
    if (m.count(k) > 0) {
        return m[k];
    }
    throw runtime_error("err");
}

int main() {
    map<int, string> m = { {0, "value"} };
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl; // выведет newvalue
}