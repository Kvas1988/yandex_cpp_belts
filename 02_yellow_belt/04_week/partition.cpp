#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

void PrintStats(vector<Person> persons) {
    cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << endl;

    //women
    auto it = partition(persons.begin(), persons.end(), [](Person p) { return p.gender == Gender::FEMALE; });
    cout << "Median age for females = " << ComputeMedianAge(persons.begin(), it) << endl;

    //men
    it = partition(persons.begin(), persons.end(), [](Person p) { return p.gender == Gender::MALE; });
    cout << "Median age for males = " << ComputeMedianAge(persons.begin(), it) << endl;

    //employed females
    it = partition(persons.begin(), persons.end(), [](Person p) { return p.gender == Gender::FEMALE & p.is_employed; });
    cout << "Median age for employed females = " << ComputeMedianAge(persons.begin(), it) << endl;

    //unemployed females
    it = partition(persons.begin(), persons.end(), [](Person p) { return p.gender == Gender::FEMALE & !p.is_employed; });
    cout << "Median age for unemployed females = " << ComputeMedianAge(persons.begin(), it) << endl;

    //employed males
    it = partition(persons.begin(), persons.end(), [](Person p) { return p.gender == Gender::MALE & p.is_employed; });
    cout << "Median age for employed males = " << ComputeMedianAge(persons.begin(), it) << endl;

    //unemployed males
    it = partition(persons.begin(), persons.end(), [](Person p) { return p.gender == Gender::MALE & !p.is_employed; });
    cout << "Median age for unemployed males = " << ComputeMedianAge(persons.begin(), it) << endl;
}
