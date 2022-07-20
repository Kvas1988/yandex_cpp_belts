#pragma once

#include <array>
#include <stdexcept>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    typename std::array<T,N>::iterator begin();
    typename std::array<T,N>::iterator end();
    const typename std::array<T,N>::iterator begin() const;
    const typename std::array<T,N>::iterator end() const;

    size_t Size() const;
    size_t Capacity() const;

    void PushBack(const T& value);
    T PopBack();

private:
    std::array<T, N> data_;
    size_t size_;
};

