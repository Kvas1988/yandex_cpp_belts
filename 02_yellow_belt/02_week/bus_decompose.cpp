#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <cassert>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

bool operator == (Query q1, Query q2) {
    if (q1.bus == q2.bus & q1.stop == q2.stop & q1.stops == q2.stops & q1.type == q2.type) {
        return true;
    }
    return false;
}

istream& operator >> (istream& is, Query& q) {
    // Реализуйте эту функцию
    string actionType, bus, stop;
    size_t stopCount;
    is >> actionType;
    if (actionType == "NEW_BUS") {        
        is >> bus >> stopCount;        
        vector<string> stops(stopCount);
        for (auto& stopName : stops) {            
            is >> stopName;            
        }
        q.type = QueryType::NewBus;
        q.bus = bus;
        q.stops = stops;
    }
    else if (actionType == "BUSES_FOR_STOP") {
        is >> stop;
        q.type = QueryType::BusesForStop;
        q.stop = stop;
    }
    else if (actionType == "STOPS_FOR_BUS") {
        is >> bus;
        q.type = QueryType::StopsForBus;
        q.bus = bus;
    }
    else if (actionType == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
    // Наполните полями эту структуру
    string stop;
    vector<string> buses;
    string err;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    // Реализуйте эту функцию
    if (r.buses.size() == 0) {
        os << r.err;
    }
    else {
        bool isFirst = true;
        for (const auto& bus : r.buses) {            
            if (!isFirst) {
                os << " ";
            }
            os << bus;
            isFirst = false;
        }
    }

    return os;
}

bool operator ==(BusesForStopResponse bfs1, BusesForStopResponse bfs2) {
    if (bfs1.err == bfs2.err & bfs1.stop == bfs2.stop & bfs1.buses == bfs2.buses) {
        return true;
    }
    return false;
}

struct StopsForBusResponse {
    // Наполните полями эту структуру
    string bus;
    vector<string> stops;
    map<string, vector<string>> interchange;
    string err;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    // Реализуйте эту функцию
    if (r.stops.size() == 0) {
        os << r.err;
    }
    else {
        bool isFirst = true;
        for (const auto& stop : r.stops) {
            if (!isFirst) {
                os << endl;
            }
            isFirst = false;

            os << "Stop " << stop << ":";
            if (r.interchange.at(stop).size() == 1) {
                os << " no interchange";
            }
            else {
                for (const auto& bus : r.interchange.at(stop)) {
                    if (bus != r.bus) {
                        os << " " << bus;
                    }
                }
            }            
        }
    }
    return os;
}

struct AllBusesResponse {
    // Наполните полями эту структуру
    string err;
    map<string, vector<string>> buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    // Реализуйте эту функцию
    if (r.buses.size() == 0) {
        os << r.err;
    }
    else {
        bool isFirst = true;
        for (const auto& bus : r.buses) {
            if (!isFirst) {
                os << endl;
            }
            isFirst = false;

            os << "Bus " << bus.first << ":";
            for (const auto& stop : bus.second) {
                os << " " << stop;
            }
        }
    }

    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        // Реализуйте этот метод
        for (const auto& stop : stops) {
            buses_to_stops[bus].push_back(stop);
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        // Реализуйте этот метод
        BusesForStopResponse res;
        if (stops_to_buses.count(stop) == 0) {
            res.err = "No stop";
        }
        else {
            //vector<string> buses;
            for (const auto& bus : stops_to_buses.at(stop)) {
                //buses.push_back(bus);
                res.buses.push_back(bus);
            }
        }

        return res;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        // Реализуйте этот метод
        StopsForBusResponse res;
        res.bus = bus;
        if (buses_to_stops.count(bus) == 0) {
            res.err = "No bus";
        }
        else {
            res.stops = buses_to_stops.at(bus);
            for (const auto& stop : buses_to_stops.at(bus)) {                        
                res.interchange[stop] = stops_to_buses.at(stop);
            }
        }

        return res;
    }

    AllBusesResponse GetAllBuses() const {
        // Реализуйте этот метод
        AllBusesResponse res;
        if (buses_to_stops.size() == 0) {
            res.err = "No buses";
        }
        else {
            res.buses = buses_to_stops;
        }

        return res;
    }

    map<string, vector<string>> TestBusesToStops() {
        return buses_to_stops;
    }
    map<string, vector<string>> TestStopsToBuses() {
        return stops_to_buses;
    }

private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};

void TestFuncs() {
    BusManager bm;    
    Query q;
    cin >> q;

    Query exp_q;
    exp_q.type = QueryType::NewBus;
    exp_q.bus = "32";
    exp_q.stops = { "Tolstopaltsevo", "Marushkino", "Vnukovo" };
    assert(q == exp_q);
    cout << "Add Query OK" << endl; 
    
    bm.AddBus(q.bus, q.stops);
    //bm.AddBus("32", { "Tolstopaltsevo", "Marushkino", "Vnukovo" });

    cin >> q;
    bm.AddBus(q.bus, q.stops);
    //bm.AddBus("32K", { "Tolstopaltsevo", "Marushkino", "Vnukovo", "Peredelkino", "Solntsevo", "Skolkovo" });
    bm.AddBus("272", { "Vnukovo", "Moskovsky", "Rumyantsevo", "Troparyovo" });
    
    map<string, vector<string>> expected_bts, expected_stb;
    expected_bts["32"] = {"Tolstopaltsevo", "Marushkino", "Vnukovo" };
    expected_bts["32K"] = {"Tolstopaltsevo", "Marushkino", "Vnukovo", "Peredelkino", "Solntsevo", "Skolkovo"};
    expected_bts["272"] = { "Vnukovo", "Moskovsky", "Rumyantsevo", "Troparyovo" };

    expected_stb["Tolstopaltsevo"] = { "32", "32K" };
    expected_stb["Marushkino"] = { "32", "32K" };
    expected_stb["Vnukovo"] = { "32", "32K", "272" };
    expected_stb["Peredelkino"] = { "32K" };
    expected_stb["Solntsevo"] = { "32K" };
    expected_stb["Skolkovo"] = { "32K" };

    expected_stb["Moskovsky"] = { "272" };
    expected_stb["Rumyantsevo"] = { "272" };
    expected_stb["Troparyovo"] = { "272" };


    assert(bm.TestBusesToStops() == expected_bts);
    assert(bm.TestStopsToBuses() == expected_stb);
    cout << "AddBus OK" << endl;

    BusesForStopResponse expectedResponse_bfs;
    //expectedResponse_bfs.stop = "Vnukovo";
    expectedResponse_bfs.buses = { "32", "32K", "272" };
    BusesForStopResponse classReturn = bm.GetBusesForStop("Vnukovo");
    assert(classReturn == expectedResponse_bfs);
    cout << "GetBusesForStop function OK" << endl;

    cout << classReturn;

}

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {    
    //TestFuncs();
    //return 0;
    
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }

    return 0;
}
