#pragma once

#include <iostream>
#include <iomanip>

class Date {
public:	
	Date() {
		year_ = 0;
		month_ = 0;
		day_ = 0;
	}

	Date(int y, int m, int d) : year_(y), month_(m), day_(d) {}

	int GetDay() const;
	int GetMonth() const;
	int GetYear() const;

	std::string DateToStr() const;

private:
	int year_, month_, day_;
	/*int year_ = 0;
	int month_ = 0;
	int day_ = 0;*/
};

Date ParseDate(std::istream& is);

// Operators

std::ostream& operator <<(std::ostream& os, Date d);

bool operator == (Date lhs, Date rhs);
bool operator < (Date lhs, Date rhs);
bool operator <= (Date lhs, Date rhs);
bool operator > (Date lhs, Date rhs);
bool operator >= (Date lhs, Date rhs);
bool operator !=(Date lhs, Date rhs);

// Tests
void TestParseDate();