#ifndef PARALLELTASKS_STRUCTURE_H
#define PARALLELTASKS_STRUCTURE_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

class Process {
public:
    int id;     // id procesu
    int r_j;    // moment gotowosci przybycia, przybycia
    int p_j;    // czas trwania
    int size_j; // liczba procesorów
    int f_t;    // finish time
    vector<int> procs_numbers;

    Process() { };              //empty constructor
    Process(int id, int r, int p, int size) : id(id), r_j(r), p_j(p), size_j(size) { }
    ~Process() { }

    void display();

};


#endif //PARALLELTASKS_STRUCTURE_H
