#ifndef PARALLELTASKS_FILEREADING_H
#define PARALLELTASKS_FILEREADING_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <iomanip>
#include <string>
#include <array>
#include <iostream>
#include <fstream>
#include "Process.h"


using namespace std;


class File {
public:
    string helper;
    string name;
    int maxJobs;
    int maxRecords;
    int maxProcs;
    int maxNodes;

    File() { /* cout << "File created!" << endl; */ }
    ~File() { /* cout << "File destructed!" << endl; */ }

    vector<Process> reading(string name_of_file, int task_amount);
    void parallelTask(vector<Process> processes_list);
    void findAlternativeSolution() throw(string);

};


#endif //PARALLELTASKS_FILEREADING_H
