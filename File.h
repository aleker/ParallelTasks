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
#include <tgmath.h>
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
    unsigned int averageReadyTime;
    unsigned int averageProcsAmount;
    int lastTaskTime = 0;
    int old_last_task_time = 0;

    File() { /* cout << "File created!" << endl; */ }
    ~File() { /* cout << "File destructed!" << endl; */ }

    vector<Process> reading(string name_of_file, int task_amount);
    void parallelTask(vector<Process> processes_list);
    vector<Process> findAlternativeSolution(vector<Process> processes_list) throw(string);
    void simulatedAnnealing(vector<Process> processes_list);
    void saveToFile(vector<Process> processes_vector, string type);
    void averageCalculating(vector<Process> processes_list);

};


#endif //PARALLELTASKS_FILEREADING_H
