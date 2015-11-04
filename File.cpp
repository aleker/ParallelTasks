#include "File.h"

bool File::reading() {
    fstream file;
    file.open( "Files/test1.txt" );
    if( !file.good() )
        return false;
    while ( !file.eof() ) {
        int flag = 0;
        string row;
        getline( file, row);
        if (row.substr(0,11)=="; MaxJobs: ") {
            helper=row.substr(11,10);
            maxJobs = stoi(helper);
            maxRecords = maxJobs;
            cout << "maxJobs and maxRecords = " << maxJobs << endl;
        }
        else if (row.substr(0,12)=="; MaxProcs: ") {
            helper=row.substr(12,10);
            maxProcs = stoi(helper);
            maxNodes = maxProcs;
            cout << "maxProcs and maxNodes = " << maxProcs << endl;
        }
        else if (row.substr(0,1) != ";"){
            for(char c : row){
                if(isdigit(c) && flag < 6){
                    flag++;
                    switch(flag){
                        case 1:
                            cout << setw(10) << "id : " << c << " | " ;
                            break;
                        case 2:
                            cout << setw(10) << "standby time : " << c << " | ";
                            break;
                        case 4:
                            cout << setw(10) << "duration : " << c << " | ";
                            break;
                        case 5 :
                            cout << setw(10) << "procs no. : " << c << " ";
                    }

                }

            }
            cout << endl;
        }
    }

}
