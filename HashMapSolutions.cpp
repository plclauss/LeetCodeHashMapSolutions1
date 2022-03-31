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

// takes a pattern, such as "abab", and a string, such as, "hi bye hi bye"
// and determines whether the string follows the same pattern as pattern
// O_tc(n*m), O_sc(n)
bool HashMap::wordPattern(const std::string pattern, const std::string s) {
    // if # spaces in s doesnt equal the # of chars in pattern - 1, ret false
    int index = 0, numSpaces = 0;
    for (auto& it : s) {
        if (s.find(' ', index) == std::string::npos) {
            break;
        }
        else {
            index = s.find(' ', index) + 1;
            numSpaces++;
        }
    }

    if (numSpaces != pattern.size() - 1)
        return false;

    // construct map
    // KEY = char in pattern not alr in map
    // MAPPED = string in s not alr in map
    std::unordered_map<char, std::string> map;

    index = 0;
    for (auto& it : pattern) {
        if (map.find(it) == map.end()) {
            if (s.find(' ', index) == std::string::npos) {
                if (!isInMap(map, s.substr(index)))
                    map.insert(std::make_pair(it, s.substr(index)));
            }
            else {
                map.insert(std::make_pair(it, findSuitableInsert(map, s, &index)));
            }
        }
    }


    // validate pattern
    index = 0;
    for (auto& it : pattern) {
        if (s.find(' ', index) == std::string::npos) {
            if (s.substr(index) != map[it])
                return false;
        }
        else {
            if (s.substr(index, (s.find(' ', index) - index)) != map[it])
                return false;
        }
        index = s.find(' ', index) + 1;
    }

    return true;
}

// find string not already in map
std::string HashMap::findSuitableInsert(const std::unordered_map<char, std::string> &map, const std::string& str, int *index) {
    while (*index < str.size()) {
        if (str.find(' ', *index) == std::string::npos) {
            if (!isInMap(map, str.substr(*index)))
                return str.substr(*index);
            break;
        }
        else {
            if (!isInMap(map, str.substr(*index, (str.find(' ', *index)) - *index)))
                return str.substr(*index, (str.find(' ', *index) - *index));
        }
        *index = str.find(' ', *index) + 1;
    }

    return "";
}

// returns true if str is already in map
// returns false otherwise
bool HashMap::isInMap(const std::unordered_map<char, std::string>& map, const std::string& str) {
    for (auto it : map) {
        if (map.at(it.first) == str)
            return true;
    }
    return false;
}

// returns shortest subarray containing same degree as nums
// degree is defined as the max frequency of any number in nums
// O_tc(n^2), O_sc(n)
int HashMap::findShortestSubArray(std::vector<int> &nums) {
    // find degree
    // KEY = num in nums
    // MAPPED = frequency
    std::unordered_map<int, int> map;

    // generate map
    for (auto &it: nums) {
        if (map.find(it) == map.end())
            map.insert(std::make_pair(it, 1));
        else
            map[it]++;
    }

    // find highest degree
    int deg = 0;
    for (auto &it: map) {
        if (map[it.first] > deg)
            deg = map[it.first];
    }

    // new map for distances
    // KEY = num of suitable degree
    // MAPPED = dist from farthest key
    std::unordered_map<int, int> distMap;
    std::vector<int> arr;

    for (auto& it : map) {
        if (map[it.first] == deg) {
            auto itFirst = nums.begin();
            auto itSecond = nums.begin() + nums.size() - 1;
            while (itFirst < itSecond) {
                if (*itFirst == it.first && *itSecond == it.first)
                    break;
                if (*itFirst != it.first)
                    itFirst++;
                if (*itSecond != it.first)
                    itSecond--;
            }
            arr.assign(itFirst, itSecond + 1);
            if (hasDegree(arr, deg, it.first))
                distMap.insert(std::make_pair(it.first, arr.size()));
            arr.clear();
        }
    }

    // iterate through distance map
    // find smallest dist
    int smallest = INT_MAX;
    for (auto& it : distMap)
        if (distMap[it.first] < smallest)
            smallest = distMap[it.first];

    return smallest;
}

// see if arr has enough of nums in it to match degree level
bool HashMap::hasDegree(const std::vector<int>& copy, int temp, const int numID) {
    for (auto& num : copy) {
        if (num == numID)
            temp--;
        if (temp == 0)
            return true;
    }

    return false;
}

// given a 9x9 sudoku map, check if filled in squares produces a valid sudoku board
// i.e., no repeating nums in any row, col, or 3x3 square
// O_tc(n^2), O_sc(n)
bool HashMap::isValidSudoku(std::vector<std::vector<char>> &board) {
    // KEY = num in row
    // MAPPED = doesn't matter
    std::unordered_map<char, int> map;

    // check rows
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] != '.' && map.find(board[i][j]) != map.end())
                return false;
            if (board[i][j] != '.')
                map.insert(std::make_pair(board[i][j], 0));
        }
        map.clear();
    }

    // check cols
    map.clear();
    for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
            if (board[i][j] != '.' && map.find(board[i][j]) != map.end())
                return false;
            if (board[i][j] != '.')
                map.insert(std::make_pair(board[i][j], 0));
        }
        map.clear();
    }


    // check 3x3s
    // KEY = x
    // MAPPED = y
    map.clear();
    std::unordered_multimap<int, int> XY ({
        {0, 0}, {0, 3}, {0, 6},
        {3, 0}, {3, 3}, {3, 6},
        {6, 0}, {6, 3}, {6, 6}
    });
    for (auto& it : XY) {
        for (int start = it.first; start < (it.first + 3); start++) {
            for (int end = it.second; end < (it.second + 3); end++) {
                if (board[start][end] != '.' && map.find(board[start][end]) != map.end())
                    return false;
                if (board[start][end] != '.')
                    map.insert(std::make_pair(board[start][end], 0));
            }
        }
        map.clear();
    }

    return true;
}