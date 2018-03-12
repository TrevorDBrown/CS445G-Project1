/*
 CS 445(G) - Dr. Qi Li
 Project 1 - t2fs (Travis and Trevor's File System)
 Simulated File System
 Trevor D. Brown and Travis Anderson
 
 vcb.hpp - Volume Control Block (Header)
 */

#include <stdio.h>              // Standard I/O library
#include <stdlib.h>             // Standard C library
#include <unistd.h>             // Standard symbolic constants and types
#include <vector>               // Vector library

#ifndef __VCB_H_INCLUDED__
#define __VCB_H_INCLUDED__

using namespace std;            // All implicit references to functions made in this class are for std.

// Begin class defintion
class vcb {
    // Private class variables
    private:
        int number_of_blocks;               // number of blocks on disk
        int block_size;                     // size of each block
        int free_block_count;               // free block counter
        vector<int> free_block_bit_map;     // free block bitmap
    
    // Public class methods (explanation in vcb.cpp)
    public:
        vcb();
        int getNumberOfBlock();
        int getBlockSize();
        int getFreeBlockCount();
        int getFirstFreeBlock();
        vector<int> getFreeBlockBitMap();
        int getFreeBlockBitMapValue(int index);
        void updateFreeBlockCount(int operation);
        void allocateBlocks(int starting_block, int blocks_allocated);
        void freeBlocks(int first_block, int file_size);
};

#endif
