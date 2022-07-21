#include "stats.h"

Stats::Stats() {
    methods_ = {
            {"GET", 0},
            {"PUT", 0},
            {"POST", 0},
            {"DELETE", 0},
            {"UNKNOWN", 0},
    };

    uri_ = {
        {"/", 0},
        {"/order", 0},
        {"/product", 0},
        {"/basket", 0},
        {"/help", 0},
        {"unknown", 0},
    };
}

void Stats::AddMethod(string_view method) {
    if (methods_.find(method) != methods_.end()) {
        methods_[method]++;
    } else {
        methods_["UNKNOWN"]++;
    }
}

void Stats::AddUri(string_view uri) {
    if (uri_.find(uri) != uri_.end()) {
        uri_[uri]++;
    } else {
        uri_["unknown"]++;
    }
}

const map<std::string_view, int>& Stats::GetMethodStats() const {
    return methods_;
}

const map<std::string_view, int>& Stats::GetUriStats() const {
    return uri_;
}


HttpRequest ParseRequest(string_view line) {
    HttpRequest request;
    line.remove_prefix(line.find_first_not_of(" "));
    request.method = line.substr(0, line.find(" "));

    line.remove_prefix(std::min(line.find(" ") + 1, line.npos));
    request.uri = line.substr(0, line.find(" "));

    line.remove_prefix(std::min(line.find(" ") + 1, line.npos));
    request.protocol = line.substr(0, line.find(" "));

    return request;
}