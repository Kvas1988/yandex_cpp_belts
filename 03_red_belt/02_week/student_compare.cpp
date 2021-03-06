#include "student.h"
#include "test_runner.h"
#include "profile.h"
#include <algorithm>

using namespace std;

bool Compare(const Student& first, const Student& second) {
    //LOG_DURATION("std compare")
//    return first.Less(second);
    
    return first.rating > second.rating;
}

//void TestComparison() {
//  Student newbie {
//    "Ivan", "Ivanov", {
//      {"c++", 1.0},
//      {"algorithms", 3.0}
//    },
//    2.0
//  };
//
//  Student cpp_expert {
//    "Petr", "Petrov", {
//      {"c++", 9.5},
//      {"algorithms", 6.0}
//    },
//    7.75
//  };
//
//  Student guru {
//    "Sidor", "Sidorov", {
//      {"c++", 10.0},
//      {"algorithms", 10.0}
//    },
//    10.0
//  };
//  ASSERT(Compare(guru, newbie));
//  ASSERT(Compare(guru, cpp_expert));
//  ASSERT(!Compare(newbie, cpp_expert));
//}
//
//void TestSorting() {
//  vector<Student> students {
//    {"Sidor", "Sidorov", {{"maths", 2.}}, 2.},
//    {"Semen", "Semenov", {{"maths", 4.}}, 4.},
//    {"Ivan", "Ivanov", {{"maths", 5.}}, 5.},
//    {"Petr", "Petrov", {{"maths", 3.}}, 3.},
//    {"Alexander", "Alexandrov", {{"maths", 1.}}, 1.}
//  };
//  sort(students.begin(), students.end(), Compare);
//  ASSERT(is_sorted(students.begin(), students.end(),
//    [](Student first, Student second) {
//      return first.Less(second);
//    })
//  );
//}
//
//void MassTest() {
//    vector<Student> students;
//    for (int i = 0; i < 1000000; i++) {
//        double rating = static_cast<double>(random()*10);
//        Student stud  {"Sidor", "Sidorov", {{"maths", 2.}}, rating};
//        students.push_back(stud);
//    }
//
//    {
//        LOG_DURATION("MassTest");
////        for (auto it = next(students.begin()); it != students.end(); it++) {
////            Compare(*it, *(it--));
////        }
//        for (int i = 1; i < students.size(); i++) {
//            Compare(students[i-1], students[i]);
//        }
//
//    }
//}
//
//int main() {
////    LOG_DURATION("Total");
//    TestRunner tr;
//    RUN_TEST(tr, TestComparison);
//    RUN_TEST(tr, TestSorting);
////    MassTest();
//    return 0;
//}
