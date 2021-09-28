#include "phone_number.h"
#include <string>
#include <sstream>
#include <stdexcept>

 PhoneNumber::PhoneNumber(const string& international_number) {
	stringstream stream(international_number);
	string country_c, city_c, local_n;
	if (stream) {
		getline(stream, country_c, '-');
		getline(stream, city_c, '-');
		getline(stream, local_n, '\n');
	}

	// country_code check
	if (country_c[0] != '+') {
		throw invalid_argument("");
	}
	string tmp;
	for (int i = 1; i < country_c.size(); i++) {
		tmp += country_c[i];
	}
	country_code_ = tmp;

	// city_code check 
	if (city_c.empty()) {
		throw invalid_argument("");
	}
	city_code_ = city_c;

	// local_number check
	if (local_n.empty()) {
		throw invalid_argument("");
	}
	local_number_ = local_n;
}

string PhoneNumber::GetCountryCode() const {
	return country_code_;
}

string PhoneNumber::GetCityCode() const {
	return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
	return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
	string res = "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
	return res;
}