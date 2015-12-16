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

    // FOR TESTING
    ofstream output;
    stringstream output_name;
    output_name << "TEST." << file.name;
    output.open(output_name.str().c_str());
    if( !output.good() ) {
        cout << "Output file is not good enough, my soldier!" << endl;
        return 0;
    }
    int tab[3] = {1,2,5};
    for (int z = 1; z < 16; z++) {
        cout << z << endl;
        for (int j = 1; j <= 10000; j *= 10) {
            for (int i = 0; i < 3; i++) {
                cout << tab[i] * j << endl;
                tasks_amount = tab[i] * j;
                processes_list = file.reading(file.name, tasks_amount);
                if (processes_list.empty()) {
                    return 0;
                }
                file.parallelTask(processes_list);
//                if( tab[i] * j  > 2)
                file.simulatedAnnealing(processes_list);
//                else cout << "heh\n";

                // TIME END
                auto end = Clock::now();
                auto duration = duration_cast<nanoseconds>(end - start);
                output << tasks_amount << ";" << duration.count() / 1000000000.0 << endl;
                start = Clock::now();
            }
        }
    }
    output.close();
    return 0;

}