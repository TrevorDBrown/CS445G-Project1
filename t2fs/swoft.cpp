/*
 CS 445(G) - Dr. Qi Li
 Project 1 - t2fs (Travis and Trevor's File System)
 Simulated File System
 Trevor D. Brown and Travis Anderson
 
 swoft.cpp - System Wide Open File Table (Implementation)
 */

#include "swoft.hpp"        // System Wide Open File Table header file

// swoft constructor
swoft::swoft(){
    // Nothing to populate
}

/*
    getSize()
    returns the size of the SWOFT (using the file_names vector)
 */
long swoft::getSize(){
    return file_names.size();
}

/*
    getFileName(int index)
    returns a file name, based on a given vector index.
 */
string swoft::getFileName(int index){
    return file_names[index];
}

/*
    isFileOpen(string file_name)
    returns a boolean representing the existence of the specified file in the SWOFT
 */
bool swoft::isFileOpen(string file_name){
    if (file_names.size() > 0){
        for (int i = 0; i < file_names.size(); i++){
            if (file_names[i] == file_name){
                return true;
            }
        }
    }
    
    return false;
}

// Note: you may want to make a lock for this, as pthreads may interfere with modifications to the table.

/*
    addEntry(string file_name, fcb file_fcb)
    adds a new entry to the SWOFT.
*/
void swoft::addEntry(string file_name, fcb file_fcb){
    file_names.push_back(file_name);
    file_control_blocks.push_back(file_fcb);
}

/*
    getEntryIndex(string file_name)
    returns the vector index of a specified file
 */
int swoft::getEntryIndex(string file_name){
    // set the vector index to -1.
    int swoft_entry_index = -1;
    
    // If the file names vector is larger than 0, search it for the specified file.
    if (file_names.size() > 0){
        for (int i = 0; i < file_names.size(); i++){
            if (file_name == file_names[i]){
                // if the file is found, store its vector index.
                swoft_entry_index = i;
            }
        }
    }
    
    return swoft_entry_index;   // return the vector index.
}

/*
    removeEntry(string file_name)
    remove a file from the SWOFT, given the file is now closed
 */
void swoft::removeEntry(string file_name){
    // If the file names table is larger than 0
    if (file_names.size() > 0){
        // get the handle of the file from the SWOFT's vector index.
        int swoft_index = getEntryIndex(file_name);
        
        // Erase the entries from the vectors
        file_names.erase(file_names.begin() + swoft_index);
        file_control_blocks.erase(file_control_blocks.begin() + swoft_index);
    }
    else{
        printf("Error: file not found in SWOFT.");
    }
}

/*
    printTableContents()
    prints the contents of the SWOFT.
 */
void swoft::printTableContents(){
    printf("\nSystem Wide Open File Table\n");
    printf("File Name \t|\t FCB Starting Block\n");
    for (int i = 0; i < file_names.size(); i++){
        printf("%s \t\t|\t %i\n", file_names[i].c_str(), file_control_blocks[i].getFirstBlock());
    }
}
