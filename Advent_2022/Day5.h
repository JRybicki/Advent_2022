#pragma once
#include "common.h"

#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <stack>

void Day5_Main(Star Part_Of_Day)
{
    std::ifstream DataFile("Input_Data//Day5_Input.txt");
    //std::ifstream DataFile("Input_Data//test.txt");
    std::string line;

    int elf_overlap = 0;
    bool stackInit = false;
    std::vector<std::stack<char>> stacks;
    std::vector<std::string> stackLines;

    while (getline(DataFile, line)) {

        //Create the initial stacks
        if (!line.empty()) {
            if (stackInit == false) {
                //store lines in a vector because will need to reverse for stack
                stackLines.push_back(line);
            } else {
                //Start modifying the stack based on insctructions
                const char delimit = ' ';
                int pos1 = 0;
                int pos2 = 0;
                enum insType {
                    Count,
                    From,
                    To,
                    NUM_INSTRUCTIONS
                };
                int moveIns[NUM_INSTRUCTIONS];

                for (int i = 0; i < NUM_INSTRUCTIONS; i++) {
                    //numbers are between spaces
                    pos1 = line.find(delimit, pos1) + 1;
                    pos2 = line.find(delimit, pos1);

                    moveIns[i] = atoi(line.substr(pos1, pos2 - pos1).c_str());
                    pos1 = pos2 + 1;
                }
                
                if (Part_Of_Day == Part_1) {
                    //Perform move instructions (How many, from, to) (1 offset)
                    for (int i = 0; i < moveIns[Count]; i++) {
                        char crate = stacks[moveIns[From] - 1].top();
                        stacks[moveIns[From] - 1].pop();

                        stacks[moveIns[To] - 1].push(crate);
                    }
                } else {
                    //Move all crates at once

                    //intermediate stack
                    std::stack<char> tempStack;
                    for (int i = 0; i < moveIns[Count]; i++) {
                        char crate = stacks[moveIns[From] - 1].top();
                        stacks[moveIns[From] - 1].pop();
                        tempStack.push(crate);
                    }

                    for (int i = 0; i < moveIns[Count]; i++) {
                        char crate = tempStack.top();
                        tempStack.pop();

                        stacks[moveIns[To] - 1].push(crate);
                    }

                }


            }
        } else {
            stackInit = true;
            stackLines.pop_back();

            std::reverse(stackLines.begin(), stackLines.end());

            for (std::string stackLine : stackLines) {
                //Take advantage of the input spacing
                //ex. [Z] [M] [P]
                int ind = 1;
                int stackInd = 0;
                while (ind < stackLine.size()) {
                    //This will init vector first time through
                    if (stacks.size() <= stackInd) {
                        //create a new stack
                        std::stack<char> curStack;
                        stacks.push_back(curStack);
                    }
                    char c = stackLine[ind];
                    if (c != ' ') {
                        stacks[stackInd].push(c);
                    }
                    ind += 4;
                    stackInd++;
                }
            }
        }
    }
    
    for (int i = 0; i < stacks.size(); i++) {
        std::cout << stacks[i].top();
    }
    std::cout << std::endl;
    DataFile.close();
}