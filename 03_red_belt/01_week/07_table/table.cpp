#include "test_runner.h"

#include <vector>

// using namespace std;

// Реализуйте здесь шаблонный класс Table
template <typename T>
class Table {
public:
    Table(size_t rows, size_t columns) {
        Resize(rows, columns);
    }

    void Resize(size_t new_rows, size_t new_columns) {
        data_.resize(new_rows);
        for (vector<T> rows : data_) {
            rows.resize(new_columns);
        }
    }

    pair<size_t, size_t> Size() const {
        return {data_.size(), (data_.empty() ? 0 : data_[0].size())};
    }

    vector<T>& operator [](size_t idx) { return data_[idx]; }
    const vector<T>& operator [](size_t idx) const { return data_[idx]; }

private:
    std::vector<std::vector<T>> data_;
};

void TestTable() {
  Table<int> t(1, 1);
  pair<size_t , size_t> size = t.Size();
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}