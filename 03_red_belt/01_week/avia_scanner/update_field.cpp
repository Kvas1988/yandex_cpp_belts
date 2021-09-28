#include "test_runner.h"
#include "airline_ticket.h"

#include <algorithm>
#include <numeric>
#include <vector>
#include <tuple>
#include <iomanip>
using namespace std;

// funcs to make tuples
tuple<int, int, int> DateTuple(const Date& date) {
    return make_tuple(date.year, date.month, date.day);
}

tuple<int, int> TimeTuple(const Time& time) {
    return make_tuple(time.hours, time.minutes);
}

// Date and Time operators
bool operator <(const Time& lhs, const Time& rhs) {
    return TimeTuple(lhs) < TimeTuple(rhs);
}

bool operator <(const Date& lhs, const Date& rhs) {
    return DateTuple(lhs) < DateTuple(rhs);
}

bool operator ==(const Date& lhs, const Date& rhs) {
    return DateTuple(lhs) == DateTuple(rhs);
}

bool operator ==(const Time& lhs, const Time& rhs) {
    return TimeTuple(lhs) == TimeTuple(rhs);
}

ostream& operator <<(ostream& os, Date d) {
    os << setw(4) << setfill('0') << d.year << '-'
        << setw(2) << setfill('0') << d.month << '-'
        << setw(2) << setfill('0') << d.day;
    return os;
}

ostream& operator <<(ostream& os, Time t) {
    os << setw(2) << setfill('0') << t.hours << ':'
        << setw(2) << setfill('0') << t.minutes;
    return os;
}

istream& operator >>(istream& is, Time& t) {
    is >> t.hours;
    is.ignore(1);
    is >> t.minutes;
    return is;
}

istream& operator >>(istream& is, Date& d) {
    is >> d.year;
    is.ignore(1);
    is >> d.month;
    is.ignore(1);
    is >> d.day;
    return is;
}

// Macros
#define SORT_BY(field)   \
[](AirlineTicket& lhs,AirlineTicket& rhs)  {  \
    return lhs.field < rhs.field;}

#define UPDATE_FIELD(ticket, field, values) \
{   \
    map<string, string>::const_iterator it; \
    it = values.find(#field);    \
    if (it != values.end()) {  \
        istringstream is(it->second);   \
        is >> ticket.field; \
    }   \
}

void TestUpdate() {
    AirlineTicket t;
    t.price = 0;

    const map<string, string> updates1 = {
      {"departure_date", "2018-2-28"},
      {"departure_time", "17:40"},
    };
    UPDATE_FIELD(t, departure_date, updates1);
    UPDATE_FIELD(t, departure_time, updates1);
    UPDATE_FIELD(t, price, updates1);

    ASSERT_EQUAL(t.departure_date, (Date{ 2018, 2, 28 }));
    ASSERT_EQUAL(t.departure_time, (Time{ 17, 40 }));
    ASSERT_EQUAL(t.price, 0);

    const map<string, string> updates2 = {
      {"price", "12550"},
      {"arrival_time", "20:33"},
    };
    UPDATE_FIELD(t, departure_date, updates2);
    UPDATE_FIELD(t, departure_time, updates2);
    UPDATE_FIELD(t, arrival_time, updates2);
    UPDATE_FIELD(t, price, updates2);

    // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
    // значения этих полей не должны измениться
    ASSERT_EQUAL(t.departure_date, (Date{ 2018, 2, 28 }));
    ASSERT_EQUAL(t.departure_time, (Time{ 17, 40 }));
    ASSERT_EQUAL(t.price, 12550);
    ASSERT_EQUAL(t.arrival_time, (Time{ 20, 33 }));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestUpdate);
}

