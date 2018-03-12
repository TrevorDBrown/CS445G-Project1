/*
 CS 445(G) - Dr. Qi Li
 Project 1 - t2fs (Travis and Trevor's File System)
 Simulated File System
 Trevor D. Brown and Travis Anderson
 
 vcb.cpp - Volume Control Block (Implementation)
 */

#include "vcb.hpp"      // Volume Control Block header file.

// vcb constructor
vcb::vcb(){
    // Set defaults
    number_of_blocks = 512;
    block_size = 2048;
    free_block_count = 512;
    
    // Push "zeros" into the free block bitmap.
    for (int i = 0; i < number_of_blocks; i++){
        free_block_bit_map.push_back(0);
    }
}

/*
    getNumberOfBlocks()
    return the total number of blocks available.
 */
int vcb::getNumberOfBlock(){
    return number_of_blocks;
};

/*
    getBlockSize()
    returns the size of each block.
 */
int vcb::getBlockSize(){
    return block_size;
};

/*
    getFreeBlockCount()
    gets the free block count for the disk.
 */
int vcb::getFreeBlockCount(){
    return free_block_count;
};

/*
    getFreeBlockBitMapValue(int index)
    returns a specified block's use state
 */
int vcb::getFreeBlockBitMapValue(int index){
    return free_block_bit_map[index];
}

/*
    getFirstFreeBlock()
    returns the index of the first freed block.
 */
int vcb::getFirstFreeBlock(){
    // set the index to -1.
    int first_free_block = -1;
    
    // parse the free block bitmap for the first 0 found.
    for (int i = 0; i < number_of_blocks; i++){
        if (free_block_bit_map[i] == 0){
            first_free_block = i;
            break;
        }
    }

    // return the first zero found in the bitmap.
    return first_free_block;
}

/*
    updateFreeBlockCount(int operation)
    either increments or decrements the free block count by 1.
    operation == 1 --> increment
    operation == -1 --> decrement
 */
void vcb::updateFreeBlockCount(int operation){
    if (operation == 1){
        free_block_count += 1;
    }
    else if (operation == -1){
        free_block_count -= 1;
    }
    
}

/*
    allocateBlocks(int starting_block, int blocks_allocated)
    allocates a set number of blocks, starting at the starting block, and ending at starting_block + blocks_allocated.
 */
void vcb::allocateBlocks(int starting_block, int blocks_allocated){
    for (int i = starting_block; i < (starting_block + blocks_allocated); i++){
        free_block_bit_map[i] = 1;
        updateFreeBlockCount(-1);
    }
}

/*
     freeBlocks(int starting_block, int blocks_allocated)
     frees a set number of blocks, starting at the starting block, and ending at starting_block + blocks_allocated.
*/
void vcb::freeBlocks(int starting_block, int blocks_allocated){
    for (int i = starting_block; i < (starting_block + blocks_allocated); i++){
        free_block_bit_map[i] = 0;
        updateFreeBlockCount(1);
    }
}
