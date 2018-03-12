/*
 CS 445(G) - Dr. Qi Li
 Project 1 - t2fs (Travis and Trevor's File System)
 Simulated File System
 Trevor D. Brown and Travis Anderson
 
 ds.hpp - Directory Structure (Partition, Implementation)
 */

#include "ds.hpp"   // Directory Structure header file

// Directory Structure constructor
ds::ds(){
    // Does nothing
}

/*
    getFileName(int starting_block)
    returns the file name of the file, based on the specified first data block.
 */
string ds::getFileName(int starting_block){
    // Traverse the file control blocks vector.
    for (int i = 0; i < file_control_blocks.size(); i++){
        if (file_control_blocks[i].getFirstBlock() == starting_block){
            // If a first data block exists equal to the specified starting block,
            // return the file name at the same vector index.
            return file_names[i];
        }
    }
    
    // Otherwise, return a blank string.
    return "";
}

/*
    getFileSizeByVectorIndex(int index)
    return the size of a file, based on the file specified via its vector index in ds.
 */
int ds::getFileSizeByVectorIndex(int index){
    // If the FCB is larger than 0, return the file size of the file at the specified vector index.
    if ((file_control_blocks.size() > 0)){
        return file_control_blocks[index].getFileSize();
    }
    else{
        // Otherwise, return 0.
        return 0;
    }
}

/*
    getFileSizeByStartingBlock(int starting_block)
    returns the size of a file, based on the first data block index specified.
 */
int ds::getFileSizeByStartingBlock(int starting_block){
    // Traverse the file control blocks vector
    for (int i = 0; i < file_control_blocks.size(); i++){
        // If a file control block is found that has the starting block
        if (file_control_blocks[i].getFirstBlock() == starting_block){
            // Return the file size of the specified file.
            return file_control_blocks[i].getFileSize();
        }
    }
    // Otherwise, return -1.
    return -1;
}

/*
    newFile(string file_name, fcb new_fcb)
    Add the name of the file and the file's file control block to their respective vectors.
 */
void ds::newFile(string file_name, fcb new_fcb){
    file_names.push_back(file_name);
    file_control_blocks.push_back(new_fcb);
}

/*
    removeFile(int vector_index)
    removes the file's name and file control block from their respective vectors.
 */
void ds::removeFile(int vector_index){
    file_names.erase(file_names.begin() + vector_index);
    file_control_blocks.erase(file_control_blocks.begin() + vector_index);
}

/*
    getFileControlBlocks()
    returns all of the file control blocks.
 */
vector<fcb> ds::getFileControlBlocks(){
    return file_control_blocks;
}

/*
    getFileControlBlockWithVectorIndex(int vector_index)
    returns the file control block at the specified vector index.
 */
fcb ds::getFileControlBlockWithVectorIndex(int vector_index){
    return file_control_blocks[vector_index];
}

/*
    getFileControlBlockWithFileName(string file_name)
    returns the file control block with the specified file name.
 */
fcb ds::getFileControlBlockWithFileName(string file_name){
    // set the vector index to -1.
    int fcb_index = -1;
    
    // Traverse the file names vector
    for (int i = 0; i < file_names.size(); i++){
        // If the file name matches one in the vector,
        // store the index
        if (file_name == file_names[i]){
            fcb_index = i;
        }
    }
    
    // If the index is not -1, return the file control block found
    if (fcb_index != -1){
        return file_control_blocks[fcb_index];
    }
    else{
        // Otherwise, return an empty file control block.
        return fcb();
    }
    
}

/*
    getFileControlBlockWithStartBlock(int starting_block)
    Return the file control block, based on the specified starting block.
 */
fcb ds::getFileControlBlockWithStartBlock(int starting_block){
    // Traverse the file control blocks vector
    for (int i = 0; i < file_control_blocks.size(); i++){
        // If the file control block's first block id is the same as the starting block,
        // Return the file control block.
        if (file_control_blocks[i].getFirstBlock() == starting_block){
            return file_control_blocks[i];
        }
    }
    
    // Otherwise, return a blank file control block.
    return fcb();
}

/*
    getFileControlBlockVectorIndexWithStartBlock(int starting_block)
    return the vector index of an entry in the file control block, for use with the file names vector.
 */
int ds::getFileControlBlockVectorIndexWithStartBlock(int starting_block){
    // Traverse the file control blocks vecotor
    for (int i = 0; i < file_control_blocks.size(); i++){
        // If the file control block's first block matches the starting block
        if (file_control_blocks[i].getFirstBlock() == starting_block){
            // Return the index of the current vector entry
            return i;
        }
    }
    // Otherwise, return -1.
    return -1;
}

/*
    getFileControlBlockVectorIndexWithFileName(string file_name)
    Return the vector index of a specific file control block, based on the file name of a file.
 */
int ds::getFileControlBlockVectorIndexWithFileName(string file_name){
    for (int i = 0; i < file_names.size(); i++){
        if (file_names[i] == file_name){
            return i;
        }
    }
    
    return -1;
}

/*
    doesFileExist(string file_name)
    Return the vector indes of the file, if it exists. Otherwise, return -1.
 */
int ds::doesFileExist(string file_name){
    for (int i = 0; i < file_names.size(); i++){
        if (file_names[i] == file_name){
            return i;
        }
    }
    return -1;
}

/*
    replaceFCB(string file_name, fcb file_control_block)
    replaces the file control block of a file, specified with a file name, with an updated (or even new) file control block.
 */
void ds::replaceFCB(string file_name, fcb file_control_block){
    for (int i = 0; i < file_names.size(); i++){
        if (file_names[i] == file_name){
            file_control_blocks[i] = file_control_block;
        }
    }
}

/*
    replaceFCB(int vector index, fcb file_control_block)
    replaces the file control block of a file, specified with its vector index, with an updated (or even new) file control block.
 */
void ds::replaceFCB(int vector_index, fcb file_control_block){
    file_control_blocks[vector_index] = file_control_block;
}

/*
    updateFCBFirstBlock(int vector_index, int start_block)
    updates the file control block's starting block, specified by the file control block's vector index, with a new start block)
 */
void ds::updateFCBFirstBlock(int vector_index, int start_block){
    file_control_blocks[vector_index].updateFirstBlock(start_block);
}

/*
    updateFCBFileSize(int vector_index, int new_file_size)
    updates the file control block's file size, specified by the file control block's vector index, with a new file size.
 */
void ds::updateFCBFileSize(int vector_index, int new_file_size){
    file_control_blocks[vector_index].updateFileSize(new_file_size);
}

/*
    updateFCBFileContent(int vector_index, string file_content)
    updates the file control block's file content, specified by the file control block's vector index, with new content.
 */
void ds::updateFCBFileContent(int vector_index, string file_content){
    file_control_blocks[vector_index].updateFileContent(file_content);
}

/*
    getBlockOwner(int block_number)
    returns the file name of the file that occupies that block.
 */
string ds::getBlockOwner(int block_number){
    // traverse the file control blocks vector
    for (int i = 0; i < file_control_blocks.size(); i++){
        // if a file control block's first block is equal to the specified file control block number.
        if (file_control_blocks[i].getFirstBlock() == block_number){
            // Return the file name with that index in the file names vector.
            return file_names[i];
        }
        // if a file control block's block value is within the range of a file's block occupation:
        else if ((block_number > file_control_blocks[i].getFirstBlock()) && (block_number < file_control_blocks[i].getFirstBlock() + file_control_blocks[i].getFileSize())){
            // Return the file name with that index in the file names vector.
            return file_names[i];
        }
    }
    
    // Otherwise, return a blank string.
    return "";
}

/*
    getFileContent(string file_name)
    reutnrs the file content of a file, specified by the file's name.
 */
string ds::getFileContent(string file_name){
    // traverse the file names vector.
    for (int i = 0; i < file_names.size(); i++){
        // if a specified file name matches a file name in the file names vector
        if (file_names[i] == file_name){
            // Return the file content of the file.
            return file_control_blocks[i].getFileContent();
        }
    }
    // Otherwise, return a blank string.
    return "";
}

/*
    listAllFiles(int block_size)
    lists all of the files on disk. Additionally, the byte size is computed using the size of blocks.
 */
void ds::listAllFiles(int block_size){
    // Table header
    printf("\nFiles on disk:\n");
    printf("File Name\t|\tSize (bytes)\n");
    
    // Table data
    for (int i = 0; i < file_names.size(); i++){
        printf("%s\t\t|\t %i\n", file_names[i].c_str(), (file_control_blocks[i].getFileSize() * block_size));
        //printFileInfo(file_names[i]);
    }
    
    printf("\n");
}

/*
    printFileInfo(string file_name)
    Prints out basic file information from the file control block, based on the file name.
 */
void ds::printFileInfo(string file_name){
    int vector_index = getFileControlBlockVectorIndexWithFileName(file_name);
    printf("%s file information:\n", file_name.c_str());
    file_control_blocks[vector_index].printFCBValues();
}
