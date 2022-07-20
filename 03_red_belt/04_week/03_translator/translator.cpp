#include "test_runner.h"
#include <string>
#include <vector>

#include <map>

using namespace std;

class Translator {
public:
    void Add(string_view source, string_view target);
    string_view TranslateForward(string_view source) const;
    string_view TranslateBackward(string_view target) const;

private:

    string_view Translate(std::map<string_view, string_view> dict, string_view source) const;

    std::map<string_view, string_view> vocab_;
    std::map<string_view, string_view> backward_;
};

void Translator::Add(string_view source, string_view target) {
    vocab_.insert({source, target});
    backward_.insert({target, source});
}

string_view Translator::Translate(std::map<string_view, string_view> dict, string_view source) const {
    std::map<string_view, string_view>::const_iterator pos = dict.find(source);
    if (pos == dict.end()) {
        return "";
    }
    return pos->second;
}

string_view Translator::TranslateForward(string_view source) const {
    return Translate(vocab_, source);
}

string_view Translator::TranslateBackward(string_view target) const {
    return Translate(backward_, target);
}


void TestSimple() {
    Translator translator;
    translator.Add(string("okno"), string("window"));
    translator.Add(string("stol"), string("table"));

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    return 0;
}
