#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

#include "date.h"

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

class Database {
public:
	Database() {}

	void Add(const Date& d, const std::string& event);
	void Print(std::ostream& os) const;

	//template <typename Predicat>
	//int RemoveIf(Predicat predicate) {
	//	int count = 0;

	//	for (auto it = records_v.begin(); it != records_v.end(); ) {
	//		Date date = it->first;
	//		auto events = it->second;

	//		auto rem_it = std::remove_if(events.begin(), events.end(),
	//			[=](const std::string& event) { return predicate(date, event); });

	//		auto len = std::distance(rem_it, events.end());
	//		count += len;
	//		auto next_it = next(it);
	//		if (len == events.size()) {
	//			records_v.erase(date);
	//		}
	//		else {
	//			events.erase(rem_it, events.end());
	//			// records[date] = { events.begin(), events.end() };
	//		}
	//		it = next_it;
	//	}

	//	for (auto it = records.begin(); it != records.end(); ) {
	//		Date date = it->first;
	//		auto events = it->second;

	//		auto rem_it = std::remove_if(events.begin(), events.end(),
	//			[=](const std::string& event) { return predicate(date, event); });

	//		auto len = std::distance(rem_it, events.end());
	//		count += len;
	//		auto next_it = next(it);
	//		if (len == events.size()) {
	//			records.erase(date);
	//		}
	//		else {
	//			events.erase(rem_it, events.end());
	//			// records[date] = { events.begin(), events.end() };
	//		}
	//		it = next_it;
	//	}

	//	return count;
	//}

	template <typename Predicat> 
	int RemoveIf(Predicat predicate) {
		int count = 0;
		std::map<Date, std::vector<std::string>::iterator> to_delete;

		for (auto& rv : records_v) {
			Date date = rv.first;
			std::vector<std::string> events = rv.second;

			auto del_it = std::stable_partition(events.begin(), events.end(),
				[=](const std::string& event) {return !predicate(date, event); });

			to_delete[date] = del_it;
		}

		for (auto& i : to_delete) {
			Date date = i.first;
			auto del_it = i.second;

			count += records_v[date].end() - del_it;
			records_v[date].erase(del_it, records_v[date].end());
			records[date] = std::set<std::string>(records_v[date].begin(), records_v[date].end());
			if (records_v[date].empty()) {
				records.erase(date);
				records_v.erase(date);
			}
		}

		return count;
	}

	/*template <typename Predicat> 
	int RemoveIf(Predicat predicate) {
		int count = 0;
		for (auto& rv : records_v) {
			auto it = std::remove_if(rv.second.begin(), rv.second.end(),
				[=](std::string e) {return predicate(rv.first, e); });
			count += std::distance(it, rv.second.end());
			rv.second.erase(it, rv.second.end());
		}

		for (auto it = records.begin(); it != records.end(); ) {
			for (auto i = it->second.begin(); i != it->second.end(); ) {
				auto next_i = next(i);
				if (predicate(it->first, *i)) {
					it->second.erase(*i);
				}
				i = next_i;
				if (it->second.empty()) {
					break;
				}
			}
			auto netxt_it = next(it);
			if (it->second.size() == 0) {
				records.erase(it->first);
			}
			it = netxt_it;
			if (records.empty()) {
				break;
			}
		}
		return (count);
	}*/
	 
	template <typename Predicat>
	std::vector<Entry> FindIf(Predicat predicate) const {
		std::vector<Entry> res;

		for (auto r : records_v) {
			for (auto e : r.second) {
				if (predicate(r.first, e)) {										
					res.push_back({ r.first, e });
				}
			}
		}
		return res;
	}
	
	std::string Last(const Date& d) const;

	//std::vector<Record> records;
private:
	std::map<Date, std::set<std::string>> records;
	std::map<Date, std::vector<std::string>> records_v;
};

std::ostream& operator <<(std::ostream& os, Entry e);