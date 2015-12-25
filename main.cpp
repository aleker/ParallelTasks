#include <iostream>
#include <chrono>
#include <sstream>
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
        cout << "The file was not found. Please, enter the name of the file.\n"
                "The file must be in the same directory as ParallelTasks.\n";
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
    file.start2 = clock();
    //file.parallelTask(processes_list);
    file.simulatedAnnealing(processes_list);

    // TIME END
    auto end = Clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    cout << "Elapsed time: " << duration.count()/ 1000000000.0 << " seconds" << endl;

//    for (int i = 0; i <= 10; i++) {
//        int rand_procs_number = rand() % (30 - 3 - 0) + 0;
//        cout << rand_procs_number << endl;
//    }

    return 0;

}