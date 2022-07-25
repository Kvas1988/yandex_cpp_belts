#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <vector>
#include <future>
using namespace std;

struct Stats {
    map<string, int> word_frequences;

    void operator += (const Stats& other) {
        for (auto& [word, freq] : other.word_frequences) {
            word_frequences[word] += freq;
        }
    }

    bool contains(const std::string& key) {
        if (word_frequences.find(key) == word_frequences.end()) {
            return false;
        }
        return true;
    }

    int& operator [](const std::string& key) {
        return word_frequences[key];
    }
};


Stats ExploreLine(const set<string>& key_words, const string& line) {
    Stats stats;
    std::string_view line_view(line);

    auto pos = line_view.find_first_not_of(" ");
    line_view.remove_prefix(pos);

    while(pos != line_view.npos) {
        pos = line_view.find_first_of(" ");
        std::string key = std::string(line_view.substr(0, pos));

        if (key_words.count(key) > 0) {
            stats[key]++;
        }

        if (pos == line_view.npos) {
            break;
        } else {
            line_view.remove_prefix(pos + 1);
        }
    }

    return stats;
}

Stats ExploreBatch(const std::set<string>& key_words, const std::vector<std::string> batch) {
    Stats stats;
    for (const std::string& line : batch) {
        stats += ExploreLine(key_words, line);
    }
    return stats;
}

Stats ExploreKeyWordsSingleThread(
        const set<string>& key_words, istream& input
) {
    Stats result;
    for (string line; getline(input, line); ) {
        result += ExploreLine(key_words, line);
    }
    return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    // Реализуйте эту функцию
    Stats result;
    std::vector<std::future<Stats>> futures;
    std::vector<std::string> batch;
    size_t batch_size = 10;
    batch.reserve(batch_size);

    for (string line; getline(input, line); ) {
        batch.push_back(line);

        if (batch.size() >= batch_size) {
            futures.push_back(async(ExploreBatch, std::ref(key_words), std::move(batch) ));
            batch.reserve(batch_size);
        }
    }

    if (!batch.empty()) {
        futures.push_back(async(ExploreBatch, std::ref(key_words), std::move(batch) ));
    }

    for (auto& f : futures) {
        result += f.get();
    }
    return result;
}

void TestBasic() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
            {"yangle", 6},
            {"rocks", 2},
            {"sucks", 1}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}
