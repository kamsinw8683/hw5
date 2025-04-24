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
void generateWords(const std::string& pattern,
                   const std::string& floating,
                   const std::set<std::string>& dict,
                   std::string& current,
                   std::set<std::string>& results,
                   std::size_t pos,
                   std::map<char,int>& floatingCount)
{
    // Base case: filled all positions
    if (pos == pattern.size()) {
        bool allUsed = true;
        for (std::map<char,int>::const_iterator it = floatingCount.begin();
             it != floatingCount.end();
             ++it)
        {
            if (it->second != 0) {
                allUsed = false;
                break;
            }
        }
        if (allUsed && dict.find(current) != dict.end()) {
            results.insert(current);
        }
        return;
    }

    // If this position is fixed
    if (pattern[pos] != '-') {
        current.push_back(pattern[pos]);
        generateWords(pattern, floating, dict, current, results, pos + 1, floatingCount);
        current.pop_back();
        return;
    }

    // Try every letter 'a'..'z'
    for (char c = 'a'; c <= 'z'; ++c) {
        // (1) Use a required floating letter, if still needed
        std::map<char,int>::iterator fit = floatingCount.find(c);
        if (fit != floatingCount.end() && fit->second > 0) {
            current.push_back(c);
            fit->second--;
            generateWords(pattern, floating, dict, current, results, pos + 1, floatingCount);
            fit->second++;
            current.pop_back();
        }

        // (2) Always allow as a filler letter
        current.push_back(c);
        generateWords(pattern, floating, dict, current, results, pos + 1, floatingCount);
        current.pop_back();
    }
}