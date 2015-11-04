#ifndef PARALLELTASKS_FILEREADING_H
#define PARALLELTASKS_FILEREADING_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <iomanip>
#include <string.h>

using namespace std;

class File {
public:
    string helper;
    int maxJobs;
    int maxRecords;
    int maxProcs;
    int maxNodes;

    bool reading();

    File() { cout << "File created!" << endl; }
};


#endif //PARALLELTASKS_FILEREADING_H
