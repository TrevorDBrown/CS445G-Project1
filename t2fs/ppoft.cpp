/*
 CS 445(G) - Dr. Qi Li
 Project 1 - t2fs (Travis and Trevor's File System)
 Simulated File System
 Trevor D. Brown and Travis Anderson
 
 ppoft.cpp - Per-process Open File Table (Implementation)
 */

#include "ppoft.hpp"    // Per-Process Open File Table header file

// ppoft constructor
ppoft::ppoft(pthread_t current_tid){
    tid = current_tid;
    printf("PPOFT created for tid: %i\n", tid);
}

/*
    getTid()
    returns the pthread id of a particular PPOFT
 */
pthread_t ppoft::getTid(){
    return tid;
}

/*
    getFileName(int index)
    returns the file name of a specific file at a specified vector index.
 */
string ppoft::getFileName(int index){
    return file_names[index];
}

/*
    getSize()
    returns the size of the file names vector (which, in turn, is the length of the PPOFT)
 */
long ppoft::getSize(){
    return file_names.size();
}

/*
    getHandle(int index)
    returns the handle of a file, specified in the PPOFT, by vector index.
 */
int ppoft::getHandle(int index){
    return handles[index];
}

/*
    updateHandle(int index, int handle)
    updates a file's handle, in the PPOFT, in case the SWOFT has changed.
 */
void ppoft::updateHandle(int index, int handle){
    handles[index] = handle;
}

// Note: you may want to make a lock for this, as pthreads may interfere with modifications to the table.
// THIS IS PER-PROCESS!! (PTHREAD)

/*
    addEntry(string file_name, int handle)
    adds an open file entry to a process/pthread's PPOFT
 */
void ppoft::addEntry(string file_name, int handle){
    file_names.push_back(file_name);
    handles.push_back(handle);
}

/*
    removeEntry(string file_name)
    removes a file from the process/pthread's PPOFT (assumed file is closed)
 */
void ppoft::removeEntry(string file_name){
    // Initialize the table index to -1
    int table_index = -1;
    
    // Parse through the file names vector
    for (int i = 0; i < file_names.size(); i++){
        if (file_names[i] == file_name){
            // If the file name is found in the vector, remove it from the vector
            table_index = i;
            file_names.erase(file_names.begin() + i);
        }
    }
    
    // If the vector index is not -1, remove the entry from the handles vector as well, using the same index.
    if (table_index != -1){
        // Remove from Handles vector
        handles.erase(handles.begin() + table_index);
    }
    else{
        // Otherwise, report an error.
        printf("\nError: file not found in PPOFT.\n");
    }
    
}

/*
    printTableContents()
    prints to the console the content of a calling process/pthread's PPOFT
 */
void ppoft::printTableContents(){
    printf("\nProcess Number %i Open File Table\n", tid);
    printf("File Name \t|\t Handle\n");
    for (int i = 0; i < file_names.size(); i++){
        printf("%s \t\t|\t %i\n", file_names[i].c_str(), handles[i]);
    }
}
