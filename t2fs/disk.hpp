/*
 CS 445(G) - Dr. Qi Li
 Project 1 - t2fs (Travis and Trevor's File System)
 Simulated File System
 Trevor D. Brown and Travis Anderson
 
 disk.hpp - the disk (Header)
 */
#include <stdio.h>              // Standard I/O library
#include <stdlib.h>             // Standard C library
#include <unistd.h>             // Standard symbolic constants and types
#include <pthread.h>            // Pthreads library
#include <string>               // String library

#include "swoft.hpp"            // System Wide Open File Table class
#include "ppoft.hpp"            // Per-Process Open File Table class
#include "vcb.hpp"              // Volume Control Block class
#include "ds.hpp"               // Directory Structure class
#include "fcb.hpp"              // File Control Block class.

using namespace std;            // All implicit references to functions made in this class are for std.

// Begin class definition
class disk{
    // Private class variables
    private:
        // Disk ID (int)
        int disk_id;
        // Disk Label (string)
        string disk_label;
        // Directory Structure (ds, ADT)
        ds directory_structure;
        // Volume Control Block (vcb, ADT)
        vcb volume_control_block;
        // System Wide Open File Table (swoft, ADT)
        swoft system_wide_open_file_table;
        // vector of Per-Process Open File Tables (vector<ppoft>, ADT)
        vector<ppoft> per_process_open_file_tables;
    
    // Public class methods (explanations found in disk.cpp)
    public:
        disk(int id, string label);
        string getLabel();
        int getTotalBlocks();
        int getTotalFreeBlocks();
    
        void createPPOFT(pthread_t tid);
        void refactorPPOFT();
    
        int findStartingBlock(int file_size);
    
        void printFreeBlockBitmap();
        void printSWOFT();
        void printPPOFTs();
    
        void create(string file_name, string file_content);
        void open(pthread_t tid, string file_name);
        void close(pthread_t tid, string file_name);
        void write(pthread_t tid, string file_name, string file_content);
        string read(string file_name);
        void dir();
        void del(string file_name);
    
        void prepareShift();
        int shiftAllocatedBlocksToFront(int start_block);
};


