#include "simple_vector.h"
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

template <typename T>
SimpleVector<T>::SimpleVector(size_t size) :
    capacity_(size),
    size_(size),
    data_(new T[size])
    {}

template <typename T>
SimpleVector<T>::SimpleVector() :
    capacity_(0),
    size_(0),
    data_(nullptr)
    {}

template <typename  T>
SimpleVector<T>::~SimpleVector() { delete[] data_; }

template <typename T>
T& SimpleVector<T>::operator[](size_t index) { return data_[index]; }

template <typename T>
T* SimpleVector<T>::begin() { return data_; }

template <typename T>
T* SimpleVector<T>::end() { return data_ + size_; }

template <typename T>
size_t SimpleVector<T>::Size() const { return size_; }

template <typename T>
size_t SimpleVector<T>::Capacity() const { return capacity_; }

template <typename T>
void SimpleVector<T>::PushBack(const T &value) {
    if (size_ == capacity_) {
        capacity_ = capacity_ == 0 ? 1: capacity_ * 2;
        T* new_data = new T[capacity_];
        std::copy(begin(), end(), new_data);
        delete[] data_; // !!!
        data_ = new_data;
    }

    data_[size_++] = value;
}

void TestConstruction() {
    SimpleVector<int> empty;
    ASSERT_EQUAL(empty.Size(), 0u);
    ASSERT_EQUAL(empty.Capacity(), 0u);
    ASSERT(empty.begin() == empty.end());

    SimpleVector<string> five_strings(5);
    ASSERT_EQUAL(five_strings.Size(), 5u);
    ASSERT(five_strings.Size() <= five_strings.Capacity());
    for (auto& item : five_strings) {
        ASSERT(item.empty());
    }
    five_strings[2] = "Hello";
    ASSERT_EQUAL(five_strings[2], "Hello");
}

void TestPushBack() {
    SimpleVector<int> v;
    for (int i = 10; i >= 1; --i) {
        v.PushBack(i);
        ASSERT(v.Size() <= v.Capacity());
    }
    sort(begin(v), end(v));

    const vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_EQUAL(v.Size(), expected.size());
    ASSERT(equal(begin(v), end(v), begin(expected)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestConstruction);
    RUN_TEST(tr, TestPushBack);
    return 0;
}
