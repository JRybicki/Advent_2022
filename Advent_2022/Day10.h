#pragma once
#include "common.h"

#include <fstream>
#include <string>
#include <vector>
#include <array>

int Day10_Main(Star Part_Of_Day)
{
    std::ifstream DataFile("Input_Data//Day10_Input.txt");
    //std::ifstream DataFile("Input_Data//test.txt");
    std::string line;

    int cycle = 1;
    int x_reg = 1;
    int temp_x = 0;
    int temp_cycle = 0;

    int sumStr = 0;

    //Rows of 40 pixels
    //Sprite is 3 pixels wide and 1 pixel is drawn per cycle
    std::vector<std::array<char, 40>> screen;
    int sprInd = 0;

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
            if (cycle % 40 == 20 && cycle > 0) {
                sumStr += cycle * x_reg;
            }
            
            std::array<char, 40>* curLine;

            //Want this to happen at 0 as well
            if (((cycle - 1) / 40) >= screen.size()) {
                std::array<char, 40> line{ ' ' };
                screen.push_back(line);

                curLine = &screen.back();
            } else {
                int index = (cycle - 1) / 40;
                curLine = &screen[index];
            }

            char draw = '.';
            if ((cycle - ((screen.size() - 1) * 40) - x_reg <= 2) && (cycle - ((screen.size() - 1) * 40) - x_reg >= 0)) {
                draw = '#';
            }

            curLine->at(cycle - 1 - ((screen.size() - 1) * 40)) = draw;
            cycle++;
        }
        
        x_reg += temp_x;
        sprInd = x_reg - 1 - ((screen.size() - 1) * 40);
        int test = 0;
    }

    for (int i = 0; i < screen.size(); i++) {
        std::array<char, 40> arr = screen[i];

        for (int i = 0; i < 40; i++) {
            std::cout << arr[i];
        }
        std::cout << std::endl;
    }

    DataFile.close();

    return sumStr;
}