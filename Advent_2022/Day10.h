#pragma once
#include "common.h"

#include <fstream>
#include <string>
#include <vector>
#include <array>

int Day10_Main(Star Part_Of_Day)
{
    //std::ifstream DataFile("Input_Data//Day10_Input.txt");
    std::ifstream DataFile("Input_Data//test.txt");
    std::string line;

    int cycle = 1;
    int x_reg = 1;
    int temp_x = 0;
    int temp_cycle = 0;

    int sumStr = 0;

    //Rows of 40 pixels
    //Sprite is 3 pixels wide and 1 pixel is drawn per cycle
    std::vector<std::array<int, 40>> screen;


    while (getline(DataFile, line)) {
        if (line.find("noop") != std::string::npos) {
            temp_cycle = 1;
            temp_x = 0;
        } else if (line.find("addx") != std::string::npos) {
            int x_val = atoi(line.substr(line.find_first_of(" ")).c_str());
            temp_cycle = 2;
            temp_x = x_val;
        }

        for (int i = 0; i < temp_cycle; i++) {
            if (cycle % 40 == 20) {
                sumStr += cycle * x_reg;
            }
            cycle++;
        }
        x_reg += temp_x;
        int test = 0;
    }
    DataFile.close();

    return sumStr;
}