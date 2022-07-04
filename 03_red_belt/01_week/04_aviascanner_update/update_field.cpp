#include "airline_ticket.h"
#include "test_runner.h"

#include <tuple>
#include <iomanip>

using namespace std;

// macros
#define SORT_BY(field) [](const AirlineTicket& lhs, const AirlineTicket& rhs) {return lhs.field < rhs.field;}

#define UPDATE_FIELD(ticket, field, values)  {                          \
    map<string, string>::const_iterator iter = values.find(#field);     \
    if (iter != values.end()) {                                         \
        istringstream is(iter->second);                                 \
        is >> ticket.field;                                             \
    }                                                                   \
}


// funcs to handle dates
tuple<int, int, int> MakeDateTuple(const Date& d) {
    return make_tuple(d.year, d.month, d.day);
}

tuple<int, int> MakeTimeTuple(const Time& t) {
    return make_tuple(t.hours, t.minutes);
}

// operators
// dates
bool operator <(const Date& lhs, const Date& rhs) {
    return MakeDateTuple(lhs) < MakeDateTuple(rhs);
}

bool operator ==(const Date& lhs, const Date& rhs) {
    return MakeDateTuple(lhs) == MakeDateTuple(rhs);
}

ostream& operator <<(ostream& os, const Date& d) {
    os << setw(2) << setfill('0') << d.day << '.' 
        << setw(2) << setfill('0') << d.month << '.'
        << setw(4) << setfill('0') << d.year;

    return os;
}

istream& operator >>(istream& is, Date& d) {
    is >> d.year;
    is.ignore(1);
    is >> d.month;
    is.ignore(1);
    is >> d.day;
    return is;
}

// time
bool operator <(const Time& lhs, const Time& rhs) {
    return MakeTimeTuple(lhs) < MakeTimeTuple(rhs);
}

bool operator ==(const Time& lhs, const Time& rhs) {
    return MakeTimeTuple(lhs) == MakeTimeTuple(rhs);
}

ostream& operator <<(ostream& os, const Time& t) {
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

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
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
  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}
