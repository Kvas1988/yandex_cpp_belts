#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <string>
#include <deque>

using namespace std;

void MakeAction(deque<string>& d, const string& s2) {
    d.push_front("(");
    d.push_back(") ");
    d.push_back(s2);
}

int main() {
    deque<string> res;
    string a;
    int n;
    cin >> a >> n;
    res.push_back(a);

    cin.ignore();
    for (int i = 0; i < n; ++i) {
        string addAction;
        getline(cin, addAction, '\n');
        MakeAction(res, addAction);
    }

    for (const auto& item : res) {
        cout << item;
    }

    return 0;
}

//void MakeAction(string& s1, const string& s2) {
//    s1.insert(0, "(");
//    //s1.push_back(') ');
//    s1 = s1 + ") " + s2;
//    //s1 += s2;
//    //return s;
//}

//int main() {
//    string res;
//    cin >> res;
//   
//    int actions;
//    cin >> actions;
//    cin.ignore();
//    for (int i = 0; i < actions; ++i) {
//        string addAction;
//        getline(cin, addAction, '\n');
//        MakeAction(res, addAction);
//    }
//
//    cout << res;
//    return 0;
//}
