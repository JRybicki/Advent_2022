#pragma once
#include "common.h"

#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>

int Day3_Main(Star Part_Of_Day)
{
    std::ifstream DataFile("Input_Data//Day3_Input.txt");
    //std::ifstream DataFile("Input_Data//test.txt");
    std::string line;

    int totalScore = 0;

    std::vector<std::unordered_set<char>> group;
    int bagIndex = 0;

    while (getline(DataFile, line)) {

        if (Part_Of_Day == Part_1) {
            //Create a set of the first half
            std::unordered_set<char> part1;

            for (int i = 0; i < line.size() / 2; i++) {
                part1.insert(line.at(i));
            }

            char dupe_item;
            for (int i = line.size() / 2; i < line.size(); i++) {
                dupe_item = line.at(i);
                //CHeck if this item is in part 1 of sack
                if (part1.count(dupe_item) != 0) {
                    break;
                }
            }

            int priority_sub = dupe_item > 'Z' ? 96 : 38;
            int item_priority = dupe_item - priority_sub;

            totalScore += item_priority;
        } else {
            std::unordered_set<char> bag;
            for (int i = 0; i < line.size(); i++) {
                bag.insert(line.at(i));
            }
            group.push_back(bag);

            if (bagIndex == 2) {
                std::unordered_set<char> commonChars;

                //check the first two bags and find common characters
                std::unordered_set<char> smallBag = group[0].size() > group[1].size() ? group[1] : group[0];
                std::unordered_set<char> largeBag = group[0].size() > group[1].size() ? group[0] : group[1];

                for (char c : largeBag) {
                    if (smallBag.count(c) != 0) {
                        commonChars.insert(c);
                    }
                }

                //Now check that common list against the third
                smallBag = group[2].size() > commonChars.size() ? commonChars : group[2];
                largeBag = group[2].size() > commonChars.size() ? group[2] : commonChars;

                char badgeChar;
                for (char c : largeBag) {
                    if (smallBag.count(c) != 0) {
                        badgeChar = c;
                        break;
                    }
                }

                int priority_sub = badgeChar > 'Z' ? 96 : 38;
                int item_priority = badgeChar - priority_sub;

                totalScore += item_priority;

                //Reset for next group
                bagIndex = 0;
                group.clear();
            } else {
                bagIndex++;
            }
        }
    }

    DataFile.close();
    return totalScore;
}