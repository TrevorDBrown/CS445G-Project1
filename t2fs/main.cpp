/*
  CS 445(G) - Dr. Qi Li
  Project 1 - t2fs (Travis and Trevor's File System)
  Simulated File System
  Trevor D. Brown and Travis Anderson

  main.cpp - the main class of the program.
*/

#include <pthread.h>            // Pthreads library
#include "main.hpp"             // Main header file

using namespace std;            // All implicit references to functions made in this class are for std.

disk the_disk = *new disk(0, "My Disk");    // Declares a global disk

// Thread 1 runner function
void *thread1(void *param){
    
    the_disk.createPPOFT(pthread_self());   // Create a PPOFT for the thread
    
    // Create a new file (file 1, 2 blocks)
    the_disk.create("file1", "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");
    
    // Write new content to the file.
    the_disk.write(pthread_self(), "file1", "This is an update to the file!");
    
    // Print the PPOFTs and SWOFT to show their states.
    the_disk.printPPOFTs();
    the_disk.printSWOFT();
    
    // Clsoe the file
    the_disk.close(pthread_self(), "file1");
    
    //Reprint PPOFTs and SWOFT.
    the_disk.printPPOFTs();
    the_disk.printSWOFT();
    
    // Create another new file (file2, 1 block)
    the_disk.create("file2", "This is a new file. One block in size.");
    
    // Write new content to the file (4 blocks)
    the_disk.write(pthread_self(), "file2", "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");
    
    // Close the file
    the_disk.close(pthread_self(), "file2");
    
    // Exit the thread
    printf("\nPthread ID %i is closing.\n", pthread_self());
    pthread_exit(0);
}

// Thread 2 runner function
void *thread2(void *param){
    // Create PPOFT for the pthread
    the_disk.createPPOFT(pthread_self());
    
    // Open the file
    the_disk.open(pthread_self(), "file1");
    // Read the file.
    string file_content = the_disk.read("file1");
    
    // Print the file content.
    printf("\nThe file content:\n");
    printf("%s\n", file_content.c_str());
    
    // Close the file.
    the_disk.close(pthread_self(), "file1");
    
    // Exit the pthread.
    printf("\nPthread ID %i is closing.\n", pthread_self());
    pthread_exit(0);
}

// Thread3 runner function
void *thread3(void *param){
    //Create PPOFT for pthread
    the_disk.createPPOFT(pthread_self());
    
    // Open the file.
    the_disk.open(pthread_self(), "file2");
    // Read the file.
    string file_content = the_disk.read("file2");
    
    // Print the file's content
    printf("\nThe file content:\n");
    printf("%s\n", file_content.c_str());
    
    // Close the file.
    the_disk.close(pthread_self(), "file2");
    
    // Exit the pthread.
    printf("\nPthread ID %i is closing.\n", pthread_self());
    pthread_exit(0);
}

// Thread4 runner function.
void *thread4(void *param){
    // Create PPOFT for pthread
    the_disk.createPPOFT(pthread_self());
    
    // List the files in the directory
    the_disk.dir();
    // Delete file1
    the_disk.del("file1");
    // Relist the files in the directory
    the_disk.dir();
    
    // Exit the pthread.
    printf("\nPthread ID %i is closing.\n", pthread_self());
    pthread_exit(0);
}

/*
    main(int argc, char *argv[])
    The main method of the program
 */
int main(int argc, char *argv[]){
    // Print welcome message.
    printf("t2fs (Trevor and Travis's File System)\n");
    printf("(c)2018 Trevor D. Brown and Travis Anderson.\n\n");
    
    // Print new disk information.
    printf("New disk (%s) created!\n", the_disk.getLabel().c_str());

    // Declare a new pthread
    pthread_t p1; // Pthread (p1)
    
    // Declare and initialize thread attributes
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    // Create Pthread p1:
    pthread_create(&p1, &attr, thread1, NULL);
    printf("Pthread p1 created.\n");
    
    // Join thread when complete
    pthread_join(p1, NULL);
    
    // Create pthread 2 and 3
    pthread_t p2, p3;
    pthread_create(&p2, &attr, thread2, NULL);
    printf("Pthread p2 created.\n");
    pthread_create(&p3, &attr, thread3, NULL);
    printf("Pthread p3 created.\n");
    
    // Join threads when complete
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    
    // Create pthread 4
    pthread_t p4;
    pthread_create(&p4, &attr, thread4, NULL);
    printf("Pthread p4 created.\n");
    
    // Join thread when complete..
    pthread_join(p4, NULL);
    
    // Print the disk free block bitmap
    the_disk.printFreeBlockBitmap();
    
    // End program
    return 0;
}
