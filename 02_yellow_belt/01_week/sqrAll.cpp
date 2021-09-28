#include <string>
#include <iostream>
#include <cstdint>
#include <vector>
#include <map>
#include <algorithm>
#include <tuple>

using namespace std;

template <typename T> T Sqr(T x);
template <typename Col> Col operator *(Col first, Col second);

template <typename Key, typename Value>
map<Key, Value> operator *(const map<Key, Value> m1, map<Key, Value> m2);

template <typename First, typename Second>
pair<First, Second> operator * (const pair<First, Second> p1, const pair<First, Second> p2);

// =============================================
template <typename T> 
T Sqr(const T x) {
    return x * x;
}

template <typename Col>
Col operator *(Col first, Col second) {
    Col res;
    for (size_t i = 0; i < first.size(); ++i) {
        res.push_back(first[i] * second[i]);
    }
    return res;
}

template <typename Key, typename Value>
map<Key, Value> operator *(const map<Key, Value> m1, const map<Key, Value> m2) {
    map<Key, Value> res;
    for (const auto& i : m1) {
        res[i.first] = i.second * i.second; // without m2
    }
    return res;
}

template <typename First, typename Second>
pair<First, Second> operator * (const pair<First, Second> p1, const pair<First, Second> p2) {
    return make_pair(p1.first * p2.first, p1.second * p2.second);    
}


int main() {
    // Пример вызова функции
    vector<int> v = { 1, 2, 3 };
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, int> p = { {1,5}, {3,6}, {7,2} };
    cout << "map: ";
    for (auto i : Sqr(p)) {
        cout << i.first << ": " << i.second << ", ";
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
      {4, {2, 2}},
      {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
}