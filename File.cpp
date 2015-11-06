#include "File.h"


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
        cout << "File not good enough, my soldier!" << endl;
        exit;
    }
    while ( !file.eof() && tasks_amount != 0) {
        int flag = 0;
        string row;
        getline( file, row);
        if (row.substr(0,11)=="; MaxJobs: ") {
            helper=row.substr(11,10);
            maxJobs = stoi(helper);
            maxRecords = maxJobs;
            cout << "maxJobs and maxRecords = " << maxJobs << endl;
            if (tasks_amount == -1 || tasks_amount > maxJobs)
                tasks_amount = maxJobs;
        }
        else if (row.substr(0,12)=="; MaxProcs: ") {
            helper=row.substr(12,10);
            maxProcs = stoi(helper);
            maxNodes = maxProcs;
            cout << "maxProcs and maxNodes = " << maxProcs << endl << endl;
        }
        else if (row.substr(0,1) != ";"){
            tasks_amount --;
            Process process;
            const char * tab = row.c_str();
            for(int i=0; i <= row.length(); i++){
                if(isdigit(tab[i]) && flag<=6){
                    flag++;
                    string number;
                    do{
                        number+=tab[i];
                        i++;
                    }while(tab[i]!=' ');

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

                    }
                    if(flag == -1)
                        break;
                }
            }
            if (process.id >0 && process.r_j >= 0 &&  process.p_j > 0 && process.size_j > 0 ) {
                //process.f_t = process.r_j + process.p_j;
                processes_list.push_back(process);
            }
        }
    }
    sort(processes_list.begin(), processes_list.end(), myCmp);
    return processes_list;
}

void File::parallelTask(vector<Process> processes_list) {
    unsigned int clock_tick = 0;
    int free_proc = maxProcs;
    Process task;
    vector<Process> active_tasks;
    int i = 0;
    int proc_num = i;
    bool flag;

    while ( !processes_list.empty()) {
        i = 0;
        flag = true;       // to add more then one task in one clock_tick
        //delete task;
        task.p_j = 0;
        while ( !active_tasks.empty() && active_tasks.front().f_t <= clock_tick){
            free_proc += active_tasks.front().size_j;
            // dodawanie do pliku gdy wychodzi
            active_tasks.erase(active_tasks.begin());
        }
        while (free_proc > 0 && flag) {
            flag = false;
            while (( i < processes_list.size() ) && processes_list[i].r_j <= clock_tick ){
                if ((task.p_j == 0 || processes_list[i].size_j > task.size_j) && processes_list[i].size_j <= free_proc) {
                    task = processes_list[i];
                    proc_num = i;
                    flag = true;
                }
                i++;
            }
            if (task.p_j != 0) {
                task.f_t = clock_tick + task.p_j;
                active_tasks.push_back(task);
                // dodawanie do pliku  gdy wchodzi
                task.display();
                cout << "Clock " << clock_tick << endl;
                sort(active_tasks.begin(), active_tasks.end(), myCmp2);

                processes_list.erase(processes_list.begin()+proc_num);
                free_proc -= task.size_j;
                // delete task
                i = 0;
                task.p_j = 0;
            }
            //cout << "Wychodzisz? Moje życie to żart" << endl;
        }
    clock_tick ++;
    }

}