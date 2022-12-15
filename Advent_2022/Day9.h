#pragma once
#include "common.h"

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

int Day9_Main(Star Part_Of_Day)
{
    std::ifstream DataFile("Input_Data//Day9_Input.txt");
    //std::ifstream DataFile("Input_Data//test.txt");
    std::string line;

    //Start at 0,0 wherever that ends up being
    std::pair<int, int> Head{ 0, 0 };
    std::pair<int, int> Tail{ 0, 0 };
    
    std::vector<std::pair<int, int>> knots;

    int num_knots = 0;
    if (Part_Of_Day == Part_1) {
        num_knots = 1;
    } else {
        num_knots = 9;
    }

    for (int i = 0; i < num_knots; i++) {
        knots.push_back(std::make_pair(0, 0));
    }

    std::set<std::pair<int, int>> T_locations;
    int lines = 0;
    while (getline(DataFile, line)) {
        //Read the line into movement for H
        char dir = line[0];
        int steps = atoi(line.substr(line.find_first_of(" ") + 1).c_str());

        int* pMove;
        int posDir = 0;

        if (dir == 'R' || dir == 'L') {
            pMove = &Head.first;
        } else {
            pMove = &Head.second;
        }

        if (dir == 'R' || dir == 'U') {
            posDir = 1;
        } else {
            posDir = -1;
        }

        while (steps != 0) {
            //Modify the head value
            *pMove = *pMove + (1 * posDir);

            std::pair<int, int>* prevKnot = &Head;

            //Check all values behind in list
            for (int i = 0; i < knots.size(); i++) {
                std::pair<int, int> *knot = &knots[i];

                //First = X, Second = Y (X, Y coords)
                int x_dif = prevKnot->first  - knot->first;
                int y_dif = prevKnot->second - knot->second;

                int x_dir = x_dif >= 0 ? 1 : -1;
                int y_dir = y_dif >= 0 ? 1 : -1;

                int x_abs = abs(x_dif);
                int y_abs = abs(y_dif);

                if (lines == 67) {
                    int test = 0;
                }

                if (x_abs > 2 || y_abs > 2) {
                    int test = 0;
                }

                if (x_abs == 2 && y_abs == 2) {
                    knot->first += (1 * x_dir);
                    knot->second += (1 * y_dir);
                } else if (x_abs > 1 && y_abs >= 1) {
                    //Go to same row as H (Y values equal)
                    knot->second = prevKnot->second;
                    knot->first += (1 * x_dir);
                } else if (x_abs >= 1 && y_abs > 1) {
                    //Goto same column as H (X values equal)
                    knot->first = prevKnot->first;
                    knot->second += (1 * y_dir);
                } else if (x_abs > 1) {
                    knot->first += (1 * x_dir);
                } else if (y_abs > 1) {
                    knot->second += (1 * y_dir);
                }

                x_dif = prevKnot->first - knot->first;
                y_dif = prevKnot->second - knot->second;

                x_abs = abs(x_dif);
                y_abs = abs(y_dif);

                if (x_abs > 2 || y_abs > 2) {
                    int test = 0;
                }

                prevKnot = knot;
            }
            steps--;
            T_locations.insert(knots.back());
        }
       
        int test = 0;
        lines++;
    }
    DataFile.close();

    return T_locations.size();
}