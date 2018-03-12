/*
 CS 445(G) - Dr. Qi Li
 Project 1 - t2fs (Travis and Trevor's File System)
 Simulated File System
 Trevor D. Brown and Travis Anderson
 
 ppoft.hpp - Per-process Open File Table (Header)
 */

#include <stdio.h>              // Standard I/O library
#include <stdlib.h>             // Standard C library
#include <unistd.h>             // Standard symbolic constants and types
#include <string>               // String library
#include <vector>               // Vector library
#include <pthread.h>            // Pthread library

#ifndef __PPOFT_H_INCLUDED__
#define __PPOFT_H_INCLUDED__

using namespace std;            // All implicit references to functions made in this class are for std.

// Begin class defintion
class ppoft {
    // Private class variables
    private:
        pthread_t tid;                  // pthread id
        vector<string> file_names;      // vector of file names
        vector<int> handles;            // vector of file handles (indices of files in SWOFT)
    
    // Public class methods (explanations in ppoft.cpp)
    public:
        ppoft(pthread_t tid);
        pthread_t getTid();
        string getFileName(int index);
        long getSize();
        int getHandle(int index);
        void updateHandle(int index, int handle);
        void addEntry(string file_name, int handle);
        void removeEntry(string file_name);
        void printTableContents();
};

#endif

