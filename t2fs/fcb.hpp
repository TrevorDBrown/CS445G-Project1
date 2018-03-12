/*
 CS 445(G) - Dr. Qi Li
 Project 1 - t2fs (Travis and Trevor's File System)
 Simulated File System
 Trevor D. Brown and Travis Anderson
 
fcb.hpp - File Control Block (Header)
 */

#include <stdio.h>              // Standard I/O library
#include <stdlib.h>             // Standard C library
#include <unistd.h>             // Standard symbolic constants and types
#include <string>               // String library
#include <vector>               // Vector library

#include "vcb.hpp"              // Volume Control Block class

#ifndef __FCB_H_INCLUDED__
#define __FCB_H_INCLUDED__

using namespace std;            // All implicit references to functions made in this class are for std.

// Begin class defintion
class fcb {
    // Private class variables
    private:
        int file_size;              // file size
        int first_data_block;       // first data block of file
        string file_content;        // the file content
    
    // Public class methods (explanation in fcb.cpp)
    public:
        fcb();
        fcb(int size, string content, int first_block);
        string getFileContent();
        int getFileSize();
        int getFirstBlock();
    
        void updateFirstBlock(int new_start_block);
        void updateFileSize(int new_file_size);
        void updateFileContent(string new_file_content);
    
        void printFCBValues();
};

#endif
