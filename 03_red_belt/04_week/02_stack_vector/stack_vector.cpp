#include "stack_vector.h"

#include "test_runner.h"
#include "profile.h"

#include <random>
#include <stdexcept>
using namespace std;

template <typename T, size_t N>
StackVector<T, N>::StackVector(size_t a_size) : size_(a_size) {
    if (size_ > N) {
        throw std::invalid_argument("size is bigger then StackVector's capacity");
    }
}

template <typename T, size_t N>
T& StackVector<T, N>::operator[](size_t index) {
    return data_[index];
}

template <typename T, size_t N>
const T& StackVector<T, N>::operator[](size_t index) const {
    return data_[index];
}

template <typename T, size_t N>
typename std::array<T,N>::iterator StackVector<T, N>::begin() {
    return data_.begin();
}

template <typename T, size_t N>
const typename std::array<T,N>::iterator StackVector<T, N>::begin() const {
    return data_.begin();
}

template <typename T, size_t N>
typename std::array<T,N>::iterator StackVector<T, N>::end() {
    return data_.begin() + size_;
}

template <typename T, size_t N>
const typename std::array<T,N>::iterator StackVector<T, N>::end() const {
    return data_.begin() + size_;
}

template <typename T, size_t N>
size_t StackVector<T, N>::Size() const {
    return size_;
}

template <typename T, size_t N>
size_t StackVector<T, N>::Capacity() const {
    return data_.max_size();
}

template <typename T, size_t N>
void StackVector<T, N>::PushBack(const T &value) {
    if (size_ >= data_.max_size()) {
        throw std::overflow_error("max capacity reached");
    }
    data_[size_++] = value;
}

template <typename T, size_t N>
T StackVector<T, N>::PopBack() {
    if (size_ == 0) {
        throw std::underflow_error("StackVector is empty");
    }
    return data_[--size_];
}

void TestConstruction() {
    StackVector<int, 10> v;
    ASSERT_EQUAL(v.Size(), 0u);
    ASSERT_EQUAL(v.Capacity(), 10u);

    StackVector<int, 8> u(5);
    ASSERT_EQUAL(u.Size(), 5u);
    ASSERT_EQUAL(u.Capacity(), 8u);

    try {
        StackVector<int, 10> u(50);
        Assert(false, "Expect invalid_argument for too large size");
    } catch (invalid_argument&) {
    } catch (...) {
        Assert(false, "Unexpected exception for too large size");
    }
}

void TestPushBack() {
    StackVector<int, 5> v;
    for (size_t i = 0; i < v.Capacity(); ++i) {
        v.PushBack(i);
    }

    try {
        v.PushBack(0);
        Assert(false, "Expect overflow_error for PushBack in full vector");
    } catch (overflow_error&) {
    } catch (...) {
        Assert(false, "Unexpected exception for PushBack in full vector");
    }
}

void TestPopBack() {
    StackVector<int, 5> v;
    for (size_t i = 1; i <= v.Capacity(); ++i) {
        v.PushBack(i);
    }
    for (int i = v.Size(); i > 0; --i) {
        ASSERT_EQUAL(v.PopBack(), i);
    }

    try {
        v.PopBack();
        Assert(false, "Expect underflow_error for PopBack from empty vector");
    } catch (underflow_error&) {
    } catch (...) {
        Assert(false, "Unexpected exception for PopBack from empty vector");
    }
}

int main() {
    {
        TestRunner tr;
        RUN_TEST(tr, TestConstruction);
        RUN_TEST(tr, TestPushBack);
        RUN_TEST(tr, TestPopBack);
    }

    cerr << "Running benchmark..." << endl;
    const size_t max_size = 2500;

    default_random_engine re;
    uniform_int_distribution<int> value_gen(1, max_size);

    vector<vector<int>> test_data(50000);
    for (auto& cur_vec : test_data) {
        cur_vec.resize(value_gen(re));
        for (int& x : cur_vec) {
            x = value_gen(re);
        }
    }

    {
        LOG_DURATION("vector w/o reserve");
        for (auto& cur_vec : test_data) {
            vector<int> v;
            for (int x : cur_vec) {
                v.push_back(x);
            }
        }
    }
    {
        LOG_DURATION("vector with reserve");
        for (auto& cur_vec : test_data) {
            vector<int> v;
            v.reserve(cur_vec.size());
            for (int x : cur_vec) {
                v.push_back(x);
            }
        }
    }
    {
        LOG_DURATION("StackVector");
        for (auto& cur_vec : test_data) {
            StackVector<int, max_size> v;
            for (int x : cur_vec) {
                v.PushBack(x);
            }
        }
    }
    cerr << "Done" << endl;
}
