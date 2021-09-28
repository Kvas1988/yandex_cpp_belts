#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

#include "date.h"
#include "eventtype.h"

struct Entry {
public:
	//Entry() {};
	Entry(Date d, std::string e) : date(d), event(e) {}

public:
	Date date;
	std::string event;
};

std::ostream& operator <<(std::ostream& os, Entry e);
bool operator ==(Entry lhs, Entry rhs);
bool operator !=(Entry lhs, Entry rhs);

class Database {
public:
	Database() {}

	void Add(const Date& d, const std::string& event);
	void Print(std::ostream& os) const;

	template <typename Predicat>
	int RemoveIf(Predicat predicate) {
		int count = 0;

		for (auto& r : db) {
			const Date& date = r.first;
			count += r.second.RemoveIf([=](const std::string& event) {
				return predicate(date, event); 
				});
		}
		for (auto it = db.begin(); it != db.end(); ) {
			if (it->second.GetEvents().empty()) {
				it = db.erase(it);
			}
			else {
				++it;
			}
		}

		return count;
	}
	 
	template <typename Predicat>
	std::vector<Entry> FindIf(Predicat predicate) const {
		std::vector<Entry> res;

		for (auto r : db) {
			for (auto e : r.second.GetEvents()) {
				if (predicate(r.first, e)) {										
					res.push_back({ r.first, e });
				}
			}
		}
		return res;
	}
	
	Entry Last(const Date& d) const;

	//std::vector<Record> records;
private:
	//::map<Date, std::set<std::string>> records;
	//std::map<Date, std::vector<std::string>> records_v;
	std::map<Date, EventType> db;
};

std::ostream& operator <<(std::ostream& os, Entry e);

// Tests
void TestDatabaseAddAndPrint();
void TestDatabaseFind();
void TestDatabaseRemove();
void TestDatabaseLast();