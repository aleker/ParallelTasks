#include <iostream>
#include "Process.h"
#include "File.h"

using namespace std;

int main(int argc, char* argv[]) {

    //clock_t beg_time = clock();
    vector<Process> processes_list;
    File file;
    string file_name = "Files/test3.txt";
    int tasks_amount = -1; //first n tasks

    // READING FILE NAME
    if (argc > 1) {
        file_name = argv[1];
        cout << "argv[1]= " << argv[1] << endl;
        cout << "argc = " << argc << endl;
    }

    // READING TASKS_AMOUNT
    if (argc > 2) {
        tasks_amount = stoi(argv[2]);
        cout << "Tasks_amount = " << tasks_amount << endl;
    }
    processes_list = file.reading(file_name, tasks_amount);

    // DISPLAY LIST OF PROCESSES
    for (Process task: processes_list) {
        task.display();
    }
    cout << endl;

    file.parallelTask(processes_list);

    // DISPLAY TIME
    //sleep(10);
    //clock_t end_time = clock();
    //double duration = (end_time - beg_time )/(double) CLOCKS_PER_SEC;
    //cout << duration << endl;

    return 0;
}