#ifndef WORDLE_H
#define WORDLE_H

#ifndef RECCHECK
#include <set>
#include <string>
#include <map>
#endif

/**
 * @brief Returns the list of all legal words in the provided dictionary
 *        that meet the criteria provided in the `in` and `floating`
 *        inputs.
 * 
 * @param [in] in - string of fixed, correct characters and `-`s to indicate
 *                  the length of string and locations that must be filled in
 * @param [in] floating  - Characters that must be used somewhere in the word
 * @param [in] dict - Dictionary of strings of legal words
 * @return std::set<std::string> - Set of all words that meet the criteria
 */
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict);

/**
 * @brief Recursively generates all possible word combinations that match the given constraints
 * 
 * @param [in] in - string of fixed, correct characters and `-`s to indicate open positions
 * @param [in] floating - Characters that must be used somewhere in the word
 * @param [in] dict - Dictionary of strings of legal words
 * @param [in,out] current - Current partial word being constructed
 * @param [out] results - Set to store valid words that match the criteria
 * @param [in] pos - Current position in the word being processed
 * @param [in,out] floatingCount - Map tracking remaining occurrences of floating characters
 */
void generateWords(const std::string& in, const std::string& floating, 
                  const std::set<std::string>& dict, std::string& current, 
                  std::set<std::string>& results, size_t pos, 
                  std::map<char, int>& floatingCount);

#endif // WORDLE_H