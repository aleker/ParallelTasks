#ifndef PARALLELTASKS_STRUCTURE_H
#define PARALLELTASKS_STRUCTURE_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>

using namespace std;

class Process {
public:
    int id;     // id procesu
    int r_j;    // moment gotowosci przybycia, przybycia
    int p_j;    // czas trwania
    int size_j; // liczba procesorów

    Process() { cout << "Process created!" << endl; };              //empty constructor
    Process(int id, int r, int p, int size) : id(id), r_j(r), p_j(p), size_j(size) { cout << "Process created!" << endl; }

};


#endif //PARALLELTASKS_STRUCTURE_H
