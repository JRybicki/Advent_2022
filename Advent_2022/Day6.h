#pragma once
#include "common.h"

#include <fstream>
#include <string>
#include <unordered_map>

int Day6_Main(Star Part_Of_Day)
{
    std::ifstream DataFile("Input_Data//Day6_Input.txt");
    //std::ifstream DataFile("Input_Data//test.txt");
    std::string line;
    int endKey = 0;

    while (getline(DataFile, line)) {
        //2 pointers thing maybe
        int p1 = 0;
        int p2 = 0;

        std::unordered_map<char, int> mark;
        int lenMark = 0;
        if (Part_Of_Day == Part_1) {
            lenMark = 4;
        } else {
            lenMark = 14;
        }

        while (mark.size() < lenMark) {
            auto it = mark.find(line[p2]);
            if (it != mark.end())
            {
                //Erase everything between p1 and the location of the it
                int pos = it->second;
                for (int i = p1; i < pos + 1; i++) {
                    mark.erase(line[i]);
                }
                p1 = pos + 1;
            }
            mark.insert(std::make_pair(line[p2], p2));
            p2++;
        }

        endKey = p2;
    }
    DataFile.close();

    return endKey;
}