/*
 CS 445(G) - Dr. Qi Li
 Project 1 - t2fs (Travis and Trevor's File System)
 Simulated File System
 Trevor D. Brown and Travis Anderson
 
 swoft.hpp - System Wide Open File Table (Header)
 */

#include <stdio.h>              // Standard I/O library
#include <stdlib.h>             // Standard C library
#include <unistd.h>             // Standard symbolic constants and types
#include <string>               // String library
#include <vector>               // Vector library

#include "fcb.hpp"              // File Control Block class

#ifndef __SWOFT_H_INCLUDED__
#define __SWOFT_H_INCLUDED__

using namespace std;            // All implicit references to functions made in this class are for std.

// Begin class defintion
class swoft {
    // Private class variables
    private:
        vector<string> file_names;          // vector of file names
        vector<fcb> file_control_blocks;    // vector of file control blocks.
    
    // Public class methods (explanation in swoft.cpp)
    public:
        swoft();
        long getSize();
        string getFileName(int index);
        bool isFileOpen(string file_name);
        void addEntry(string file_name, fcb file_fcb);
        int getEntryIndex(string file_name);
        void removeEntry(string file_name);
        void printTableContents();
};

#endif


