/*
 CS 445(G) - Dr. Qi Li
 Project 1 - t2fs (Travis and Trevor's File System)
 Simulated File System
 Trevor D. Brown and Travis Anderson
 
 disk.hpp - the disk (Implementation)
 */

#include "disk.hpp" // Disk header file.

using namespace std;    // All implicit references to functions made in this class are for std.

// Disk constructor
disk::disk(int id, string label){
    disk_id = id;
    disk_label = label;
    
    // Initialize the disk with an empty directory structure and volume control block.
    directory_structure = ds();
    volume_control_block = vcb();
};

/*
    create(string file_name, string file_content)
    Creates a new file in the directory structure.
 */
void disk::create(string file_name, string file_content){
    int file_size_bytes = file_content.length();    // Use the character length of the content string as the file size (in bytes)
    
    int file_block_size = (file_size_bytes / volume_control_block.getBlockSize()); // Convert the byte size into a block count.
    
    // Verify that an extra block is not required, depending if there is a remainder to the block computation.
    if ((file_size_bytes % volume_control_block.getBlockSize()) != 0){
        file_block_size++;
    }
    
    int file_size = file_block_size;    // For simplicity, aliased file_block_size as file_size
    
    // If the file size is less than or equal to the total number of free blocks on disk.
    if (file_size <= getTotalFreeBlocks()){
        // Enough free space available.
        int current_index_in_ds_fcb_vector = 0; // Set the File Control Block vector index to 0.
        int start_block = findStartingBlock(current_index_in_ds_fcb_vector);    // Find the first empty block available after all current files.
        
        int index = start_block;    // alias the start_block as index.
        // While the index is less than the start block location plus the file size
        // or while index greater than the total number of blocks.
        while ((index < (start_block + file_size)) || index > volume_control_block.getNumberOfBlock()){
            // Check the values at each block in the bitmap
            if (volume_control_block.getFreeBlockBitMapValue(index) == 1){
                // if the value at the block in the bitmap is used, research for the next starting block, and add its value to the current start_block.
                start_block += findStartingBlock(++current_index_in_ds_fcb_vector);
                index = start_block;
            }
            else{
                // otherwise, increment the index variable.
                index++;
            }
        }
        
        // if the index is less than or equal to the total number of blocks
        if (index <= volume_control_block.getNumberOfBlock()){
            // create a new File Control Block for the new file.
            fcb new_fcb = fcb(file_size, file_content, start_block);
            
            // Create the new file in the directory structure.
            directory_structure.newFile(file_name, new_fcb);
            
            // Update Volume Control Block with the new file information.
            volume_control_block.allocateBlocks(start_block, file_size);
            
            printf("File %s has been created successfully!\n", file_name.c_str());
        }
        else{
            printf("\nError: Not enough space contiguously for file.\n");
        }

    }
    else{
        printf("\nError: Not enough free space.\n");
    }
}

/*
    getLabel()
    returns the disk's label
 */
string disk::getLabel(){
    return disk_label;
};

/*
    getTotalBlocks()
    returns the total number of blocks on the disk.
 */
int disk::getTotalBlocks(){
    return volume_control_block.getNumberOfBlock();
}

/*
    getTotalFreeBlocks()
    returns the total number of free blocks on the disk.
 */
int disk::getTotalFreeBlocks(){
    return volume_control_block.getFreeBlockCount();
}

/*
    findStartingBlock(int index)
    find the starting block for the new file on the disk.
 */
int disk::findStartingBlock(int index){
    return directory_structure.getFileSizeByVectorIndex(index);
}

/*
    printFreeBlockBitmap()
    prints the free block bitmap information to the screen.
 */
void disk::printFreeBlockBitmap(){
    // Header of table.
    printf("\nFree Block Bitmap Values\n");
    
    // Data for table
    for (int i = 0; i < volume_control_block.getNumberOfBlock(); i++){
        // Bitmap index at i
        printf("Bitmap index %i: %i", i, volume_control_block.getFreeBlockBitMapValue(i));
        
        // Check if the value is full or empty
        if (volume_control_block.getFreeBlockBitMapValue(i) == 0){
            printf(". Empty block");    // If 0 --> empty
        }
        else if (volume_control_block.getFreeBlockBitMapValue(i) == 1){
            printf(". Used by: %s", directory_structure.getBlockOwner(i).c_str()); // If 1 --> full, list "owner"
        }
        printf("\n");
    }
}

/*
    printSWOFT()
    prints the current state of the System Wide Open File Table (SWOFT)
 */
void disk::printSWOFT(){
    system_wide_open_file_table.printTableContents();
}

/*
    printPPOFT()
    prints the current state of all Per-Process Open File Tables (PPOFT)
 */
void disk::printPPOFTs(){
    if (per_process_open_file_tables.size() > 0){
        for (int i = 0; i < per_process_open_file_tables.size(); i++){
            per_process_open_file_tables[i].printTableContents();
            printf("\n");
        }
    }
}

/*
    createPPOFT(pthread_t tid)
    creates a new Per-Process Open File Table (PPOFT) for the calling Pthread
 */
void disk::createPPOFT(pthread_t tid){
    ppoft new_ppoft = ppoft(tid);
    per_process_open_file_tables.push_back(new_ppoft);
}

/*
    open(pthread_t tid, string file_name)
    Opens the file by the listed file name to the calling pthread. Adds entries to the SWOFT and pthread's PPOFT tables.
 */
void disk::open(pthread_t tid, string file_name){
    // Check if the file is already open by another process/pthread.
    if (system_wide_open_file_table.isFileOpen(file_name) == false){
        // If not open, retrieve the file control block for the file.
        fcb file_fcb = directory_structure.getFileControlBlockWithFileName(file_name);
        
        // If the File Control Block exists
        if (file_fcb.getFileSize() != -1){
            // Add the file to the system wide open file table.
            system_wide_open_file_table.addEntry(file_name, file_fcb);
            
            // Retrieve the handle (aka SWOFT vector index) for the Pthread PPOFT.
            int handle = system_wide_open_file_table.getEntryIndex(file_name);
            
            // If the handle is larger than 0 (aka not -1)
            if (handle >= 0){
                // If the PPOFTs vector size is larger than 0...
                if (per_process_open_file_tables.size() > 0){
                    // Parse through the PPOFTs vector, to find the correct PPOFT for the pthread.
                    for (int i = 0; i < per_process_open_file_tables.size(); i++){
                        if (per_process_open_file_tables[i].getTid() == tid){
                            // Once found, append the file information to the PPOFT.
                            per_process_open_file_tables[i].addEntry(file_name, handle);
                            printf("\nFile %s has been opened!\n", file_name.c_str());
                        }
                    }
                }
                else{
                    printf("\nError: cannot find PPOFT with Pthread ID %i.\n", tid);
                }
            }
        }
        else{
            printf("\nError: file not found.\n");
        }
    }
    else{
        printf("\nError: file %s is already open!\n", file_name.c_str());
    }
}

/*
    close(pthread_t tid, string file_name)
    closes the open file, if the calling pthread opened the file.
 */
void disk::close(pthread_t tid, string file_name){
    // Check if the file is in the SWOFT.
     if (system_wide_open_file_table.isFileOpen(file_name) == true){
         // If the file is in the SWOFT, remove it from the table.
         system_wide_open_file_table.removeEntry(file_name);
         
         // Traverse the PPOFT vector for the pthread's PPOFT
         for (int i = 0; i < per_process_open_file_tables.size(); i++){
             // Once found, remove the file from the pthread's PPOFT.
             if (per_process_open_file_tables[i].getTid() == tid){
                 per_process_open_file_tables[i].removeEntry(file_name);
             }
         }
         
         // "Refactor" all PPOFTs, so their handles match the indexes of the SWOFT.
         refactorPPOFT();
         printf("\nFile %s has been closed successfully.\n", file_name.c_str());
     }
     else{
         printf("\nWarning: file not open.\n");
     }
    
}

/*
    refactorPPOFT()
    recomputes the handles of the active PPOFTs.
 */
void disk::refactorPPOFT(){
    for (int i = 0; i < system_wide_open_file_table.getSize(); i++){
        for (int j = 0; j < per_process_open_file_tables.size(); j++){
            for (int k = 0; k < per_process_open_file_tables[j].getSize(); k++){
                if (system_wide_open_file_table.getFileName(i) == per_process_open_file_tables[j].getFileName(k)){
                    if (i != per_process_open_file_tables[j].getHandle(k)){
                        per_process_open_file_tables[j].updateHandle(k, i);
                    }
                }
            }
        }
    }
}

/*
    read(string file_name)
    reads the specified file into a string variable.
 */
string disk::read(string file_name){
    int file_location = directory_structure.doesFileExist(file_name);
    if (file_location != -1){
        return directory_structure.getFileContent(file_name);
    }
    else{
        return "Error: file does not exist.";
    }
}

/*
    write(pthread_t tid, string file_name, string file_content)
    writes the content of a specified file to the existing file, using the calling pthread. File is automatically opened.
 */
void disk::write(pthread_t tid, string file_name, string file_content){
    // Open the specified file, to the specified pthread.
    open(tid, file_name);
    
    // Fine the vector index that is used in the directory structure vectors.
    int ds_vector_index = directory_structure.getFileControlBlockVectorIndexWithFileName(file_name);
    
    // If the vector_index is greater than 0 (aka not -1)
    if (ds_vector_index != -1){
        // Retrieve the file size (bytes) by counting the number of characters in the file content string.
        int file_size_bytes = file_content.length();
        
        // Convert the file sizes from bytes to block count.
        int file_block_size = (file_size_bytes / volume_control_block.getBlockSize());
        
        // Verify whether or not another block is needed for the overflow.
        if ((file_size_bytes % volume_control_block.getBlockSize()) != 0){
            file_block_size++;
        }
        
        // Alias the file block size variable as file size.
        int file_size = file_block_size;
        
        // If the file size is less than or equal to the free block count.
        if (file_size <= volume_control_block.getFreeBlockCount()){
            // If enough space exists
            // Delete the file, but close file first
            close(tid, file_name);
            del(file_name);
            // Shift all current files to the beginning of the disk.
            shiftAllocatedBlocksToFront(0);
            // Recreate the file, with the new content.
            create(file_name, file_content);
            open(tid, file_name);
            printf("File %s has been written successfully.\n", file_name.c_str());
        }
        else{
            printf("\nError: not enough free space.\n");
        }
    }
    else{
        // If the file does not exist on write, create a new file.
        printf("\nWarning: file %s does not exist. Creating.\n", file_name.c_str());
        create(file_name, file_content);
    }
    
}

/*
    dir()
    Lists all current files on disk.
 */
void disk::dir(){
    directory_structure.listAllFiles(volume_control_block.getBlockSize());
}

/*
    del(string file_name)
    deletes the specified file from the disk.
 */
void disk::del(string file_name){
    // Verify that the file is not being used by a process/pthread.
    if (system_wide_open_file_table.isFileOpen(file_name) == false){
        // Get the vector index for the vectors in directory structure.
        int ds_vector_index = directory_structure.getFileControlBlockVectorIndexWithFileName(file_name);
        
        // If the vector inde is greater than or equal to 0 (aka not -1)
        if (ds_vector_index != -1){
            // Free the blocks associated with the file.
            volume_control_block.freeBlocks(directory_structure.getFileControlBlockWithVectorIndex(ds_vector_index).getFirstBlock(), directory_structure.getFileControlBlockWithVectorIndex(ds_vector_index).getFileSize());
            // Remote the file from the directory structure.
            directory_structure.removeFile(ds_vector_index);
            // Shift all remaining files to the beginning of the disk.
            shiftAllocatedBlocksToFront(0);
            printf("\nFile %s has been deleted successfully.\n", file_name.c_str());
        }
        else{
            printf("\nError: file does not exist.\n");
        }
    
    }
    else{
        printf("\nError: file %s is open. Please close file before delete.\n", file_name.c_str());
    }
}

/*
    prepareShift()
    prepares the block shifting, by calling the function with parameter 0.
 */
void disk::prepareShift(){
    // "Shift" all free blocks to the back.
    shiftAllocatedBlocksToFront(0);
}

/*
    shiftAllocatedBlocksToFront(int start_block)
    Moves all file blocks on disk towards the front of the disk. This ensures that all empty blocks in between files are "shifted" to the end of the disk, for easier access.
 */
int disk::shiftAllocatedBlocksToFront(int start_block){
    // Set index_to_move to -1
    int index_to_move = -1;
    
    for (int i = start_block; i < volume_control_block.getNumberOfBlock(); i++){
        // checking for the smallest block index.
        if (volume_control_block.getFreeBlockBitMapValue(i) == 1){
            index_to_move = i;
            break;
        }
    }
    
    if (index_to_move != -1){
        // When the current block is the smallest block index
        // Determine the size of the selected file.
        int intermediate_size = directory_structure.getFileSizeByStartingBlock(index_to_move);
        int fcb_vector_index = directory_structure.getFileControlBlockVectorIndexWithStartBlock(index_to_move);
        // Free the blocks of the selected file
        volume_control_block.freeBlocks(index_to_move, intermediate_size);
        // Reallocate the blocks at the new location.
        volume_control_block.allocateBlocks(start_block, intermediate_size);
        // Update the file's File Control Block with the latest information.
        directory_structure.updateFCBFirstBlock(fcb_vector_index, start_block);
        directory_structure.updateFCBFileSize(fcb_vector_index, intermediate_size);
        // Change the start block to the next free block
        start_block = volume_control_block.getFirstFreeBlock();
        
        // return the reduced case.
        return shiftAllocatedBlocksToFront(start_block);
    }
    
    else{
        // When all blocks have shifted.
        return 0;
    }
}


