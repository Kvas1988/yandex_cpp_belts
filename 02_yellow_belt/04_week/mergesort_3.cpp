#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (distance(range_begin, range_end) < 2) {
        return;
    }

    vector<typename RandomIt::value_type> elements(range_begin, range_end);
    auto dst3 = distance(elements.begin(), elements.end()) / 3;
    RandomIt elem_mid1 = elements.begin() + dst3;
    RandomIt elem_mid2 = elem_mid1 + dst3;

    MergeSort(elements.begin(), elem_mid1);
    MergeSort(elem_mid1, elem_mid2);
    MergeSort(elem_mid2, elements.end());

    //sort(elements.begin(), elem_mid);
    //sort(elem_mid, elements.end());
    vector<typename RandomIt::value_type> tmp;
    merge(elements.begin(), elem_mid1, elem_mid1, elem_mid2, back_inserter(tmp));
    merge(tmp.begin(), tmp.end(), elem_mid2, elements.end(), range_begin);
}

int main() {
    vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1, 5 };
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}

// 0 1 4 4 4 6 6 7