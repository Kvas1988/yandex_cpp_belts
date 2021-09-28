#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <string>

using namespace std;

//template <typename RandomIt>
//pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {
//    string l = string{ prefix };
//    auto low = lower_bound(range_begin, range_end, l);
//
//    string r = string{ static_cast<char>(prefix+1) };
//    auto up = lower_bound(range_begin, range_end, r);
//    
//    return { low, up };
//}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string& prefix) {
    auto low = lower_bound(range_begin, range_end, prefix);

    string r = prefix;
    //cout << static_cast<char>(*r.rbegin()+1) << endl;
    *r.rbegin() = static_cast<char>(*r.rbegin() + 1);
    //cout << r << endl;
    auto up = lower_bound(range_begin, range_end, r);

    return { low, up };
}

int main() {
    const vector<string> sorted_strings = { "moscow", "motovilikha", "murmansk" };

    const auto mo_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
    for (auto it = mo_result.first; it != mo_result.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    const auto mt_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
    cout << (mt_result.first - begin(sorted_strings)) << " " <<
        (mt_result.second - begin(sorted_strings)) << endl;

    const auto na_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
    cout << (na_result.first - begin(sorted_strings)) << " " <<
        (na_result.second - begin(sorted_strings)) << endl;

    return 0;
}
