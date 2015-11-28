#include <iostream>
#include <chrono>
#include "Process.h"
#include "File.h"

using namespace std;
using namespace chrono;


int main(int argc, char* argv[]) {

    // TIME START
    typedef high_resolution_clock Clock;
    auto start = Clock::now();

    vector<Process> processes_list;
    File file;
    int tasks_amount = -1; //first n tasks

    // READING FILE NAME
    if (argc > 1) {
        file.name = argv[1];
        //cout << "argv[1]= " << argv[1] << endl;
        //cout << "argc = " << argc << endl;
    }
    else {
        cout << "The file was not found. Please, enter the name of the file.\nThe file must be in the same directory as ParallelTasks.\n";
        return 0;
    }

    // READING TASKS_AMOUNT
    if (argc > 2) {
        tasks_amount = stoi(argv[2]);
        cout << "Tasks_amount = " << tasks_amount << endl;
    }

    processes_list = file.reading(file.name, tasks_amount);
    if (processes_list.empty()) {
        return 0;
    }
    file.parallelTask(processes_list);

    // TIME END
    auto end = Clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    cout << "Elapsed time: " << duration.count()/ 1000000000.0 << " seconds" << endl;

    return 0;

}