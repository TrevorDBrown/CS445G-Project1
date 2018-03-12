/*
 CS 445(G) - Dr. Qi Li
 Project 1 - t2fs (Travis and Trevor's File System)
 Simulated File System
 Trevor D. Brown and Travis Anderson
 
 fcb.cpp - File Control Block (Implementation)
 */

#include "fcb.hpp"      // File Control Block header file.

// fcb constructor (default, blank)
fcb::fcb(){
    file_size = -1;
    first_data_block = -1;
    file_content = "";
}

// fcb constructor
fcb::fcb(int size, string content, int first_block){
    file_size = size;
    file_content = content;
    first_data_block = first_block;
};

/*
    getFileContent()
    returns the content of a file.
 */
string fcb::getFileContent(){
    return file_content;
}

/*
    getFileSize()
    returns the size of a file.
 */
int fcb::getFileSize(){
    return file_size;
};

/*
    getFirstBlock()
    returns the first data block of a file.
 */
int fcb::getFirstBlock(){
    return first_data_block;
};

/*
    updateFirstBlock(int new_start_block)
    updates the first data block value of file.
 */
void fcb::updateFirstBlock(int new_start_block){
    first_data_block = new_start_block;
}

/*
    updateFileSize(int new_file_size)
    updates the file size of a file.
 */
void fcb::updateFileSize(int new_file_size){
    file_size = new_file_size;
}

/*
    updateFileContent(string new_file_content)
    updates the content of a file.
 */
void fcb::updateFileContent(string new_file_content){
    file_content = new_file_content;
}

/*
    printsFCBValues()
    prints out the file control block information of a file.
 */
void fcb::printFCBValues(){
    printf("FCB Values:\n");
    printf("First Data Block | File Size (Blocks)\n");
    printf("%i | %i\n", first_data_block, file_size);
}
