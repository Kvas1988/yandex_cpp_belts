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
    RandomIt elem_mid = elements.begin() + distance(elements.begin(), elements.end()) / 2;

    MergeSort(elements.begin(), elem_mid);
    MergeSort(elem_mid, elements.end());

    //sort(elements.begin(), elem_mid);
    //sort(elem_mid, elements.end());
    merge(elements.begin(), elem_mid, elem_mid, elements.end(), range_begin);
}

int main() {
    vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1 };
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}

// 0 1 4 4 4 6 6 7