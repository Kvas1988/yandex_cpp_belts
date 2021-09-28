#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;


int main() {
    int n;
    cin >> n;

    vector<int> v;
    for (int i = 1; i <= n; i++) {
        v.push_back(i);
    }
    //sort(v.begin(), v.end());

    vector<vector<int>> output;
    do {
        output.push_back({ v.begin(), v.end() });
    } while (next_permutation(v.begin(), v.end()));

    reverse(output.begin(), output.end());
    for (auto& vector : output) {
        copy(vector.begin(), vector.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
    
    return 0;
}