#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
using namespace std;

class Stats {
public:
    Stats();
    void AddMethod(string_view method);
    void AddUri(string_view uri);
    const map<string_view, int>& GetMethodStats() const;
    const map<string_view, int>& GetUriStats() const;

private:
    std::map<std::string_view, int> methods_;
    std::map<std::string_view, int> uri_;
};

HttpRequest ParseRequest(string_view line);