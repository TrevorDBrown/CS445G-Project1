/*
  CS 445(G) - Dr. Qi Li
  Project 1 - Simulated File System
  Trevor D. Brown and Travis Anderson

  main.hpp - the main header of the program.
*/

// Include statements
#include <stdio.h>              // Standard I/O library
#include <stdlib.h>             // Standard C library
#include <unistd.h>             // Standard symbolic constants and types

#include "disk.hpp"             // Disk class
#include "ppoft.hpp"            // Per-Process Open File Table class

using namespace std;            // All implicit references to functions made in this class are for std.

// Pthread runner functions
void *thread1(void *param);
void *thread2(void *param);
void *thread3(void *param);
void *thread4(void *param);

// Main method
int main(int argc, char *argv[]);
