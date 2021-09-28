#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <string>
#include <deque>

using namespace std;

struct Operation {
    char op_type = 0;
    int num = 0;
};

void AddAction(deque<string>& exp, const Operation& new_operation, const char& last_op_type) {
    if ((last_op_type == '+' || last_op_type == '-') &&
        (new_operation.op_type == '*' || new_operation.op_type == '/')) {
        exp.push_front("(");
        exp.push_back(")");
    }
    exp.push_back(" ");
    exp.push_back(string{ new_operation.op_type });
    exp.push_back(" ");
    exp.push_back(to_string(new_operation.num));    
}

int main() {
    
    int first_num, n;
    cin >> first_num >> n;

    vector<Operation> opers(n);    
    for (int i = 0; i < n; ++i) {
        cin >> opers[i].op_type;
        cin >> opers[i].num;
    }

    deque<string> exp;
    exp.push_back(to_string(first_num));
    char last_op_type = '*';
    for (const auto& operation : opers) {
        AddAction(exp, operation, last_op_type);
        last_op_type = operation.op_type;
    }

    copy(exp.begin(), exp.end(), ostream_iterator<string>(cout));

    return 0;
}
