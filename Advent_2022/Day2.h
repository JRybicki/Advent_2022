#pragma once

#include <fstream>
#include <iostream>
#include <string>

//1 = rock, 2 = paper, 3 = scizzors
void Day2_Main(bool part1)
{
    std::ifstream DataFile("Input_Data//Day2_Input.txt");
    std::string line;

    int totalScore = 0;

    while (getline(DataFile, line)) {
        //Characters are hard coded in the same spot
        char hand1 = line[0];
        char hand2 = line[2];

        //PLayer hand converted to A,B,C
        char handConvert = hand2 - 23;
        int winPoints = 0;

        if (part1) {
            //Rock
            if (hand1 == 'A') {
                if (hand2 == 'Y') {
                    //win
                    winPoints = 6;
                } else if (hand2 == 'X') {
                    //tie
                    winPoints = 3;
                }
            } else if (hand1 == 'B') {
                if (hand2 == 'Z') {
                    //win
                    winPoints = 6;
                } else if (hand2 == 'Y') {
                    //tie
                    winPoints = 3;
                }
            } else if (hand1 == 'C') {
                if (hand2 == 'X') {
                    //win
                    winPoints = 6;
                } else if (hand2 == 'Z') {
                    //tie
                    winPoints = 3;
                }
            }

            int handPoint = hand2 - 87;
            int score = winPoints + handPoint;

            totalScore += score;
        } else {
            //X = lose, Y = draw, Z = win
            int handPoint = 0;
            if (hand2 == 'Y') {
                winPoints = 3;
                handPoint = (hand1 - 64);
            } else if (hand2 == 'Z') {
                winPoints = 6;
                handPoint = ((hand1 - 64) % 3) + 1;
            } else {
                //hand2 == 'X'
                winPoints = 0;
                handPoint = hand1 == 'A' ? 3 : (hand1 - 64) - 1;
            }

            int score = winPoints + handPoint;

            totalScore += score;
        }
    }

    DataFile.close();
}