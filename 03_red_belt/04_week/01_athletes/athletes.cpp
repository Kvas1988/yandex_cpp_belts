#include <list>
#include <vector>
#include <iostream>

int main() {
    int n;
    std::cin >> n;
    std::list<int> athletes;
    std::vector<std::list<int>::iterator> iters(n, athletes.end());

    int num, stand_before;
    for (size_t i = 0; i < n; i++) {
        std::cin >> num >> stand_before;
        iters[num] = athletes.insert(iters[stand_before], num);
    }

    for (int num : athletes) {
        std::cout << num << '\n';
    }

    return 0;
}