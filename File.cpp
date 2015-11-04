#include "File.h"

bool File::reading() {
    fstream file;
    file.open( "OK/test1.txt" );
    if( !file.good() )
        return false;
    while ( !file.eof() ) {
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
            //char* line = row.c_str();

        }
    }

}
