#include <queue>
#include <set>

#include "test_runner.h"

template<class T>
class ObjectPool {
public:
    T* Allocate() {
        if (deallocated_.empty()) {
            T* ptr =  new T;
            allocated_.insert(ptr);
            return ptr;
        }
        T* result = deallocated_.front();
        deallocated_.pop();
        allocated_.insert(result);
        return result;
    }

    T* TryAllocate() {
        if (deallocated_.empty()) {
            return nullptr;
        }
        T* result = deallocated_.front();
        deallocated_.pop();
        allocated_.insert(result);
        return result;
    }

    void Deallocate(T* object) {
        if (allocated_.find(object) == allocated_.end()) {
            throw new invalid_argument("no object among allocated ones");
        }
        deallocated_.push(object);
        allocated_.erase(object); 
    }

    ~ObjectPool() {
        while (!deallocated_.empty()) {
            auto obj = deallocated_.front();
            deallocated_.pop();
            delete obj;
        }

        for (T* ptr: allocated_) {
            delete ptr;
        }
    };

private:
    std::queue<T*> deallocated_;
    std::set<T*> allocated_;
};


void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}