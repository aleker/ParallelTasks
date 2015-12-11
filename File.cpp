#include <sstream>
#include "File.h"

// CONST VALUES
#define COEFFICIENT_R_J             2;
#define TEMPERATURE                 1000;
#define MIN_TEMPERATURE             50;
#define ALFA                        0.8;
#define MAX_COUNTER_BETTER_SOLUTION 20;
#define MAX_COUNTER_WORSE_SOLUTION  20;
#define MINUTES_AMOUNT              5;

vector<Process> alternative_solution;

bool myCmp(const Process& a, const Process& b)
{
    return a.r_j < b.r_j;  // smallest comes first
}

bool myCmp2(const Process& a, const Process& b)
{
    return a.f_t < b.f_t;  // smallest comes first
}

vector<Process>  File::reading(string name_of_file, int tasks_amount) {
    fstream file;
    vector<Process> processes_list;
    file.open( name_of_file );
    if( !file.good() ) {
        cout << "Input file is not good enough, my soldier!" << endl;
        return processes_list;
    }
    while ( !file.eof() and tasks_amount != 0) {
        int flag = 0;
        string row;
        getline( file, row);
        if (row.substr(0,1) == ";" and row.length() > 10) {
            const char* tab = row.c_str();
            for (int i = 0; i < row.length() - 9; i++) {
                if (row.substr(i, 8) == "MaxJobs:") {
                    string number;
                    for (int j = i + 9; j < row.length(); j++) {
                        if (isdigit(tab[j]))
                            number += tab[j];
                    }
                    maxJobs = stoi(number);
                    maxRecords = maxJobs;
                    cout << "maxJobs and maxRecords = " << maxJobs << endl;
                    if (tasks_amount == -1 or tasks_amount > maxJobs) {
                        tasks_amount = maxJobs;
                        cout << "Tasks_amount = maxJobs = " << tasks_amount << endl;
                    }
                    break;
                }
                else if (row.substr(i, 9) == "MaxProcs:") {
                    string number;
                    for (int j = i + 10; j < row.length(); j++) {
                        if (isdigit(tab[j]))
                            number += tab[j];
                    }
                    maxNodes =stoi(number);
                    maxProcs = maxNodes;
                    cout << "maxProcs and maxNodes = " << maxProcs << endl << endl;
                    break;
                }
            }
        }
        else if (row.substr(0,1) != ";"){
            Process process;
            const char * tab = row.c_str();
            for(int i=0; i <= row.length(); i++){
                if((tab[i] == '-' or isdigit(tab[i])) and flag<=6){
                    flag++;
                    string number;
                    do{
                        number+=tab[i];
                        i++;
                    } while(isdigit(tab[i]));

                    switch(flag){
                        case 1:
                            process.id = stoi(number);
                            //cout << setw(10) << "id : " << process.id << " | " ;
                            break;
                        case 2:
                            process.r_j = stoi(number);
                            //cout << setw(10) << "standby time : " << process.r_j << " | ";
                            break;
                        case 4:
                            process.p_j = stoi(number);
                            //cout << setw(10) << "duration : " << process.p_j << " | ";
                            break;
                        case 5 :
                            process.size_j = stoi(number);
                            //cout << setw(10) << "procs no. : " << process.size_j << " ";
                        case 6:
                            flag=-1;
                            break;
                        default:
                            break;
                    }
                    if(flag == -1)
                        break;
                }
            }
            if (process.id >0 and process.r_j >= 0 and  process.p_j > 0 and process.size_j > 0 ) {
                processes_list.push_back(process);
                tasks_amount --;
            }
        }
    }
    sort(processes_list.begin(), processes_list.end(), myCmp);
    return processes_list;
}

void File::parallelTask(vector<Process> processes_list) {
//    while (!alternative_solution.empty()) {
//        delete alternative_solution.front();
//    }
    alternative_solution.clear();
    //cout << "In parallelTask\n" << "processes_list.size = " << processes_list.size() << endl;
    unsigned int clock_tick = 0;
    int free_proc = maxProcs;
    Process task;
    vector<Process> active_tasks;
    bool *available_procs = new bool[maxProcs];
    int i = 0;
    int proc_num = i;
    bool flag;
    while ( !processes_list.empty()) {
        i = 0;
        flag = true;       // to add more than one task in one clock_tick
        //delete task;
        task.p_j = 0;

        // FREEING THE PROCESSORS WHEN TASK'S FINISHED
        while ( !active_tasks.empty() and active_tasks.front().f_t <= clock_tick){
            free_proc += active_tasks.front().size_j;

            // cleaning the bool array of procs numbers
            while(!active_tasks.front().procs_numbers.empty()) {
                available_procs[active_tasks.front().procs_numbers.front()] = false;
                active_tasks.front().procs_numbers.erase(active_tasks.front().procs_numbers.begin());
            }
            active_tasks.erase(active_tasks.begin());
        }

        while (free_proc > 0 and flag) {
            flag = false;

            // CHOOSING THE BEST TASK TO ALLOCATE
            while (( i < processes_list.size() ) and processes_list[i].r_j <= clock_tick ){
                if ((task.p_j == 0 or processes_list[i].size_j > task.size_j) and processes_list[i].size_j <= free_proc) {
                    task = processes_list[i];
                    proc_num = i;
                    flag = true;
                }
                i++;
            }

            // ALLOCATING THE TASK WHEN WE'VE GOT A CHOSEN ONE
            if (task.p_j != 0) {
                task.f_t = clock_tick + task.p_j;
                // assigning processors numbers to a current task
                int procs_needed = task.size_j;
                for ( int j = 0; j < maxProcs ; j++){
                    if(procs_needed != 0 and available_procs[j]==0) {
                        available_procs[j] = 1;   //changing the status to "taken"
                        procs_needed--;
                        task.procs_numbers.push_back(j);
                    }
                }
                active_tasks.push_back(task);
                alternative_solution.push_back(task);
                sort(active_tasks.begin(), active_tasks.end(), myCmp2);
                processes_list.erase(processes_list.begin()+proc_num);

                free_proc -= task.size_j;
                i = 0;
                task.p_j = 0;
            }
        }
        if (!active_tasks.empty()) {
            if (active_tasks.front().f_t <= processes_list.front().r_j and clock_tick != active_tasks.front().f_t) {
                clock_tick = (unsigned int)active_tasks.front().f_t;
            }
            else {
                vector<Process>::iterator pointer;
                pointer = processes_list.begin();
                if (pointer->size_j <= free_proc) {
                    clock_tick = (unsigned int) pointer->r_j;
                }
                else {
                    do {
                        pointer++;
                        if (pointer->size_j <= free_proc) {
                            clock_tick = (unsigned int) pointer->r_j;
                            break;
                        }
                    } while (pointer->r_j < active_tasks.front().f_t and pointer != processes_list.end());
                }
                if (pointer->r_j >= active_tasks.front().f_t or pointer == processes_list.end()) {
                    clock_tick =(unsigned int) active_tasks.front().f_t;
                }
            }
        }
        else if (!processes_list.empty()) {
            clock_tick = (unsigned int)processes_list.front().r_j;
        }
    }
}

vector<Process> File::findAlternativeSolution(vector<Process> processes_list) throw(string) {
    string exception = "The alternative_solution is empty!\n";
    if (!processes_list.empty()) {
        // drawing task numbers
        unsigned int task_number1;
        unsigned int task_number2;
        for (unsigned int i = 0; i < 10/*(unsigned int) processes_list.size() / 50*/; i++) {
            do {
                task_number1 =
                        rand() % (((unsigned int) processes_list.size() - (unsigned int) processes_list.size() / 10) + 1) + 0;
                task_number2 = rand() % ((task_number1 + (unsigned int) processes_list.size() / 10 - task_number1) + 1) +
                               task_number1;
            } while ((processes_list[task_number1].size_j < processes_list[task_number2].size_j) and
                    (processes_list[task_number1].r_j > (processes_list[task_number2].f_t - processes_list[task_number2].p_j)));
            processes_list[task_number1].r_j = processes_list[task_number2].r_j + COEFFICIENT_R_J;
            sort(processes_list.begin(), processes_list.end(), myCmp);
        }
        this->parallelTask(alternative_solution);
    }
    else throw exception;
    return processes_list;
}

double probability(int actual_end_time, int actual_temperature) {
    double parameter = -((alternative_solution.back().f_t - actual_end_time) / actual_temperature);
    return exp(parameter);
}

float temperature_reducing(int actual_temperature) {
    float alfa = ALFA;
    return alfa * actual_temperature;
}

void File::simulatedAnnealing(vector<Process> processes_list) {
    clock_t start2 = clock();
    this->parallelTask(processes_list);
    this->saveToFile(alternative_solution, "PRL");
    vector<Process> actual_solution = alternative_solution;
    vector<Process> old_good_solution = actual_solution;
    int temperature = TEMPERATURE;
    int min_temperature = MIN_TEMPERATURE;
    unsigned int counter_worse_solution = 0;
    unsigned int counter_better_solution = 0;
    unsigned int max_counter_better_solution = MAX_COUNTER_BETTER_SOLUTION;
    unsigned int max_counter_worse_solution = MAX_COUNTER_WORSE_SOLUTION;
    int minutes_amount = MINUTES_AMOUNT;
    int i = 0;
    while (temperature > min_temperature) {
        cout << temperature << endl;
        if ((clock() - start2) / CLOCKS_PER_SEC > minutes_amount * 60) {
            cout << "Time is over\n";
            this->saveToFile(actual_solution,"SA");
            return;
        }
        if (counter_worse_solution >= max_counter_worse_solution) {
            cout << "Counter_worse_solution is max\n";
            this->saveToFile(old_good_solution,"SA");
            return;
        }
        // DELETING CONTENT OF TASKS_ORDER VECTOR
//        while (!alternative_solution.empty()) {
//            delete alternative_solution[0];
//        }
        // FIND ALTERNATIVE SOLUTION
        alternative_solution = this->findAlternativeSolution(actual_solution);
        //this->saveToFile(alternative_solution, "ALTER");
        if (alternative_solution.back().f_t < actual_solution.back().f_t) {
//            while (!actual_solution.empty()) {
//                delete actual_solution[0];
//            }
            cout << "rewrite\n";
            actual_solution.clear();
            old_good_solution.clear();
            actual_solution = alternative_solution;
            old_good_solution = alternative_solution;
            counter_better_solution++;
            counter_worse_solution = 0;
            if (counter_better_solution == max_counter_better_solution) {
                temperature = (int)temperature_reducing(temperature);
            }
        }
        else if ((rand() % 100 + 0) < (probability(actual_solution.back().f_t, temperature))*100) {
//            while (!actual_solution.empty()) {
//                delete actual_solution[0];
//            }
            actual_solution.clear();
            actual_solution = alternative_solution;
            counter_worse_solution++;
            counter_better_solution = 0;
            temperature = (int)temperature_reducing(temperature);
        }
    }
    cout << "Actual temperature is lower than boundary " << temperature << endl;
    this->saveToFile(old_good_solution,"SA");
}

void File::saveToFile(vector<Process> processes_vector, string type) {
    stringstream output_name;
    output_name << type << "OUT." << this->name;
    ofstream output;
    output.open(output_name.str().c_str());
    if( !output.good() ) {
        cout << "Output file is not good enough, my soldier!" << endl;
        return;
    }
    for (auto task: processes_vector) {
        output << task.id << " " << task.f_t - task.p_j
        << " " << task.f_t << " ";
        for(int j : task.procs_numbers)
            output << j << " ";
        output << endl;
    }

    cout << "Output file saved to " << output_name.str() << endl;
    output.close();
}


