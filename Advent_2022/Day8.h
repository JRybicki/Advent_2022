#pragma once
#include "common.h"

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int Day8_Main(Star Part_Of_Day)
{
    std::ifstream DataFile("Input_Data//Day8_Input.txt");
    //std::ifstream DataFile("Input_Data//test.txt");
    std::string line;

    std::vector<std::vector<int>> treeGrid;
    int treeVisible = 0;
    while (getline(DataFile, line)) {
        //Create grid
        std::vector<int> rowVec;
        for (char c : line) {
            rowVec.push_back(int(c) - 48);
        }

        treeGrid.push_back(rowVec);
    }

    //Add top and bottom
    treeVisible += treeGrid.front().size();
    treeVisible += treeGrid.back().size();

    int rowIndex = 1;
    int maxScore = 0;
    for (auto it = treeGrid.begin() + 1; it != treeGrid.end() - 1; ++it) {
        std::vector<int> curRow = *it;
        
        //Add 2 for left and rightmost tree
        treeVisible += 2;

        //iterate rest of trees
        for (int i = 1; i < curRow.size() - 1; i++) {

            bool lVisible = true;
            bool rVisible = true;
            bool uVisible = true;
            bool dVisible = true;
            int lscore = 0;
            int rscore = 0;
            int uscore = 0;
            int dscore = 0;
            int totalscore = 0;

            //Check left
            for (int left = i - 1; left >= 0; left--) {
                lscore++;
                if (curRow[left] >= curRow[i]) {
                    //left is good
                    lVisible = false;
                    break;
                }
            }

            //Check right
            for (int right = i + 1; right < curRow.size(); right++) {
                rscore++;
                if (curRow[right] >= curRow[i]) {
                    //right is good
                    rVisible = false;
                    break;
                }
            }

            //Check up
            for (int up = rowIndex - 1; up >= 0; up--) {
                uscore++;
                if (treeGrid[up][i] >= curRow[i]) {
                    //up is good
                    uVisible = false;
                    break;
                }
            }

            //Check down
            for (int down = rowIndex + 1; down < treeGrid.size(); down++) {
                dscore++;
                if (treeGrid[down][i] >= curRow[i]) {
                    //down is good
                    dVisible = false;
                    break;
                }
            }

            if (lVisible || rVisible || uVisible || dVisible) {
                treeVisible++;
            }

            totalscore = lscore * rscore * uscore * dscore;
            maxScore = totalscore > maxScore ? totalscore : maxScore;
        }

        //index to next row counter
        rowIndex++;
    }

    DataFile.close();

    if (Part_Of_Day == Part_1) {
        return treeVisible;
    }

    return maxScore;
}