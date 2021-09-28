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


#define SORT_BY(field)   \
[](AirlineTicket& lhs,AirlineTicket& rhs)  {  \
    return lhs.field < rhs.field;}


void TestSortBy() {
    vector<AirlineTicket> tixs = {
        {"VKO", "AER", "Utair", {2018, 2, 28}, {17, 40}, {2018, 2, 28}, {20,  0}, 1200},
        {"AER", "VKO", "Utair", {2018, 3,  5}, {14, 15}, {2018, 3,  5}, {16, 30}, 1700},
        {"AER", "SVO", "Aeroflot", {2018, 3,  5}, {18, 30}, {2018, 3,  5}, {20, 30}, 2300},
        {"PMI", "DME", "Iberia", {2018, 2,  8}, {23, 00}, {2018, 2,  9}, { 3, 30}, 9000},
        {"CDG", "SVO", "AirFrance", {2018, 3,  1}, {13, 00}, {2018, 3,  1}, {17, 30}, 8000},
    };

    sort(begin(tixs), end(tixs), SORT_BY(price));
    ASSERT_EQUAL(tixs.front().price, 1200);
    ASSERT_EQUAL(tixs.back().price, 9000);

    sort(begin(tixs), end(tixs), SORT_BY(from));
    ASSERT_EQUAL(tixs.front().from, "AER");
    ASSERT_EQUAL(tixs.back().from, "VKO");

    sort(begin(tixs), end(tixs), SORT_BY(arrival_date));
    ASSERT_EQUAL(tixs.front().arrival_date, (Date{ 2018, 2, 9 }));
    ASSERT_EQUAL(tixs.back().arrival_date, (Date{ 2018, 3, 5 }));
}


void SortTickets(vector<AirlineTicket>& tixs) {
    stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
        return lhs.to < rhs.to;
        });
    stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
        return lhs.departure_time < rhs.departure_time;
        });
    stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
        return lhs.price < rhs.price;
        });
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSortBy);
}


