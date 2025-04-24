// wordle.h
#ifndef WORDLE_H
#define WORDLE_H

#ifndef RECCHECK
#include <set>
#include <string>
#include <map>
#include <vector>
#endif

std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict);

bool validateWord(std::string str, std::string floating, int place);

std::set<std::string> wordleHelper( 
    const std::string &in,
    const std::string &floating,
    const std::set<std::string> &dict,
    int currentPosition);

#endif // WORDLE_H