//
// Created by plcla on 3/28/2022.
//

#include <unordered_map>
#include <vector>
#include <string>

#ifndef LEETCODEHASHTABLESOLUTIONS_HASHMAPSOLUTIONS_H
#define LEETCODEHASHTABLESOLUTIONS_HASHMAPSOLUTIONS_H

class HashMap {
public:
    int majorityElement(const std::vector<int>& nums);
    int romanToInt(const std::string s);
    bool wordPattern(std::string Pattern, std::string s);
    int findShortestSubArray(std::vector<int>& nums);
    bool isValidSudoku(std::vector<std::vector<char>>& board);

private:
};

#endif //LEETCODEHASHTABLESOLUTIONS_HASHMAPSOLUTIONS_H
