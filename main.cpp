#include <iostream>
#include <time.h>
#include "HashMapSolutions.h"

const int NUM_TEST_CASES = 30;

const int VECMAX = 5E4;
const int STRMAX = 15;
const int PATTMAX = 300;
const int STRPATTMAX = 3000;

// ********************************************************
// ********************************************************
// ********************LESSER FUNCTION*********************
// ********************************************************
// ********************************************************

void print1DVector(const std::vector<int>& nums) {
    if (nums.size() == 0) {
        std::cout << "[]" << std::endl;
        return;
    }

    std::cout << "[";
    for (auto it = nums.begin(); it != nums.end(); it++) {
        if (it == nums.begin() + nums.size() - 1)
            std::cout << *it << "]" << std::endl;
        else
            std::cout << *it << ", ";
    }
}

void printSudokuBoard(const std::vector<std::vector<char>>& board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << board[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

// ********************************************************
// ********************************************************
// ******************END LESSER FUNCTION*******************
// ********************************************************
// ********************************************************

void generateVector(std::vector<int>& copy, const int size) {
    if (size < 1 || size > VECMAX)
        return;

    copy.clear();
    copy.reserve(size);

    //srand(time(NULL));
    for (int i = 0; i < size; i++)
        copy.push_back(rand() % 11);
}

void generateRomanNumeralString(std::string& copy, const int size) {
    if (size < 1 || size > STRMAX)
        return;

    //srand(time(NULL));

    copy.clear();
    copy.reserve(size);

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

    //srand(time(NULL));

    pattern.clear();
    pattern.reserve(pLen);
    str.clear();
    str.reserve(sLen);

    // generate pattern
    for (int i = 0; pattern.size() < pLen; i++)
        pattern += (char)(rand() % 26 + 97);

    // generate string
//    std::vector<std::string> possibleStrings = {
//            "dog", "cat", "fish", "snake", "frog", "bird", "turtle", "horse",
//            "chicken", "beef", "octopus", "shrimp", "alligator", "deer", "pork", "lamb",
//            "deadbeef", "const", "keyword", "C++", "programming", "happy", "hacking"
//    };
    std::vector<std::string> possibleStrings = {
            "dog", "cat", "fish",
            "chicken", "beef",
            "deadbeef", "happy", "hacking"
    };
    for (int i = 0; str.size() < sLen; i++) {
        str += possibleStrings[rand() % 8]; // <--- depending on which possibleStrings, % will change based on # of strs
        str += " ";
    }
}

void generateRandom9x9Matrix(std::vector<std::vector<char>>& matrix) {
//    srand(time(NULL));

    int trueorFalse;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            trueorFalse = rand() % 11;
            if (trueorFalse <= 8)
                matrix[i][j] = '.';
            else
                matrix[i][j] = rand() % 10 + 48;
        }
    }
}

void testCase1() {
    HashMap instance;
    std::vector<int> numVec;
    unsigned int i;

    std::cout << "****************************************" << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "*****BEGIN TESTING MAJORITY ELEMENT*****" << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "****************************************" << std::endl << std::endl;

    // test empty arr
    std::cout << "Current vector's contents are: ";
    print1DVector(numVec);

    std::cout << "The output of the function is: " << instance.majorityElement(numVec) << std::endl << std::endl;


    // test one element arr
    numVec.push_back(7);

    std::cout << "Current vector's contents are: ";
    print1DVector(numVec);

    std::cout << "The output of the function is: " << instance.majorityElement(numVec) << std::endl << std::endl;

    numVec.clear();

    // test multiple random num, random size arrs
//    srand(time(NULL));
    for (i = 0; i < NUM_TEST_CASES; i++) {
        generateVector(numVec, rand()% 21);

        std::cout << "Current vector's contents are: ";
        print1DVector(numVec);

        std::cout << "The output of the function is: " << instance.majorityElement(numVec) << std::endl << std::endl;

        numVec.clear();
    }

    std::cout << "****************************************" << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "******END TESTING MAJORITY ELEMENT******" << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "****************************************" << std::endl << std::endl;
}

void testCase2() {
    HashMap instance;
    std::string romanNumerals = "";
    unsigned int i;

    std::cout << "****************************************" << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "*******BEGIN TESTING ROMAN TO INT*******" << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "****************************************" << std::endl << std::endl;

    // test empty string
    std::cout << "The contents of the current string are: \"" << romanNumerals << "\"." << std::endl;
    std::cout << "The function's output: " << instance.romanToInt(romanNumerals) << std::endl << std::endl;

    romanNumerals.clear();

    // test multiple random roman numerals
    for (i = 0; i < NUM_TEST_CASES; i++) {
        generateRomanNumeralString(romanNumerals, rand() % 16 + 1);

        std::cout << "The contents of the current string are: \"" << romanNumerals << "\"." << std::endl;
        std::cout << "The function's output: " << instance.romanToInt(romanNumerals) << std::endl << std::endl;

        romanNumerals.clear();
    }

    std::cout << "****************************************" << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "********END TESTING ROMAN TO INT********" << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "****************************************" << std::endl << std::endl;
}

void testCase3() {
    HashMap instance;
    std::string pat;
    std::string sequence;
    unsigned int i;

    std::cout << "****************************************" << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "*******BEGIN TESTING WORD PATTERN*******" << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "****************************************" << std::endl << std::endl;

    // test known patterns, directly from leetcode
    // since func above works, but, I mean, it's not very great
    pat = "abab";
    sequence = "dog cat dog cat";

    std::cout << "The pattern contents are: " << pat << std::endl;
    std::cout << "The string sequence is: " << sequence << std::endl;
    std::cout << "The output of the function is: ";
    if (instance.wordPattern(pat, sequence) == 0)
        std::cout << "False." << std::endl << std::endl;
    else
        std::cout << "True." << std::endl << std::endl;

    pat = "aaa";
    sequence = "aa aa aa aa";

    std::cout << "The pattern contents are: " << pat << std::endl;
    std::cout << "The string sequence is: " << sequence << std::endl;
    std::cout << "The output of the function is: ";
    if (instance.wordPattern(pat, sequence) == 0)
        std::cout << "False." << std::endl << std::endl;
    else
        std::cout << "True." << std::endl << std::endl;

    pat = "abab";
    sequence = "dog cat dog fish";

    std::cout << "The pattern contents are: " << pat << std::endl;
    std::cout << "The string sequence is: " << sequence << std::endl;
    std::cout << "The output of the function is: ";
    if (instance.wordPattern(pat, sequence) == 0)
        std::cout << "False." << std::endl << std::endl;
    else
        std::cout << "True." << std::endl << std::endl;

    pat = "ab";
    sequence = "happy hacking";

    std::cout << "The pattern contents are: " << pat << std::endl;
    std::cout << "The string sequence is: " << sequence << std::endl;
    std::cout << "The output of the function is: ";
    if (instance.wordPattern(pat, sequence) == 0)
        std::cout << "False." << std::endl << std::endl;
    else
        std::cout << "True." << std::endl << std::endl;

    pat = "deadbeef";
    sequence = "d e a d b e e f";

    std::cout << "The pattern contents are: " << pat << std::endl;
    std::cout << "The string sequence is: " << sequence << std::endl;
    std::cout << "The output of the function is: ";
    if (instance.wordPattern(pat, sequence) == 0)
        std::cout << "False." << std::endl << std::endl;
    else
        std::cout << "True." << std::endl << std::endl;

    // begin random seeding
    for (i = 0; i < NUM_TEST_CASES + NUM_TEST_CASES; i++) {
        pat.clear();
        sequence.clear();

        generateRandomPattern(pat, sequence, rand() % 5 + 1, rand() % 299 + 1);

        std::cout << "The pattern contents are: " << pat << std::endl;
        std::cout << "The string sequence is: " << sequence << std::endl;
        std::cout << "The output of the function is: ";
        if (instance.wordPattern(pat, sequence) == 0)
            std::cout << "False." << std::endl << std::endl;
        else
            std::cout << "True." << std::endl << std::endl;
    }

    std::cout << "****************************************" << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "********END TESTING ROMAN TO INT********" << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "****************************************" << std::endl << std::endl;
}

void testCase4() {
    HashMap instance;
    std::vector<int> numVec;
    unsigned int i;

    std::cout << "****************************************" << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "****BEGIN TESTING SHORTEST SUBARRAYS****" << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "****************************************" << std::endl << std::endl;

    // test empty arr
    std::cout << "The contents of the vector are: ";
    print1DVector(numVec);

    std::cout << "The output of the function is: Size - " << instance.findShortestSubArray(numVec) << std::endl << std::endl;

    // test arr with one elem
    numVec.push_back(7);
    std::cout << "The contents of the vector are: ";
    print1DVector(numVec);

    std::cout << "The output of the function is: Size - " << instance.findShortestSubArray(numVec) << std::endl << std::endl;

    // test multiple random vecs
    numVec.clear();
    for (i = 0; i < NUM_TEST_CASES + (NUM_TEST_CASES / 2); i++) {
        generateVector(numVec, rand() % 20 + 1);

        std::cout << "The contents of the vector are: ";
        print1DVector(numVec);

        std::cout << "The output of the function is: Size - " << instance.findShortestSubArray(numVec) << std::endl << std::endl;

        numVec.clear();
    }

    std::cout << "****************************************" << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "********END TESTING ROMAN TO INT********" << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "****************************************" << std::endl << std::endl;
}

void testCase5() {
    HashMap instance;
    std::vector<std::vector<char>> sudokuBoard;
    unsigned int i = 0;

    std::cout << "****************************************" << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "****BEGIN TESTING VALID SUDOKU BOARD****" << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "****************************************" << std::endl << std::endl;

    // test known test cases
    sudokuBoard = {
            {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
            {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
            {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
            {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
            {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
            {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
            {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
            {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
            {'.', '.', '.', '.', '8', '.', '.', '7', '9'},
    };

    std::cout << "The board looks like: " << std::endl;
    printSudokuBoard(sudokuBoard);
    std::cout << std::endl << "The output of the function is: ";
    if (instance.isValidSudoku(sudokuBoard) == 0)
        std::cout << "False." << std::endl << std::endl;
    else
        std::cout << "True." << std::endl << std::endl;

    sudokuBoard[0][0] = '8';
    std::cout << "The board looks like: " << std::endl;
    printSudokuBoard(sudokuBoard);
    std::cout << std::endl << "The output of the function is: ";
    if (instance.isValidSudoku(sudokuBoard) == 0)
        std::cout << "False." << std::endl << std::endl;
    else
        std::cout << "True." << std::endl << std::endl;

    // test random inputs
    for (i = 0; i < NUM_TEST_CASES; i++) {
        generateRandom9x9Matrix(sudokuBoard);

        printSudokuBoard(sudokuBoard);
        std::cout << std::endl << "The output of the function is: ";
        if (instance.isValidSudoku(sudokuBoard) == 0)
            std::cout << "False." << std::endl << std::endl;
        else
            std::cout << "True." << std::endl << std::endl;
    }

    sudokuBoard.clear();

    std::cout << "****************************************" << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "*****END TESTING VALID SUDOKU BOARD*****" << std::endl;
    std::cout << "****************************************" << std::endl;
    std::cout << "****************************************" << std::endl << std::endl;
}

int main() {
    srand(time(NULL));

    testCase1();
    testCase2();
    testCase3();
    testCase4();
    testCase5();

    return 0;
}
