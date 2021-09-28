#include "date.h"

#include <iostream>
#include <string>
#include <sstream>
#include <tuple>
#include <stdexcept>

// Date Class

int Date::GetDay() const {
	return day_;
}
int Date::GetMonth() const {
	return month_;
}
int Date::GetYear() const {
	return year_;
}

std::string Date::DateToStr() const {
	std::stringstream ss;
	ss << *this;
	return ss.str();
}

// Utility Functions

Date ParseDate(std::istream& is) {
	int y, m, d;
	is >> y;
	is.ignore(1);
	is >> m;
	is.ignore(1);
	is >> d;
	return Date(y, m, d);
}

std::ostream& operator <<(std::ostream& os, Date d) {
	os << std::setw(4) << std::setfill('0') << d.GetYear() << '-'
		<< std::setw(2) << std::setfill('0') << d.GetMonth() << '-'
		<< std::setw(2) << std::setfill('0') << d.GetDay();
	return os;
}

bool operator == (Date lhs, Date rhs) {
	return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) ==
		std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator < (Date lhs, Date rhs) {
	return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <
		std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator <= (Date lhs, Date rhs) {
	return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <=
		std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator > (Date lhs, Date rhs) {
	return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) >
		std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator >= (Date lhs, Date rhs) {
	return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <=
		std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator !=(Date lhs, Date rhs) {
	return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) !=
		std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}