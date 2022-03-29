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
    bool wordPattern(const std::string pattern, const std::string s);
    int findShortestSubArray(std::vector<int>& nums);
    bool isValidSudoku(std::vector<std::vector<char>>& board);

private:
    bool isInMap(const std::unordered_map<char, std::string>& map, const std::string& str);
    std::string findSuitableInsert(const std::unordered_map<char, std::string>& map, const std::string& str, int* index);
    int findDegree(const std::vector<int>& arr);
};

#endif //LEETCODEHASHTABLESOLUTIONS_HASHMAPSOLUTIONS_H
