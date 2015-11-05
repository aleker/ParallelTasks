#include "File.h"


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
            cout << "maxProcs and maxNodes = " << maxProcs << endl;
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
            cout << endl;
            if (process.id >0 && process.r_j >= 0 &&  process.p_j > 0 && process.size_j > 0 ) {
                processes_list.push_back(process);
            }
        }
    }
    return processes_list;
}
