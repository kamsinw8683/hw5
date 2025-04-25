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


std::set<std::string> wordle(
    const std::string &in,
    const std::string &floating,
    const std::set<std::string> &dict)
{
    // Add your code here
    std::set<std::string> filteredDict;
    std::set<std::string>::iterator wordIterator;

    for (wordIterator = dict.begin(); wordIterator != dict.end(); ++wordIterator)
    {
        std::string currWord = *wordIterator;
        bool valid = true;

        for (int i = 0; i < currWord.length(); i++)
        {
            if (isalpha(currWord[i]) == 0)
            {
                valid = false;
            }
            else if (islower(currWord[i]) == 0)
            {
                valid = false;
            }
        }
        if (valid && (validateWord(currWord, floating, 0) && in.length() == currWord.length()))
        {
            filteredDict.insert(currWord);
        }
    }
    filteredDict = wordleHelper(in, floating, filteredDict, 0);

    return filteredDict;
}

// Define any helper functions here
std::set<std::string> wordleHelper(
    const std::string &in,
    const std::string &floating,
    const std::set<std::string> &dict,
    int curPos)
{
    std::set<std::string> filteredDict;
    std::set<std::string>::iterator wordIterator;

    if (curPos >= in.length())
    {
        return dict;
    }
    if (in[curPos] == '-')
    {
        return wordleHelper(in, floating, dict, curPos + 1);
    }

    for (wordIterator = dict.begin(); wordIterator != dict.end(); ++wordIterator)
    {
        if (in[curPos] != '-' && (*wordIterator)[curPos] == in[curPos])
            filteredDict.insert(*wordIterator);
    }

    return wordleHelper(in, floating, filteredDict, curPos + 1);
}

bool validateWord(std::string word, std::string floating, int wordPos)
{
    bool found = false;
    std::string updatedWord = word;

    if (wordPos >= floating.length())
    {
        return true;
    }
    for (int i = 0; i < word.length(); i++)
    {
        if (word[i] == floating[wordPos])
        {
            updatedWord.erase(i, 1);
            found = true;
            break;
        }
    }
    return found && validateWord(updatedWord, floating, wordPos + 1);
}
