#include "eventtype.h"

void EventType::Add(const std::string& event) {
	auto insert_result = events_.insert(event);
	if (insert_result.second) {	
		events_v_.push_back(event);
	}
}

const std::vector<std::string>& EventType::GetEvents() const {
	return events_v_;
}