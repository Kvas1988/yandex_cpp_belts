#include "test_runner.h"
#include <vector>
#include <future>
#include <functional>
#include <numeric>
using namespace std;

int64_t CalculateMatrixSumNotOptimal(const vector<vector<int>>& matrix) {
    int64_t result = 0;
    std::vector<std::future<int64_t>> futures;

    // not optimal, because we produce threads_num == row_num
    for (const std::vector<int>& row : matrix) {
        futures.push_back(std::async([row] {
           int64_t row_result = 0;
           for (int value : row) {
               row_result += value;
           }
            return row_result;
        }));
    }

    for (auto& f : futures) {
        result += f.get();
    }

    return result;
}

int64_t CalculateMatrixSingleThread(const std::vector<std::vector<int>>& matrix) {
    int64_t result = 0;
    for (const std::vector<int> row : matrix) {
        for (int value : row) {
            result += value;
        }
    }
    return result;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
    int len = matrix.end() - matrix.begin();
    int iter_step = std::ceil(len / 4.0);

    std::vector<std::future<int64_t>> futures;
    std::vector<std::vector<int>>::const_iterator it = matrix.begin();
    while (it != matrix.end()) {
        std::vector<std::vector<int>>::const_iterator end = std::min(it + iter_step, matrix.end());
        futures.push_back(std::async([it, end] {
            return CalculateMatrixSingleThread({it, end});
        }));

        it = end;
    }

    int64_t result = 0;
    for (auto& f : futures) {
        result += f.get();
    }

    return result;
}

void TestCalculateMatrixSum() {
    const vector<vector<int>> matrix = {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 14, 15, 16},

            {1, 2, 3, 4},
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 14, 15, 16}
    };
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 282);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestCalculateMatrixSum);
}
