#pragma once
#include "common.h"

#include <fstream>
#include <string>
#include <vector>
#include <queue>

enum ops {
    add,
    mult,
    square
};


struct monkey {
    std::queue<unsigned long long> items;

    unsigned long long opVal;
    ops addOp;

    int testVal;

    int trueMonkey;
    int falsMonkey;
     
    long long totalInspect;

    monkey() : opVal(0), addOp(add), testVal(0), trueMonkey(0), falsMonkey(0), totalInspect(0) { }


};

bool sortByBus(const monkey& lhs, const monkey& rhs) { return lhs.totalInspect > rhs.totalInspect; }

int Day11_Main(Star Part_Of_Day)
{
    std::ifstream DataFile("Input_Data//Day11_Input.txt");
    //std::ifstream DataFile("Input_Data//test.txt");
    std::string line;


    std::vector<monkey> monkeyList;
    std::vector<std::string> monkeyData;

    while (getline(DataFile, line)) {

        monkeyData.push_back(line);
        if (monkeyData.size() > 5) {
            monkey newMonkey;

            //parse item list
            std::string line = monkeyData[1];
            int offset = line.find_first_of(":");
            offset = line.find_first_of(" ", offset);
            while (offset != std::string::npos)
            {
                newMonkey.items.push(atoi(line.substr(offset + 1, 2).c_str()));
                offset = line.find_first_of(" ", offset + 1);
            }
            
            //Get operation number and operator
            line = monkeyData[2];
            newMonkey.opVal = atoi(line.substr(line.find("old") + 6).c_str());

            if (line.find("+") != std::string::npos) {
                newMonkey.addOp = add;
            } else {
                int multIndex = line.find("*");

                if (line.find("old", multIndex) != std::string::npos) {
                    newMonkey.addOp = square;
                } else {
                    newMonkey.addOp = mult;
                }
            }

            //Get test number
            line = monkeyData[3];
            newMonkey.testVal = atoi(line.substr(line.find("by") + 3).c_str());

            //Get true number
            line = monkeyData[4];
            newMonkey.trueMonkey = atoi(line.substr(line.find("monkey") + 7).c_str());

            //Get false number
            line = monkeyData[5];
            newMonkey.falsMonkey = atoi(line.substr(line.find("monkey") + 7).c_str());

            monkeyList.push_back(newMonkey);
            monkeyData.clear();
            //skip the next line of data
            getline(DataFile, line);
        }
    }
    int numRounds = 20;
    if (Part_Of_Day == Part_2) {
        numRounds = 10000;
    }

    unsigned long long lcm = 1;
    for (int i = 0; i < monkeyList.size(); i++) {
        lcm *= monkeyList[i].testVal;
    }

    for (int round = 0; round < numRounds; round++) {
        //parse data
        for (int i = 0; i < monkeyList.size(); i++) {
            monkey* curMonkey = &monkeyList[i];
            while (!curMonkey->items.empty()) {
                unsigned long long worry = curMonkey->items.front();

                worry %= lcm;
                curMonkey->items.pop();
                //perform operation
                if (curMonkey->addOp == add) {
                    //add
                    worry += curMonkey->opVal;
                } else if (curMonkey->addOp == mult) {
                    //multiply
                    worry *= curMonkey->opVal;
                } else {
                    worry = worry * worry;
                }

                //divide by 3
                if (Part_Of_Day == Part_1) {
                    worry /= 3;
                }



                //Check test
                if (worry % curMonkey->testVal == 0) {
                    monkeyList[curMonkey->trueMonkey].items.push(worry);
                } else {
                    monkeyList[curMonkey->falsMonkey].items.push(worry);
                }

                curMonkey->totalInspect++;
            }
        }
    }

    std::sort(monkeyList.begin(), monkeyList.end(), sortByBus);
    long long totalBus = monkeyList[0].totalInspect * monkeyList[1].totalInspect;

    DataFile.close();

    return totalBus;
}