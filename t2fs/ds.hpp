/*
 CS 445(G) - Dr. Qi Li
 Project 1 - t2fs (Travis and Trevor's File System)
 Simulated File System
 Trevor D. Brown and Travis Anderson
 
 ds.hpp - Directory Structure (Partition, Header)
 */

#include <stdio.h>              // Standard I/O library
#include <stdlib.h>             // Standard C library
#include <unistd.h>             // Standard symbolic constants and types
#include <string>               // String library
#include <vector>               // Vector library

#include "fcb.hpp"              // File Control Block class

using namespace std;            // All implicit references to functions made in this class are for std.

// Begin class definition
class ds {
    // Private class variables
    private:
        vector<string> file_names;          // vector of files names
        vector<fcb> file_control_blocks;    // vector of file control blocks
        // Please note: the indices of these vectors join their properties
    
    // Public class methods (explanations found in ds.cpp)
    public:
        ds();
        string getFileName(int starting_block);
        int getFileSizeByVectorIndex(int index);
        int getFileSizeByStartingBlock(int starting_block);
    
        void newFile(string file_name, fcb new_fcb);
        int doesFileExist(string file_name);
    
        void removeFile(int vector_index);
    
        void replaceFCB(string file_name, fcb file_control_block);
        void replaceFCB(int vector_index, fcb file_control_block);
    
        void updateFCBFirstBlock(int vector_index, int start_block);
        void updateFCBFileSize(int vector_index, int new_file_size);
        void updateFCBFileContent(int vector_index, string file_content);
    
        vector<fcb> getFileControlBlocks();
        fcb getFileControlBlockWithVectorIndex(int vector_index);
        fcb getFileControlBlockWithFileName(string file_name);
        fcb getFileControlBlockWithStartBlock(int starting_block);
        int getFileControlBlockVectorIndexWithStartBlock(int starting_block);
        int getFileControlBlockVectorIndexWithFileName(string file_name);
    
        string getBlockOwner(int block_number);
    
        string getFileContent(string file_name);
        void listAllFiles(int block_size);
    
        void printFileInfo(string file_name);
};


