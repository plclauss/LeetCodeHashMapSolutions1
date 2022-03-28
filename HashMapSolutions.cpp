//
// Created by plcla on 3/28/2022.
//

#include "HashMapSolutions.h"

// returns number that occurs most often in array
// O_tc(n), O_sc(n)
int HashMap::majorityElement(const std::vector<int> &nums) {
    // key = value of int in nums vector
    // map = number of occurrences of key
    std::unordered_map<int, int> um;

    // tally up num of occurrences
    for (auto& num : nums) {
        if (um.find(num) == um.end())
            um.insert(std::make_pair(num, 1));
        else
            um[num]++;
    }

    // iterate through keys
    int highestKey = 0, highestMapped = 0;
    for (auto it = um.begin(); it != um.end(); it++) {
        if (um[it->first] > highestMapped) {
            highestKey = it->first;
            highestMapped = um[it->first];
        }
    }

    return highestKey;
}

// take string input of roman numerals and convert to integer
// O_tc(n), O_sc(1)
int HashMap::romanToInt(const std::string s) {
    // key = roman numeral
    // mapped = roman numeral int equivalent
    std::unordered_map<char, int> map;

    // insert all combos
    map['I'] = 1;
    map['V'] = 5;
    map['X'] = 10;
    map['L'] = 50;
    map['C'] = 100;
    map['D'] = 500;
    map['M'] = 1000;

    /* ******************************** */
    /* ****NOTE: I, X, C ARE ISSUES**** */
    /* ******************************** */

    // iterate through input string
    int sum = 0;
    auto it = s.begin();
    while (it != s.end()) {
        if (*it == 'I' && *(it + 1) == 'V') {
            sum += 4;
            it += 2;
        }
        else if (*it == 'I' && *(it + 1) == 'X') {
            sum += 9;
            it += 2;
        }
        else if (*it == 'X' && *(it + 1) == 'L') {
            sum += 40;
            it += 2;
        }
        else if (*it == 'X' && *(it + 1) == 'C') {
            sum += 90;
            it += 2;
        }
        else if (*it == 'C' && *(it + 1) == 'D') {
            sum += 400;
            it += 2;
        }
        else if (*it == 'C' && *(it + 1) == 'M') {
            sum += 900;
            it += 2;
        }
        else {
            sum += map[*it];
            it++;
        }
    }

    return sum;
}

bool HashMap::wordPattern(std::string Pattern, std::string s) {

}