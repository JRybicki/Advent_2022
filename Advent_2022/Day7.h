#pragma once
#include "common.h"

#include <fstream>
#include <string>
#include <list>
#include <set>
#include <unordered_map>
#include <algorithm>

struct folder {

    folder* parent;
    folder* child;
    folder* next;

    std::string name;
    int size;
    std::unordered_map<std::string, int> fileList;

    //Pointers are cool
    int sumTotal() {
        //Start with current child
        int sumSize = this->size;

        folder* pFolder = this->child;

        while (pFolder != nullptr) {
            sumSize += pFolder->sumTotal();
            pFolder = pFolder->next;
        }

        return sumSize;
    }

    folder(std::string folderName, folder* parentFolder) : size(0) { 
        name   = folderName;
        parent = parentFolder;
        child  = nullptr;
        next   = nullptr;
    }
};

int Day7_Main(Star Part_Of_Day)
{
    std::ifstream DataFile("Input_Data//Day7_Input.txt");
    //std::ifstream DataFile("Input_Data//test.txt");
    std::string line;

    const char CMD_CHAR = '$';
    const std::string FOLDER_STRING = "dir";
    std::set<int> dirSizes;

    folder* rootFolder = new folder("/", nullptr);
    folder* curFolder = rootFolder;
    std::list<folder*> dirList{ rootFolder };

    while (getline(DataFile, line)) {
        if (line[0] == CMD_CHAR) {
            //cd or ls
            if (line.find("cd") != std::string::npos) {

                //Assume we have already been added with a dir
                std::string cdName = line.substr(line.find_last_of(" ") + 1);
                folder* tempFolder = curFolder->child;

                //Iterate the list until we find the sub folder
                while (tempFolder != nullptr) {
                    if (tempFolder->name.compare(cdName) == 0) {
                        curFolder = tempFolder;
                        break;
                    } else {
                        tempFolder = tempFolder->next;
                    }
                }

                if (line.find("..") != std::string::npos) {
                    //Go up a directory
                    curFolder = curFolder->parent;
                }

            } else if (line.find("ls") != std::string::npos) {
                //we don't actually need to do anything for this
            }

        } else if (line.find("dir") != std::string::npos) {
            //Add to the set of subfolders, don't need to check if it's already there (I think)
            std::string subDirName = line.substr(line.find_last_of(" ") + 1);
            folder* newFolder = new folder(subDirName, curFolder);

            //Put the back of the child list here
            if (curFolder->child != nullptr) {
                folder* tempFolder = curFolder->child;
                while (tempFolder->next != nullptr) {
                    tempFolder = tempFolder->next;
                }
                tempFolder->next = newFolder;
            } else {
                curFolder->child = newFolder;
            }

            dirList.push_back(newFolder);
        } else {
            //This is a file
            int fileSize = atoi(line.substr(0, line.find_last_of(" ")).c_str());
            std::string fileName = line.substr(line.find_last_of(" ") + 1);

            curFolder->fileList.insert(std::make_pair(fileName, fileSize));
            curFolder->size += fileSize;
        }
    }


    //Iterate over folders to get file sizes
    int rmFolderSize = 0;

    if (Part_Of_Day == Part_1) {
        for (auto const& pFolder : dirList) {
            int folderSize = pFolder->sumTotal();
            if (folderSize < 100000) {
                rmFolderSize += folderSize;
            }
            dirSizes.insert(folderSize);
        }
    } else {
        const int TOTAL_SIZE = 70000000;
        const int UPDATE_SIZE = 30000000;

        int diskFree = TOTAL_SIZE - rootFolder->sumTotal();
        int spaceNeed = UPDATE_SIZE - diskFree;

        for (auto const& pFolder : dirList) {
            int folderSize = pFolder->sumTotal();
            dirSizes.insert(folderSize);
        }

        //iterate list until best folder size is found
        for (auto const& curSize : dirSizes) {
            if (curSize > spaceNeed) {
                rmFolderSize = curSize;
                break;
            }
        }
    }

    DataFile.close();

    return rmFolderSize;
}