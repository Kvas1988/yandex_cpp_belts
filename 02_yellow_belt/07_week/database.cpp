#include "database.h"
#include "date.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <sstream>

// Database Class

//Database::Database() {};

void Database::Add(const Date& d, const std::string& event) {			
	//if (records[d].count(event) == 0) {
	//	records[d].insert(event);
	//	records_v[d].push_back(event);
	//}
	db[d].Add(event);
}

void Database::Print(std::ostream& os) const {
	//for (const auto& r : records) {
	//	for (const auto& e : r.second) {
	//		os << r.first << ' ' << e << std::endl;
	//	}
	//}

	for (const auto& r : db) {
		for (const auto& event : r.second.GetEvents() ) {
			os << r.first << ' ' << event << std::endl;
		}
	}
}
//std::string Database::Last(const Date& d) const {
//	if (records.empty() || d < records.begin()->first) {
//		throw std::invalid_argument("No entries");
//	}
//
//	auto res = std::prev(records.upper_bound(d));
//	return res->first.DateToStr() + " " + records_v.at(res->first).back();
//}

Entry Database::Last(const Date& d) const {
	auto it = db.upper_bound(d);
	if (it == db.begin()) {
		throw std::invalid_argument("");
	}
	--it;
	return { it->first, it->second.GetEvents().back() };
}


// Operators

std::ostream& operator <<(std::ostream& os, Entry e) {
	os << e.date << ' ' << e.event;
	return os;
}

bool operator ==(Entry lhs, Entry rhs) {
	if (lhs.date == rhs.date && lhs.event == rhs.event) {
		return true;
	}
	else {
		return false;
	}
	
}

bool operator !=(Entry lhs, Entry rhs) {
	if (lhs.date == rhs.date && lhs.event == rhs.event) {
		return false;
	}
	else {
		return true;
	}

}
