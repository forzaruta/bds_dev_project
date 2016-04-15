/**
    C++11 - GCC Compiler
    LsmTree.h
    Creates an LsmTree using data structures that are both memory and disk resident.
    Lsm Tree consists of several levels including at least one memory and one disk resident data structure.
    @author N. Ruta
    @version 1.0 4/01/16
 */
#ifndef LSMTREE_H
#define LSMTREE_H

#include "LsmLevelMemory.h"
#include "LsmLevelDisk.h"

using namespace std;

struct LsmLevel {
   int levelNumber;             // The level number --> for example c1
   int fileSize;                // the level's associated file's size --> for example size of c1.bin
   long maxFileSize;            // the maximum size, in kb, of the level's associated file
   char fileName[10];           // the name of the disk resident file for the level --> for example c1.bin
   LsmLevelDisk *lsmLevelDisk;  //
};

class LsmTree
{
    public:

        // tunable parameters -
        // NOT YET IMPLEMENTED size of m
        //

        /**
            Constructor to initialize the Lsm Tree using tunable parameters.

            Examples:



            @param numberOfLevels the number of levels for the lsm tree
            @param firstLevelFileSize
            @param sizeBetweenLevels
            @param copyAllFromC0

            // 1 for chunk all moves to where it can fit
            // 2 for insert all here then take out whatever doesn't fit and move to next
            // 3 for insert what fits here and then take the rest and add it to data for next level
            @param mergeStrategy LsmTree::updateLevels() determines strategy using this param
        */
        LsmTree(int numberOfLevels, long firstLevelFileSize, int sizeBetweenLevels, bool copyAllFromC0, double c0_percentage_of_c1, int mergeStrategy);
        virtual ~LsmTree();



        //static int numberOfLevels;

        // Adds an item to the Lsm Tree.
        void insert_value(dtype value);

        // Deletes an item from the Lsm Tree
        void delete_value(dtype value);

        // Search for the value in the Lsm Tree.
        void read_value(dtype value);

        // Functions to get the virtual and physical memory stats
        int parseLine(char* line);
        int getValueVirtualMemory();
        int getValuePhysicalMemory();

        void printStats();

    protected:
    private:

        bool copyAllFromC0;
        int numberOfLevels;
        int mergeStrategy;
        int firstLevelFileSize;
        double c0_percentage_of_c1;


        // a vector to contain all of the level structs
        vector<LsmLevel> levels;

        // an array to contain a maximum of 11 instances of the lsmLevelDisk class
        LsmLevelDisk lsmLevelDisks[11];

        // c0 instance of LsmLevelMemory
        LsmLevelMemory c0;

        // rollingMerge function is responsible for the rolling merge process once c0 fills up
        // copyAllFromC0 - should the enire c0 level be copied to c1?
        void rollingMerge(bool copyAllFromC0);

        // the rolling merge strategy is determined here.
        // once c1 is full, this function is called to move data between subsequent levels.
        void updateLevels(std::vector<long> c1_array, LsmLevelDisk* c1, int numberOfLevels, int mergeStrategy);
};

#endif // LSMTREE_H
