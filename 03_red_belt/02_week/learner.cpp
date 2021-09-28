#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include <fstream>
#include <set>
#include "profile.h"

using namespace std;

class Learner {
 private:
  //vector<string> dict;
    set<string> dict;
    

public:
    int Learn(const vector<string>& words) {
        int newWords = 0;
        auto d_size = dict.size();
        for (const auto& word : words) {
            dict.insert(word);
            if (dict.size() > d_size) {
                newWords++;
                d_size = dict.size();
            }
        }
        return newWords;
    }
    
    vector<string> KnownWords() {
        vector<string> ret;
        for (const auto& word: dict) {
            ret.push_back(word);
        }
        return ret;
    }
//  int Learn(const vector<string>& words) {
//    int newWords = 0;
//    for (const auto& word : words) {
//      if (find(dict.begin(), dict.end(), word) == dict.end()) {
//        ++newWords;
//        dict.push_back(word);
//      }
//    }
//    return newWords;
//  }
    

//  vector<string> KnownWords() {
//    sort(dict.begin(), dict.end());
//    dict.erase(unique(dict.begin(), dict.end()), dict.end());
//    return dict;
//  }
};

// coursera test
int main() {
  Learner learner;
  string line;
  while (getline(cin, line)) {
    vector<string> words;
    stringstream ss(line);
    string word;
    while (ss >> word) {
      words.push_back(word);
    }
    cout << learner.Learn(words) << "\n";
  }
  cout << "=== known words ===\n";
  for (auto word : learner.KnownWords()) {
    cout << word << "\n";
  }
    
    return 0;
}

int Mymain() {
    LOG_DURATION("Total");
    
    Learner learner;
    vector<vector<string>> vocab;
    int counterLearn = 0;
    
    // Reading Words
    ifstream in("input.txt");
    string line;
    while(getline(in, line)) {
        vector<string> words;
        stringstream ss(line);
        string word;
        while (ss >> word) {
            words.push_back(word);
        }
        vocab.push_back(words);
        }
    
    {
        LOG_DURATION("Learn");
        for (const auto& words: vocab) {
            cout << learner.Learn(words) << endl;
            counterLearn++;
        }
        cout << "Learn calls: " << counterLearn << endl;
    }
    
    {
        LOG_DURATION("Known")
//        cout << "=== known words ===\n";
        for (auto word : learner.KnownWords()) {
//          cout << word << "\n";
            string w = word;
        }
    }
    return 0;
}
