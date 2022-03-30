#include <iostream>
#include <time.h>
#include "HashMapSolutions.h"

const int VECMAX = 5E4;
const int STRMAX = 15;
const int PATTMAX = 300;
const int STRPATTMAX = 3000;

void generateVector(std::vector<int>& copy, const int size) {
    if (size < 1 || size > VECMAX)
        return;

    copy.clear();
    srand(time(NULL));
    for (int i = 0; i < size; i++)
        copy[i] = rand() % 11;
}

void generateRomanNumeralString(std::string& copy, const int size) {
    if (size < 1 || size > STRMAX)
        return;

    srand(time(NULL));

    int maxNum = 3999;
    std::unordered_multimap<char, int> pattern = {
            {'I', 3},
            {'V', 1}, {'I', 1}, {'V', 1}, {'X', 1}, {'I', 1}, {'X', 3},
            {'L', 1}, {'X', 1}, {'L', 1}, {'C', 1}, {'X', 1}, {'C', 3},
            {'D', 1}, {'C', 1}, {'D', 1}, {'M', 1}, {'C', 1}, {'M', 3}
    };

    int numTimes = -1;
    for (auto it : pattern) {
        if (it.first == 'M') {
            while (true) {
                numTimes = rand() % it.second;
                if (numTimes * 1000 < maxNum)
                    break;
            }
            maxNum -= numTimes*1000;
            for (int i = 0; i < numTimes; i++)
                copy += 'M';
        }
        else if (it.first == 'D') {
            while (true) {
                numTimes = rand() % it.second;
                if (numTimes * 500 < maxNum)
                    break;
            }
            maxNum -= numTimes*500;
            for (int i = 0; i < numTimes; i++)
                copy += 'D';
        }
        else if (it.first == 'C') {
            while (true) {
                numTimes = rand() % it.second;
                if (numTimes * 100 < maxNum)
                    break;
            }
            maxNum -= numTimes*100;
            for (int i = 0; i < numTimes; i++)
                copy += 'C';
        }
        else if (it.first == 'L') {
            while (true) {
                numTimes = rand() % it.second;
                if (numTimes * 50 < maxNum)
                    break;
            }
            maxNum -= numTimes*50;
            for (int i = 0; i < numTimes; i++)
                copy += 'L';
        }
        else if (it.first == 'X') {
            while (true) {
                numTimes = rand() % it.second;
                if (numTimes * 10 < maxNum)
                    break;
            }
            maxNum -= numTimes*10;
            for (int i = 0; i < numTimes; i++)
                copy += 'X';
        }
        else if (it.first == 'V') {
            while (true) {
                numTimes = rand() % it.second;
                if (numTimes * 5 < maxNum)
                    break;
            }
            maxNum -= numTimes*5;
            for (int i = 0; i < numTimes; i++)
                copy += 'V';
        }
        else {
            while (true) {
                numTimes = rand() % it.second;
                if (numTimes < maxNum)
                    break;
            }
            maxNum -= numTimes;
            for (int i = 0; i < numTimes; i++)
                copy += 'I';
        }
    }
}

void generateRandomPattern(std::string& pattern, std::string& str, const int pLen, const int sLen) {
    if (pLen < 1 || pLen > PATTMAX)
        return;
    if (sLen < 1 || sLen > STRPATTMAX)
        return;

    srand(time(NULL));

    // generate pattern
    for (int i = 0; i < pLen; i++)
        pattern += (char)(rand() % 26 + 97);

    // generate string
    std::vector<std::string> possibleStrings = {
            "dog", "cat", "fish", "snake", "frog", "bird", "turtle", "horse",
            "chicken", "beef", "octopus", "shrimp", "alligator", "deer", "pork", "lamb",
            "deadbeef", "const", "keyword", "C++", "programming", "happy", "hacking"
    };
    for (int i = 0; i < sLen; i++) {
        str += possibleStrings[rand() % 23];
        str += " ";
    }
}

void generateRandom9x9Matrix(std::vector<std::vector<char>>& matrix) {
    srand(time(NULL));

    int trueorFalse;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            trueorFalse = rand() % 2;
            if (trueorFalse == 0)
                matrix[i][j] = '.';
            else
                matrix[i][j] = rand() % 10;
        }
    }
}

int main() {

    return 0;
}
