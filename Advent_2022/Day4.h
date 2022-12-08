#pragma once
#include "common.h"

#include <fstream>
#include <string>
#include <unordered_set>
#include <utility>

void Day4_Main(Star Part_Of_Day)
{

    std::ifstream DataFile("Input_Data//Day4_Input.txt");
    //std::ifstream DataFile("Input_Data//test.txt");
    std::string line;

    int elf_overlap = 0;

    while (getline(DataFile, line)) {
            //Split the string by elf (no bad data assume , is always present)
            std::string elf1 = line.substr(0, line.find(','));
            std::string elf2 = line.substr(line.find(',') + 1, line.size());

            //Get integer representation of elf sections
            int elf1_min = atoi(elf1.substr(0, elf1.find('-')).c_str());
            int elf1_max = atoi(elf1.substr(elf1.find('-') + 1, elf1.size()).c_str());
            int elf2_min = atoi(elf2.substr(0, elf2.find('-')).c_str());
            int elf2_max = atoi(elf2.substr(elf2.find('-') + 1, elf2.size()).c_str());

        if (Part_Of_Day == Part_1) {
            //does elf1 contain elf2
            if (elf1_min < elf2_min) {
                if (elf1_max >= elf2_max) {
                    //elf1 contains elf1
                    elf_overlap++;
                }
            } else if (elf1_min > elf2_min) {
                //does elf2 contain elf 1
                if (elf1_max <= elf2_max) {
                    //elf1 contains elf1
                    elf_overlap++;
                }
            } else if (elf1_min == elf2_min) {
                //if they start at the same min they must overlap
                elf_overlap++;
            }
        } else {
            if (elf1_min < elf2_min) {
                if (elf1_max >= elf2_min) {
                    //elf1 contains elf1
                    elf_overlap++;
                }
            } else if (elf1_min > elf2_min) {
                //does elf2 contain elf 1
                if (elf1_min <= elf2_max) {
                    //elf1 contains elf1
                    elf_overlap++;
                }
            } else if (elf1_min == elf2_min) {
                //if they start at the same min they must overlap
                elf_overlap++;
            }
        }

        int test = 0;
    }

    std::cout << elf_overlap << std::endl;

    DataFile.close();
}