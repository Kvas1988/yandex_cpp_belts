//#include "test_runner.h"

#include <vector>
#include <stdexcept>
#include <exception>
#include <iostream>

using namespace std;

template <typename T>
class Deque {
public:
    Deque(size_t num=0) {
        if (num != 0) {
            vBack.resize(num);
            vFront.resize(0);
        }
    }
    
    bool Empty() const {
        return (vFront.empty() && vBack.empty());
    }
    
    size_t Size() const {
        return vFront.size() + vBack.size();
    }
    
    const T& operator[] (size_t index) const {
        size_t size = vFront.size();
        return (index < size) ? vFront[size-1-index] : vBack[index - size];
    }
    
    T& operator[] (size_t index) {
        size_t size = vFront.size();
        return (index < size) ? vFront[size-1-index] : vBack[index - size];
    }
    
    const T& At(size_t index) const {
        if (index > Size()) {
            throw out_of_range("out of range");
        }
        size_t size = vFront.size();
        return (index < size) ? vFront[size-1-index] : vBack[index - size];
    }
    
    T& At(size_t index) {
        if (index > Size()) {
            throw out_of_range("out of range");
        }
        size_t size = vFront.size();
        return (index < size) ? vFront[size-1-index] : vBack[index - size];
    }
    
    const T& Front() const {
        return (vFront.empty()) ? vBack.front() : vFront.back();
    }
    
    T& Front() {
        return (vFront.empty()) ? vBack.front() : vFront.back();
    }
    
    const T& Back() const {
        return (vBack.empty()) ? vFront.front() : vBack.back();
    }
    
    T& Back() {
        return (vBack.empty()) ? vFront.front() : vBack.back();
    }
    
    void PushFront(T value) {
        vFront.push_back(value);
    }
    
    void PushBack(T value) {
        vBack.push_back(value);
    }
       
private:
    vector<T> vFront;
    vector<T> vBack;
};


int main() {
  return 0;
}


