#pragma once

#include <string>
#include <set>
#include <vector>
#include <algorithm>

class EventType {
public:
	void Add(const std::string& event);
	const std::vector<std::string>& GetEvents() const;

	template <typename Predicate>
	int RemoveIf(Predicate predicate) {
		auto rem_it = std::stable_partition(events_v_.begin(), events_v_.end(), predicate);
		//int count = std::distance(events_v_.begin(), rem_it);
		int count = rem_it - events_v_.begin();
		
		//erase in set
		for (auto i = events_v_.begin(); i != rem_it; ++i) {
			events_.erase(*i);
		}
		//erase in vector
		events_v_.erase(events_v_.begin(), rem_it);

		return count;
	}

private:
	std::set<std::string> events_;
	std::vector<std::string> events_v_;
};