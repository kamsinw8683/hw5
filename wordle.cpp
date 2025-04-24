#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    set<string> results;
    string current;
    map<char, int> floatingCount;
    
    for (char c : floating) {
        floatingCount[c]++;
    }
    
    generateWords(in, floating, dict, current, results, 0, floatingCount);
    return results;
}

// Define any helper functions here
void generateWords(const string& in, const string& floating, 
                  const set<string>& dict, string& current, 
                  set<string>& results, size_t pos, map<char, int>& floatingCount) {
    // Base case:
    if (pos == in.size()) {
        // Check if the word exists in the dictionary
        if (dict.find(current) != dict.end()) {
            results.insert(current);
        }
        return;
    }

    if (in[pos] != '-') {
        current += in[pos];
        generateWords(in, floating, dict, current, results, pos + 1, floatingCount);
        return;
    }

    for (char c = 'a'; c <= 'z'; c++) {
        // If this letter is in floating letters and we haven't used it enough times
        if (floatingCount.find(c) != floatingCount.end() && floatingCount[c] > 0) {
            current += c;
            floatingCount[c]--;
            generateWords(in, floating, dict, current, results, pos + 1, floatingCount);
            floatingCount[c]++;
            current.pop_back();
        }
        // If this letter is not in floating letters
        else if (floatingCount.find(c) == floatingCount.end()) {
            current += c;
            generateWords(in, floating, dict, current, results, pos + 1, floatingCount);
            current.pop_back();
        }
    }
}

