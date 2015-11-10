#ifndef PARALLELTASKS_FILEREADING_H
#define PARALLELTASKS_FILEREADING_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <iomanip>
#include <string.h>
#include <array>
#include <iostream>
#include "Process.h"


using namespace std;

class File {
public:
    string helper;
    int maxJobs;
    int maxRecords;
    int maxProcs;
    int maxNodes;

    vector<Process> reading(string name_of_file, int task_amount);

    File() { cout << "File created!" << endl; }
    ~File() { cout << "File destructed!" << endl;}

    void parallelTask(vector<Process> processes_list);
};


#endif //PARALLELTASKS_FILEREADING_H
