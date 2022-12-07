#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <set>

void Day1_Main()
{
    std::ifstream DataFile("inputPath//Day1_Input.txt");
    std::string line;

    int elf_max = 0;
    int cur_elf_calories = 0;

    //This is lazy and we are also assuming no elves will have the same amount of food
    std::set<int> elf_calories;

    int top1 = 0;
    int top2 = 0;
    int top3 = 0;

    //Output the text from the file
    while (getline(DataFile, line)) {
        if (!line.empty()) {
            //Elf has more food
            cur_elf_calories += atoi(line.c_str());
        } else {
            //end of list for elf
            //elf_max = (elf_max < cur_elf_calories) ? cur_elf_calories : elf_max;

            if (cur_elf_calories > top1) {
                top3 = top2;
                top2 = top1;
                top1 = cur_elf_calories;
            } else if (cur_elf_calories > top2) {
                top3 = top2;
                top2 = cur_elf_calories;
            } else if (cur_elf_calories > top3) {
                top3 = cur_elf_calories;
            }

            elf_calories.insert(cur_elf_calories);
            cur_elf_calories = 0;
        }
    }

    //add the last elf
    elf_calories.insert(cur_elf_calories);
    cur_elf_calories = 0;

    auto it = elf_calories.rbegin();
    std::cout << "most elf calories: " << *it << std::endl;

    const int NUM_TOP_ELF = 3;
    int sum_top_elf = 0;
    for (int i = 0; i < NUM_TOP_ELF; i++) {
        sum_top_elf += *it;
        ++it;
    }
    std::cout << "top elf calories: " << sum_top_elf << std::endl;


    DataFile.close();
}