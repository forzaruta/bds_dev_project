/**
    C++11 - GCC Compiler
    LsmTree.cpp
    Creates an LsmTree using data structures that are both memory and disk resident.
    Lsm Tree consists of several levels including at least one memory and one disk resident data structure.
    @author N. Ruta
    @version 1.0 4/01/16
 */
#include "LsmTree.h"
#include "LsmLevelDisk.h"
#include "LsmLevelMemory.h"

// includes added for detecting virtual and physical memory usage
#include "sys/types.h"
#include "sys/sysinfo.h"

#include <typeinfo>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

// Constructs the Lsm Tree object.
LsmTree::LsmTree(int numberOfLevels, long firstLevelMaxFileSize, int sizeBetweenLevels, bool copyAllFromC0, double c0_percentage_of_c1, int mergeStrategy)
{

    // C1 LEVEL WORKING CODE
//    LsmLevel c1_level;
//
//    c1_level.levelNumber = 1;
//
//    //100000
//    c1_level.maxFileSize = firstLevelMaxFileSize;
//
//    char LevelFileName[10] = "c1.bin";
//    strncpy( c1_level.fileName, LevelFileName, sizeof(c1_level.fileName)-1 );
//
//    //LsmLevelDisk c1;
//
//    new (&c1) LsmLevelDisk(c1_level.fileName);
//
//    c1_level.lsmLevelDisk = &c1;
//
//    levels.push_back(c1_level);
    // END C1 LEVEL WORKING CODE


    LsmTree::copyAllFromC0 = copyAllFromC0;
    LsmTree::numberOfLevels = numberOfLevels;
    LsmTree::mergeStrategy = mergeStrategy;
    LsmTree::firstLevelFileSize = firstLevelMaxFileSize;
    LsmTree::c0_percentage_of_c1 = c0_percentage_of_c1;

    // an int to represent the max file size
    // it is larger after each level creation in the for loop below by using 'sizeBetweenLevels'
    long levelMaxFileSize = firstLevelMaxFileSize;

    for (int i = 1; i <= numberOfLevels; i++) {

        LsmLevel c_level;

        c_level.levelNumber = i;

        c_level.maxFileSize = levelMaxFileSize;

        // chars to convert int to char for the filename
        char char1;
        char char2;
        char FileName[10];

        // for the c10.bin file name, do the following to create the char array
        if (i == 10) {
            char1 =  '0' +  1 ;
            char2 = '0' + 0;
            char FileName[10] =  { 'c',char1, char2, '.', 'b', 'i', 'n', '\0' };

        // for c1.bin-c9.bin, do the folliwng to create the char array
        } else {
          char1 =  '0' + i ;
          char FileName[10] =  { 'c',char1, '.', 'b', 'i', 'n', '\0' };
        }

        // create a string of the char array
        strncpy(c_level.fileName, FileName, sizeof(c_level.fileName)-1);

        // create an LsmLevelDisk object for each level, pass in the filename created above
        new (&lsmLevelDisks[i]) LsmLevelDisk(c_level.fileName);
        c_level.lsmLevelDisk = &lsmLevelDisks[i];

        // add the LsmLevel to the vector of levels representing the LsmTree's total levels
        levels.push_back(c_level);

        // set the max file size for the next level
        levelMaxFileSize = levelMaxFileSize * sizeBetweenLevels;
    }

		//lsmLevelDisks[i] = LsmLevelDisk(c1_level.fileName);

    //LsmLevelDisk(c1_level.fileName) : lsmLevelDisks(4);
    //vector<LsmLevelDisk> lsmLevelDisks(20);


//for(int i=0; i<2; ++i){
//    //lsmLevelDisks[i] = i;
//    new (&lsmLevelDisks[i]) LsmLevelDisk(LevelFileName);
//}



    //vector<LsmLevelDisk> objects (numberOfLevels-1);
//    int no_of_objects = numberOfLevels-1;
//
//    LsmLevelDisk* pmyClasses = new LsmLevelDisk[no_of_objects];
//
//    for (int i=0; i < no_of_objects; i++)
//{
//    pmyClasses[i] = &c3;
//}
//for (int i=0; i < no_of_objects; i++)
//{
     //pmyClasses[i].SomeFunction();
//}
//                int level_counter = numberOfLevels - 1;
//
//                for (int index = 1; index < level_counter; index++)
//                {
//                    LsmLevel c_level;
//
//                    c_level.levelNumber = 2;
//
//                    //100000
//                    c_level.maxFileSize = firstLevelMaxFileSize * 2;
//
//                    char LevelFileName2[10] = "c2.bin";
//                    strncpy( c_level.fileName, LevelFileName2, sizeof(c_level.fileName)-1 );
//
//                    new (&c2) LsmLevelDisk(c_level.fileName);
//
//                    c2_level.lsmLevelDisk = &c2;
//
//                    levels.push_back(c2_level);
//                }







    // WORKING TEST INSERT LEVEL

//    LsmLevel c2_level;
//
//    c2_level.levelNumber = 2;
//
//    c2_level.maxFileSize = firstLevelMaxFileSize * 2;
//
//    char LevelFileName2[10] = "c2.bin";
//    strncpy( c2_level.fileName, LevelFileName2, sizeof(c2_level.fileName)-1 );
//
//    new (&c2) LsmLevelDisk(c2_level.fileName);
//
//    c2_level.lsmLevelDisk = &c2;
//
//    levels.push_back(c2_level);

    // END WORKING TEST








   // LsmLevelDisk c2;

    //c2.set(c2_level.fileName);
    // LsmLevelDisk c2(c2_level.fileName);

    //c2 = new  LsmLevelDisk(c2_level.fileName);





    //LsmLevelDisk* c2 = new LsmLevelDisk(c2_level.fileName);


    //LsmLevelDisk* c2 = new LsmLevelDisk(c2_level.fileName);

    //LsmLevelDisk c2 =

    //new (&c2) LsmLevelDisk(c2_level.fileName);




}

LsmTree::~LsmTree()
{
    //dtor
}

// Adds an item to the Lsm Tree.
void LsmTree::insert_value( dtype value )
{

//    int x1 = 0;
//    while (x1 < 2000)
//   {
//    c0.insert(x1);
//    x1 += 1;
//   }

    //LsmLevelMemory::values_count = 0;
    //LsmLevelMemory::total_nodes_count = 0;
    //int c0NodesCount = ;

    //cout << "BEFORE - NODES COUNT FOR c0 " << c0.getNodesCount() << endl;

//    if (c0.getNodesCount() == 0 || c0.getNodesCount() < 20 )
//    {
//        cout << "c0 nodes count is 0, inserting value - " << value << endl;
//        c0.insert(value);
//
//    } else
    //cout << "BEFORE WHAT IS THE NODES COUNT? IT IS -- " << c0NodesCount << endl;




    //cout << "FIRST LEVEL MAX " << LsmTree::firstLevelFileSize << endl;
    //cout << "percentage number is " << LsmTree::c0_percentage_of_c1 << endl;

    int c0_max_size = (int) (LsmTree::firstLevelFileSize * LsmTree::c0_percentage_of_c1) / 50;
    //get c0 size by finding the count of nodes/////////////////////
    //cout << "C0 Size " << c0_max_size << endl;
    //cout << "firstLevelFileSize is " << LsmTree::firstLevelFileSize;


    //cout << "c0 has this many values " << c0.getValuesCount() << endl;

    // is c0 full?
    // NO
    if (c0.getNodesCount() < 3)
//    {
      //if (c0.getValuesCount() < c0_max_size)
      {


        /* ********************************************** DEBUG ******************************************************
        *************************************************************************************************************/
//        cout << "C0 is NOT FULL - C0 VALUE INSERT - " << value << endl;
//        c0.print();
        //************************************************************************************************************

        // insert the value to c0
        c0.insert(value);

        return;

    // is c0 full?
    // YES
    } else {

         /* ********************************************** DEBUG ******************************************************
        *************************************************************************************************************/
        //cout << "C0 is FULL - ROLLING MERGE" << endl;
        //************************************************************************************************************

        // true - copy entire c0 to c1 on rollingMerge
        rollingMerge(LsmTree::copyAllFromC0);

         /* ********************************************** DEBUG ******************************************************
        *************************************************************************************************************/
        //cout << "INSERT VALUE " << value << " TO C0 AFTER ROLLING MERGE" << endl;
        //************************************************************************************************************

        // insert the value to c0
        c0.insert(value);
    }



    /* ********************************************** DEBUG ******************************************************
    *************************************************************************************************************/
//    cout << "NODES COUNT FOR c0 " << c0.getNodesCount() << endl;
//    c0.print();
    //************************************************************************************************************





   //cout << x1 << endl;

   //c0.print();


//       int x2 = 0;
//    while (x2 < 30000)
//   {
//    //cout << "INSERTING VALUE TO C0 - " << x1;
//    c0.insert(x2);
//    x2 += 1;
//   }



    //c0.ShowSearch(66);


    //std::cout << "THE SIZE IS " << sizeof(c0) << endl;



    // print out the first 10 values of c0
//    int x2 = 0;
//    while (x2 < 9)
//    {
//        //c0
//
//        x2 += 1;
//    }





// TEST CREATION c1 and c2 //

//    char TreeFileName[] = "c1.bin";
//
//    new (&c1) LsmLevelDisk(TreeFileName);


//    std::vector<int> arr = c0.memoryLevelCopy();
//
 //   const size_t count = arr.size();
//    for (size_t index = 0; index < count; ++index) {
//        cout << "INSERTING -- " << index << " = " << arr[index] << endl;
//        c1.insert(arr[index]);
//
//
//    }
//    cout << "PRINT C1 CONTENTS AFTER INSERTS - " << endl;
//    c1.print();
//
//
//    cout << "c0 before delete" << endl;
//    c0.print();
//
//        for (size_t index = 0; index < count; ++index) {
//        cout << "INSERTING -- " << index << " = " << arr[index] << endl;
//        c0.DelNode(arr[index]);
//
//
//    }
//
//    cout << "c0 after delete" << endl;
//    c0.print();




//    LsmLevelDisk c2;
//
//    char TreeFileNameC2[] = "c2.bin";
//////
//////
//    new (&c2) LsmLevelDisk(TreeFileNameC2);
//
//
//
//        for (size_t index = 0; index < count; ++index) {
//        cout << "INSERTING -- " << index << " = " << arr[index] << endl;
//        c2.insert(arr[index]);
//
//
//    }
//
//    cout << "C2 CONTENTS - " << endl;
//    c2.print();
// END TEST CREATION c1 and c2 //





}

// current behavior is to check each level and execute a BLIND DELETE ONCE
// THIS MAY CAUSE DUPLCIATES IF MY CODE DOESNT WORK - I HAVE A SET CREATION IN THE diskLevelCopy function to make sure there are never dubplicates in a level
void LsmTree::delete_value(dtype value)
{
        c0.DelNode(value);

        for (int i = 0; i < numberOfLevels; ++i)
        {
            (*levels[i].lsmLevelDisk).DelNode(value);
        }
}

// does a read request, if the value is found, the first time it is found...the function returns.
void LsmTree::read_value(dtype value)
{
        // look for the value in c0 memory
        bool memory_search_result = c0.search_value(value);
        if (memory_search_result) { return; }

        // not found in memory, look for it at each level
        for (int i = 0; i < numberOfLevels; ++i)
        {
            bool disk_search_result = (*levels[i].lsmLevelDisk).search_value(value);
            if (disk_search_result) { return; }
        }
}

// parse lines for proc/self/status file
int LsmTree::parseLine(char* line){
        int i = strlen(line);
        while (*line < '0' || *line > '9') line++;
        line[i-3] = '\0';
        i = atoi(line);
        return i;
    }

    // Virtual Memory currently used by current process:
    int LsmTree::getValueVirtualMemory(){ //Note: this value is in KB!
        FILE* file = fopen("/proc/self/status", "r");
        int result = -1;
        char line[128];


        while (fgets(line, 128, file) != NULL){
            if (strncmp(line, "VmSize:", 7) == 0){
                result = parseLine(line);
                break;
            }
        }
        fclose(file);
        return result;
    }




    // physical memory currently used by current process:
    int LsmTree::getValuePhysicalMemory(){ //Note: this value is in KB!
        FILE* file = fopen("/proc/self/status", "r");
        int result = -1;
        char line[128];


        while (fgets(line, 128, file) != NULL){
            if (strncmp(line, "VmRSS:", 6) == 0){
                result = parseLine(line);
                break;
            }
        }
        fclose(file);
        return result;
    }

    void LsmTree::printStats() {

        struct sysinfo memInfo;

        sysinfo (&memInfo);
        long long totalVirtualMem = memInfo.totalram;
        //Add other values in next statement to avoid int overflow on right hand side...
        totalVirtualMem += memInfo.totalswap;
        totalVirtualMem *= memInfo.mem_unit;

        cout << "TOTAL VIRTUAL MEMORY - " << totalVirtualMem << endl;

        long long virtualMemUsed = memInfo.totalram - memInfo.freeram;
        //Add other values in next statement to avoid int overflow on right hand side...
        virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
        virtualMemUsed *= memInfo.mem_unit;

        cout << "TOTAL VIRTUAL MEMORY USED - " << virtualMemUsed << endl;

        cout << "TOTAL AVAILABLE VIRTUAL MEMORY - " << totalVirtualMem - virtualMemUsed << endl;

        // Virtual Memory currently used by current process:
        cout << "Virtual Memory currently used by current process: " << getValueVirtualMemory() << endl;

        long long totalPhysMem = memInfo.totalram;
        //Multiply in next statement to avoid int overflow on right hand side...
        totalPhysMem *= memInfo.mem_unit;

        cout << "TOTAL Physical MEMORY  - " << totalPhysMem << endl;

        // PHYSICAL Memory currently used by current process:
        cout << "PHYSICAL Memory currently used by current process: " << getValuePhysicalMemory() << endl;


        long long physMemUsed = memInfo.totalram - memInfo.freeram;
        //Multiply in next statement to avoid int overflow on right hand side...
        physMemUsed *= memInfo.mem_unit;

        cout << "TOTAL PHYSICAL MEMORY USED - " << physMemUsed << endl;
        cout << "TOTAL AVAILABLE PHYSICAL MEMORY - " << totalPhysMem - physMemUsed << endl;

        cout << "C0 PRINT CONTENTS" << endl;
        c0.print();

        /* ********************************************** DEBUG ******************************************************
        *************************************************************************************************************/

        for (int a = 0; a < LsmTree::numberOfLevels; a++)
        {
        cout << "-------------------- START - DEBUG DISK LEVEL ----------------------------- " << endl;
        cout << "C" << a+1 << " file size is - " << LsmLevelDisk::getFileSize(levels[a].fileName) << endl;
        cout <<  "LEVEL NUMBER - " << levels[a].levelNumber << endl;
        cout <<  "maxFileSize - " << levels[a].maxFileSize << endl;
        cout <<  "lsmLevelDisk - " << levels[a].lsmLevelDisk << endl;
        cout <<  "fileName - " << levels[a].fileName << endl;
        cout <<  "the values count in this level is " << (*levels[a].lsmLevelDisk).getValuesCount((*levels[a].lsmLevelDisk).root) << endl;
        (*levels[a].lsmLevelDisk).print();
        cout << endl;
        cout << "--------------------END - DEBUG DISK LEVEL----------------------------- " << endl;
        }
        //************************************************************************************************************
 }

 void LsmTree::updateLevels(std::vector<long> c1_array, LsmLevelDisk* c1, int numberOfLevels, int mergeStrategy)
 {

        // if mergeStrategy == 1 do chunk
        // if mergeStrategy == 2 do fill each level and remainder to next level

        // if mergeStrategy is set to 1, do the chunk moving to largest place it can fit all together merge strategy
        // maybe called a modified sharding technique
        if (mergeStrategy == 1)
        {


            // initialize the array as the c1 array before updating c2-n
            // initialize pointer to c1 to start the update process
            std::vector<long> current_array = c1_array;
            LsmLevelDisk* previous_level_pointer = c1;
            LsmLevelDisk* current_level_pointer;

            // for each level of the LSM Tree after C1
            for (int i = 1; i <= numberOfLevels; i++)
            {

                    /* ********************************************** DEBUG ******************************************************
                    *************************************************************************************************************/
    //                cout << "updateLevels() -  DISK ARRAY SIZE IS ----->>>> " << current_array.size() << endl;
    //                cout << "updateLevels() -  DISK LEVEL COPY COMPLETE ------------------------->" << endl;
    //
    //                    // DEBUG - PRINT THE ARRAY'S VALUES
    //                    const size_t disk_count = current_array.size();
    //                    for (size_t index = 0; index < disk_count; ++index) {
    //                        cout << "updateLevels() - current_aray - BEGINNING OF FOR LOOP FOR EACH LEVEL " << index << " = " << current_array[index] << endl;
    //                    }
                    //************************************************************************************************************

                current_level_pointer = levels[i].lsmLevelDisk;


                // get size of disk level
                std::string stringFileName(levels[i].fileName);

                int fileSize = LsmLevelDisk::getFileSize(stringFileName);

                //is level full? YES
                if (fileSize > levels[i].maxFileSize)
                {

                    const size_t counter = current_array.size();

                    // INSERT FROM PREVIOUS LEVEL
                    for (size_t index = 0; index < (counter); index++)
                    {

                            /* ********************************************** DEBUG ******************************************************
                            *************************************************************************************************************/
                            //cout << "updateLevels() - INSERTING DISK TO DISK -- " << index << " = " << current_array[index] << endl;
                            //************************************************************************************************************

                            // get the instance of LsmLevelDisk that this pointer is pointing at
                            // and insert to that LsmLevelDisk object
                            (*current_level_pointer).insert(current_array[index]);
                    }

                   /* ********************************************** DEBUG ******************************************************
                   *************************************************************************************************************/
                   //cout << "updateLevels() -  INSERTED TO DISK LEVEL FROM PREVIOUS LEVEL" << endl;
                   //************************************************************************************************************


                    /* ********************************************** DEBUG ******************************************************
                   *************************************************************************************************************/
                   //cout << "updateLevels() -  DELETING FROM PREVIOUS LEVEL" << endl;
                   //************************************************************************************************************

                    /* ********************************************** DEBUG ******************************************************
                    *************************************************************************************************************/
    //                cout << levels[i-1].fileName << " before delete" << endl;
    //                //cout << "updateLevels() -  NODES COUNT - " << (*previous_level_pointer).getNodesCount() << endl;
    //                (*previous_level_pointer).print();
                    //************************************************************************************************************

                    for (size_t index = 0; index < counter; ++index) {

                        /* ********************************************** DEBUG ******************************************************
                        *************************************************************************************************************/
                        //cout << "updateLevels() -  DELETING FROM OLD -- " << index << " = " << current_array[index] << endl;
                        //************************************************************************************************************
                        (*previous_level_pointer).DelNode(current_array[index]);

                        //current_array   remove( 99, current_array);

                        //current_array.erase(remove(current_array.begin(), current_array.end(), current_array[index]), current_array.end());
                        //std::remove( current_array.begin(), current_array.end(), current_array[index] );

                        //cout << " I TRIED TO DELETE - " << current_array[index] << " FROM -- " << endl;
                        //(*previous_level_pointer).print();

                    }



                    /* ********************************************** DEBUG ******************************************************
                    *************************************************************************************************************/
    //                cout << "updateLevels() - " << levels[i-1].fileName << " after delete" << endl;
    //                (*previous_level_pointer).print();
                    //************************************************************************************************************



                    //GET ARRAY FROM CURRENT LEVEL AND STORE OUTSIDE OF LOOP

                    /* ********************************************** DEBUG ******************************************************
                    *************************************************************************************************************/
    //                cout << "updateLevels() -  GETTING NEW ARRAY FROM CURRENT DISK LEVEL from fileSize check FALSE" << endl;
    //
    //                cout << levels[i].fileName << "updatedLevels() - print the current level disk values - " << endl;
    //                (*current_level_pointer).print();
                    //************************************************************************************************************

                    // create a pointer to the LsmLevelDisk memory location
                    //current_level_pointer = levels[i].lsmLevelDisk;

                    // copy a portion of disk level to a new array

                    // pass root of copy level

                    current_array = (*current_level_pointer).diskLevelCopy((*current_level_pointer).root);
                    previous_level_pointer = current_level_pointer;

                    /* ********************************************** DEBUG ******************************************************
                    *************************************************************************************************************/
    //                cout << "updateLevels() -  DISK ARRAY SIZE IS ----->>>> " << current_array.size() << endl;
    //                cout << "updateLevels() -  DISK LEVEL COPY COMPLETE ------------------------->" << endl;
    //
    //                    // DEBUG - PRINT THE ARRAY'S VALUES
    //                    const size_t disk_count = current_array.size();
    //                    for (size_t index = 0; index < disk_count; ++index) {
    //                        cout << "updateLevels() - current_aray - LEVEL FULL YES " << index << " = " << current_array[index] << endl;
    //                    }
                    //************************************************************************************************************

                //is level full? NO
                } else {

                    const size_t counter2 = current_array.size();

                    // INSERT FROM PREVIOUS LEVEL
                    for (size_t index = 0; index < (counter2); index++)
                    {

                            /* ********************************************** DEBUG ******************************************************
                            *************************************************************************************************************/
                            //cout << "updateLevels() - INSERTING DISK TO DISK -- " << index << " = " << current_array[index] << endl;
                            //************************************************************************************************************

                            // get the instance of LsmLevelDisk that this pointer is pointing at
                            // and insert to that LsmLevelDisk object
                            (*current_level_pointer).insert(current_array[index]);
                    }

                   /* ********************************************** DEBUG ******************************************************
                   *************************************************************************************************************/
                   //cout << "updateLevels() -  INSERTED TO DISK LEVEL FROM PREVIOUS LEVEL" << endl;
                   //************************************************************************************************************


                    /* ********************************************** DEBUG ******************************************************
                   *************************************************************************************************************/
                   //cout << "updateLevels() -  DELETING FROM PREVIOUS LEVEL" << endl;
                   //************************************************************************************************************

                    /* ********************************************** DEBUG ******************************************************
                    *************************************************************************************************************/
                    //cout << levels[i-1].fileName << " before delete" << endl;
                    //cout << "updateLevels() -  NODES COUNT - " << (*previous_level_pointer).getNodesCount() << endl;
                    //(*previous_level_pointer).print();
                    //************************************************************************************************************

                    for (size_t index = 0; index < counter2; ++index) {

                        /* ********************************************** DEBUG ******************************************************
                        *************************************************************************************************************/
                        //cout << "updateLevels() -  DELETING FROM OLD -- " << index << " = " << current_array[index] << endl;
                        //************************************************************************************************************
                        (*previous_level_pointer).DelNode(current_array[index]);
                    }


                    /* ********************************************** DEBUG ******************************************************
                    *************************************************************************************************************/
                    //cout << "updateLevels() - " << levels[i-1].fileName << " after delete" << endl;
                    //(*previous_level_pointer).print();
                    //************************************************************************************************************

                    return;
                }
            }
    }

    // if mergeStrategy == 2 do fill each level and remainder to next level
    if (mergeStrategy == 2)
    {


            // initialize the array as the c1 array before updating c2-n
            // initialize pointer to c1 to start the update process
            std::vector<long> current_array = c1_array;

            LsmLevelDisk* previous_level_pointer = c1;
            LsmLevelDisk* current_level_pointer;






            // ****************************************************************
            //int current_array_size = current_array.size() * 32;



            //cout << current_array_size << " THE CURRENT SIZE " << c1_array.size() << endl;
            // **************************************************************************



            // for each level of the LSM Tree after C1
            for (int i = 1; i < numberOfLevels; ++i)
            {

                std::vector<long> *active_array;
                std::vector<long> *current_array_after_c1;

                if (levels[i].levelNumber == 2)
                {
                    active_array = &current_array;
                }

                if (levels[i].levelNumber > 2) {
                    active_array = current_array_after_c1;
                }







                const size_t counter1 = (*active_array).size();





                // ****************************************************************

                int current_level_max_values = (int)levels[i].maxFileSize / 50;
                //int current_level_max_values = 1;
                 //int current_level_max_values = 5;
//                cout << levels[i].fileName << endl;
//                cout <<  " MAX VALUES THAT FIT IN THIS LEVEL ARE " << current_level_max_values << endl;
//                cout <<  " THE CURRENT SIZE " << counter1 << endl;
                // **************************************************************************







                    /* ********************************************** DEBUG ******************************************************
                    *************************************************************************************************************/
                    //cout << "updateLevels() -  DISK ARRAY SIZE IS ----->>>> " << current_array.size() << endl;
    //                cout << "updateLevels() -  DISK LEVEL COPY COMPLETE ------------------------->" << endl;
    //
    //                    // DEBUG - PRINT THE ARRAY'S VALUES
    //                    const size_t disk_count = current_array.size();
    //                    for (size_t index = 0; index < disk_count; ++index) {
    //                        cout << "updateLevels() - current_aray - BEGINNING OF FOR LOOP FOR EACH LEVEL " << index << " = " << current_array[index] << endl;
    //                    }
                    //************************************************************************************************************

                current_level_pointer = levels[i].lsmLevelDisk;


                // get size of disk level
                std::string stringFileName(levels[i].fileName);

                int fileSize = LsmLevelDisk::getFileSize(stringFileName);



                //CAN THIS LEVEL CONTAIN THE ENTIRE ARRAY PASSED TO IT? NO
                if (current_level_max_values < counter1)
                {


                    //cout << "NO +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ " << endl;

                    //cout << levels[i].fileName << " current_level_max_values: " <<  current_level_max_values << " counter1: " << counter1 << endl;


//                    const size_t counter1 = current_array.size();
//
                    // INSERT FROM PREVIOUS LEVEL
                    for (size_t index = 0; index < (counter1); index++)
                    {

                            /* ********************************************** DEBUG ******************************************************
                            *************************************************************************************************************/
                            //cout << "updateLevels() - INSERTING DISK TO DISK -- " << index << " = " << current_array[index] << endl;
                            //************************************************************************************************************

                            // get the instance of LsmLevelDisk that this pointer is pointing at
                            // and insert to that LsmLevelDisk object
                            (*current_level_pointer).insert((*active_array)[index]);
                    }


//
//                   /* ********************************************** DEBUG ******************************************************
//                   *************************************************************************************************************/
//                   //cout << "updateLevels() -  INSERTED TO DISK LEVEL FROM PREVIOUS LEVEL" << endl;
//                   //************************************************************************************************************
//
//
//                    /* ********************************************** DEBUG ******************************************************
//                   *************************************************************************************************************/
//                   //cout << "updateLevels() -  DELETING FROM PREVIOUS LEVEL" << endl;
//                   //************************************************************************************************************
//
//                    /* ********************************************** DEBUG ******************************************************
//                    *************************************************************************************************************/
//    //                cout << levels[i-1].fileName << " before delete" << endl;
//    //                //cout << "updateLevels() -  NODES COUNT - " << (*previous_level_pointer).getNodesCount() << endl;
//                        (*previous_level_pointer).print();
//                    //************************************************************************************************************




                    /* ********************************************** DEBUG ******************************************************
                    *************************************************************************************************************/
//                    cout << "PREVIOUS PRINT BEFORE DELETE IS -" << endl;
//                    (*previous_level_pointer).print();
//                    cout << "CURRENT PRINT IS - " << endl;
//                    (*current_level_pointer).print();
                    //************************************************************************************************************


//
                    for (size_t index = 0; index < counter1; ++index) {

                        /* ********************************************** DEBUG ******************************************************
                        *************************************************************************************************************/
                        //cout << "updateLevels() -  DELETING FROM OLD -- " << index << " = " << current_array[index] << endl;
                        //************************************************************************************************************
                        (*previous_level_pointer).DelNode((*active_array)[index]);

//                        cout << " I TRIED TO DELETE - " << (*active_array)[index] << " FROM -- " << endl;
//                        (*previous_level_pointer).print();

                    }




////
////                    /* ********************************************** DEBUG ******************************************************
////                    *************************************************************************************************************/
//                        cout << levels[i-1].fileName << endl;
//                        cout << "PREVIOUS PRINT AFTER DELETE IS -" << endl;
//                                            (*previous_level_pointer).print();


////    //                cout << "updateLevels() - " << levels[i-1].fileName << " after delete" << endl;
////    //                (*previous_level_pointer).print();
////                    //************************************************************************************************************
////
////
////
////
////
////
////
////                    //GET ARRAY FROM CURRENT LEVEL AND STORE OUTSIDE OF LOOP
////
////                    /* ********************************************** DEBUG ******************************************************
////                    *************************************************************************************************************/
////    //                cout << "updateLevels() -  GETTING NEW ARRAY FROM CURRENT DISK LEVEL from fileSize check FALSE" << endl;
////    //
////    //                cout << levels[i].fileName << "updatedLevels() - print the current level disk values - " << endl;
////    //                (*current_level_pointer).print();
////                    //************************************************************************************************************
////
////                    // create a pointer to the LsmLevelDisk memory location
////                    //current_level_pointer = levels[i].lsmLevelDisk;
////
////                    // copy a portion of disk level to a new array
////
////                    // pass root of copy level
////
                        //int total_to_pass_next_level = current_array.size() - current_level_max_values;

                        //current_array.clear();


                        int total_to_pass_next_level = (*current_level_pointer).getValuesCount((*current_level_pointer).root) - current_level_max_values;


                        //current_array.size() - current_level_max_values;












//                                        std::vector<long> *active_array;
//                std::vector<long> *current_array_after_c1;x
//
//                if (c2) then use current_array
//                    active_array = current_array;
//
//                else use current_array_after_c1
//                    active_array = current_array_after_c1;

                        std::vector<long> temp_array = (*current_level_pointer).diskLevelCopyX(((*current_level_pointer).root), total_to_pass_next_level);







                        current_array_after_c1 = &temp_array;

                        //cout << "total to pass to next level is: " << total_to_pass_next_level << "  " << "current level max - VALUES COUNT: "
                        //<< current_level_max_values << " " <<  (*current_level_pointer).getValuesCount((*current_level_pointer).root) << endl;

                        //current_array = (*current_level_pointer).diskLevelCopy(((*current_level_pointer).root));
////
                        previous_level_pointer = current_level_pointer;

                    /* ********************************************** DEBUG ******************************************************
                    *************************************************************************************************************/
//                    cout << "updateLevels() -  DISK ARRAY SIZE IS ----->>>> " << current_array.size() << endl;
//                    cout << "updateLevels() -  DISK LEVEL COPY COMPLETE ------------------------->" << endl;
//
                        // DEBUG - PRINT THE ARRAY'S VALUES
//                        (*current_level_pointer).print();
//                        const size_t disk_count = current_array.size();
//                        for (size_t index = 0; index < disk_count; ++index) {
//                            cout << "updateLevels() - current_aray - LEVEL FULL YES " << index << " = " << current_array[index] << endl;
//                        }
                    //************************************************************************************************************























//                                        //const size_t counter2 = current_array.size();
//
//                    // INSERT FROM PREVIOUS LEVEL
//                    for (size_t index = 0; index < (counter1); index++)
//                    {
//
//                            /* ********************************************** DEBUG ******************************************************
//                            *************************************************************************************************************/
//                            //cout << "updateLevels() - INSERTING DISK TO DISK -- " << index << " = " << current_array[index] << endl;
//                            //************************************************************************************************************
//
//                            // get the instance of LsmLevelDisk that this pointer is pointing at
//                            // and insert to that LsmLevelDisk object
//                            (*current_level_pointer).insert(current_array[index]);
//                    }
//
//                   /* ********************************************** DEBUG ******************************************************
//                   *************************************************************************************************************/
//                   //cout << "updateLevels() -  INSERTED TO DISK LEVEL FROM PREVIOUS LEVEL" << endl;
//                   //************************************************************************************************************
//
//
//                    /* ********************************************** DEBUG ******************************************************
//                   *************************************************************************************************************/
//                   //cout << "updateLevels() -  DELETING FROM PREVIOUS LEVEL" << endl;
//                   //************************************************************************************************************
//
//                    /* ********************************************** DEBUG ******************************************************
//                    *************************************************************************************************************/
//                    //cout << levels[i-1].fileName << " before delete" << endl;
//                    //cout << "updateLevels() -  NODES COUNT - " << (*previous_level_pointer).getNodesCount() << endl;
//                    //(*previous_level_pointer).print();
//                    //************************************************************************************************************
//
//                    for (size_t index = 0; index < counter1; ++index) {
//
//                        /* ********************************************** DEBUG ******************************************************
//                        *************************************************************************************************************/
//                        //cout << "updateLevels() -  DELETING FROM OLD -- " << index << " = " << current_array[index] << endl;
//                        //************************************************************************************************************
//                        (*previous_level_pointer).DelNode(current_array[index]);
//                    }
//
//
//                    /* ********************************************** DEBUG ******************************************************
//                    *************************************************************************************************************/
//                    //cout << "updateLevels() - " << levels[i-1].fileName << " after delete" << endl;
//                    //(*previous_level_pointer).print();
//                    //************************************************************************************************************
//
//                    return;


















                //CAN THIS LEVEL CONTAIN THE ENTIRE ARRAY PASSED TO IT? YES
                } else {

                    //cout << "YES IT CAN CONTAIN IT +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ " << endl;

                    const size_t counter2 = (*active_array).size();

                    // INSERT FROM PREVIOUS LEVEL
                    for (size_t index = 0; index < (counter2); index++)
                    {

                            /* ********************************************** DEBUG ******************************************************
                            *************************************************************************************************************/
                            //cout << "updateLevels() - INSERTING DISK TO DISK -- " << index << " = " << current_array[index] << endl;
                            //************************************************************************************************************

                            // get the instance of LsmLevelDisk that this pointer is pointing at
                            // and insert to that LsmLevelDisk object
                            (*current_level_pointer).insert((*active_array)[index]);
                    }

                   /* ********************************************** DEBUG ******************************************************
                   *************************************************************************************************************/
                   //cout << "updateLevels() -  INSERTED TO DISK LEVEL FROM PREVIOUS LEVEL" << endl;
                   //************************************************************************************************************


                    /* ********************************************** DEBUG ******************************************************
                   *************************************************************************************************************/
                   //cout << "updateLevels() -  DELETING FROM PREVIOUS LEVEL" << endl;
                   //************************************************************************************************************

                    /* ********************************************** DEBUG ******************************************************
                    *************************************************************************************************************/
                    //cout << levels[i-1].fileName << " before delete" << endl;
                    //cout << "updateLevels() -  NODES COUNT - " << (*previous_level_pointer).getNodesCount() << endl;
                    //(*previous_level_pointer).print();
                    //************************************************************************************************************

                    for (size_t index = 0; index < counter2; ++index) {

                        /* ********************************************** DEBUG ******************************************************
                        *************************************************************************************************************/
                        //cout << "updateLevels() -  DELETING FROM OLD -- " << index << " = " << current_array[index] << endl;
                        //************************************************************************************************************
                        (*previous_level_pointer).DelNode((*active_array)[index]);
                    }


                    /* ********************************************** DEBUG ******************************************************
                    *************************************************************************************************************/
                    //cout << "updateLevels() - " << levels[i-1].fileName << " after delete" << endl;
                    //(*previous_level_pointer).print();
                    //************************************************************************************************************

                    return;
                }
            }
    }
 }

 void LsmTree::rollingMerge(bool copyAllFromC0)
 {
    // copy a portion of c0 to a new array
    // a pointer to the c0 memory level object
    LsmLevelMemory *cPoint = &c0;
    std::vector<long> arr = c0.memoryLevelCopy(cPoint, copyAllFromC0);

    const size_t count = arr.size();


    //cout << sizeof(vector<long>) + (sizeof(int) * arr.size()) << endl;

    int levelCounter = 0;

    // get size of disk level
    std::string stringFileName(levels[levelCounter].fileName);

    /* ********************************************** DEBUG ******************************************************
    *************************************************************************************************************/
//    cout << " THE VALUE FOR copyAllFromC0 is " << copyAllFromC0 << endl;
//    cout << levels[levelCounter].fileName << "C" << levelCounter+1 << " file size is - " << LsmLevelDisk::getFileSize(stringFileName) << endl;
//    cout <<  "LEVEL NUMBER - " << levels[levelCounter].levelNumber << endl;
//    cout <<  "maxFileSize - " << levels[levelCounter].maxFileSize << endl;
//    cout <<  "lsmLevelDisk - " << levels[levelCounter].lsmLevelDisk << endl;
    //************************************************************************************************************

    int fileSize = LsmLevelDisk::getFileSize(stringFileName);




    // can this level contain the entire array? YES
    int current_level_max_values = (int)levels[levelCounter].maxFileSize / 50;
    if (current_level_max_values > count)
    {



    // is this level full? NO
    // if the level is smaller than the threshold, insert the c0 array of values
//    if (fileSize < levels[levelCounter].maxFileSize)
//    {
       // insert to this level
       //insertToLevelDisk(arr, count, c1);
        for (size_t index = 0; index < count; ++index)
        {

            /* ********************************************** DEBUG ******************************************************
            *************************************************************************************************************/
//            cout << "INSERTING FROM WITHIN fileSize CHECK IS TRUE -- " << index << " = " << arr[index] << endl;
            //************************************************************************************************************

            // create a pointer to the LsmLevelDisk memory location
            LsmLevelDisk *c = levels[levelCounter].lsmLevelDisk;

            // get the instance of LsmLevelDisk that this pointer is pointing at
            // and insert to that LsmLevelDisk object
            (*c).insert(arr[index]);
        }

       /* ********************************************** DEBUG ******************************************************
        *************************************************************************************************************/
//       cout << "INSERT TO DISK LEVEL COMPLETE FROM WITHIN fileSize CHECK IS TRUE" << endl;
       //************************************************************************************************************

    // // can this level contain the entire array? NO
    } else {
        // insert to this level

       //insertToLevelDisk(arr, count, c1);
        for (size_t index = 0; index < count; ++index)
        {
            /* ********************************************** DEBUG ******************************************************
            *************************************************************************************************************/
//            cout << "INSERTING FROM WITHIN fileSize check FALSE -- " << index << " = " << arr[index] << endl;
            //************************************************************************************************************

            // create a pointer to the LsmLevelDisk memory location
            LsmLevelDisk *c = levels[levelCounter].lsmLevelDisk;

            // get the instance of LsmLevelDisk that this pointer is pointing at
            // and insert to that LsmLevelDisk object
            (*c).insert(arr[index]);
        }

        /* ********************************************** DEBUG ******************************************************
        *************************************************************************************************************/
//        cout << "INSERT TO DISK LEVEL COMPLETE from fileSize check FALSE" << endl;
        //************************************************************************************************************

        /* ********************************************** DEBUG ******************************************************
        *************************************************************************************************************/
//        cout << "GETTING NEW ARRAY FROM CURRENT DISK LEVEL from fileSize check FALSE" << endl;
        //************************************************************************************************************

        // create a pointer to the LsmLevelDisk memory location
        LsmLevelDisk *c_old = levels[levelCounter].lsmLevelDisk;

        // copy a portion of disk level to a new array




  /////////////////////////////////////////////////////////////////////////////////////////////

                               //current_array.clear();

                        int current_level_max_values = (int)levels[levelCounter].maxFileSize / 50;


                        int total_to_pass_next_level = (*c_old).getValuesCount((*c_old).root) - current_level_max_values;

                        //current_array.size() - current_level_max_values;



                        std::vector<long> arrDisk = (*c_old).diskLevelCopyX(((*c_old).root), total_to_pass_next_level);

                        //cout << "C1 -- total to pass to next level is: " << total_to_pass_next_level << "  " << "C1 -- current level max - VALUES COUNT: "
                        //<< current_level_max_values << " " <<  (*c_old).getValuesCount((*c_old).root) << endl;

                        //current_array = (*current_level_pointer).diskLevelCopy(((*current_level_pointer).root));
////
                        //previous_level_pointer = current_level_pointer;


  /////////////////////////////////////////////////////////////////////////////////////////////




        // pass root of copy level
        //std::vector<long> arrDisk = (*c_old).diskLevelCopy((*c_old).root);

        /* ********************************************** DEBUG ******************************************************
        *************************************************************************************************************/
        //cout << "DISK ARRAY SIZE IS ----->>>> " << arrDisk.size() << endl;
        //cout << "DISK LEVEL COPY COMPLETE ------------------------->" << endl;
        //************************************************************************************************************

        const size_t counter2 = arrDisk.size();








//                        const size_t disk_count = arrDisk.size();
//                        for (size_t index = 0; index < disk_count; ++index) {
//                            cout << "ARRAY " << index << " = " << arrDisk[index] << endl;
//                        }


        // update the levels of the LSM Tree
        LsmTree::updateLevels(arrDisk, c_old, LsmTree::numberOfLevels, LsmTree::mergeStrategy);



        //TEMPORARY CREATE HERE
//
//        LsmLevel c2_level;
//
//         c2_level.levelNumber = 2;
//
//
//
//         LsmLevelDisk c2;
//
//         char DiskLevelFileName[10] = "c2.bin";
//         strncpy( c2_level.fileName, DiskLevelFileName, sizeof(c2_level.fileName)-1 );
//
//
//         new (&c2) LsmLevelDisk(DiskLevelFileName);
//
//
//
//    int firstLevelMaxFileSize = levels[0].maxFileSize;
//
//    //100000
//    c2_level.maxFileSize = firstLevelMaxFileSize * 2;
//
//    cout << "FIRSTLEVELMAXFILESIZE " << firstLevelMaxFileSize << "  times 2 " << firstLevelMaxFileSize * 2 << endl;
//
//    //char LevelFileName[10] = "c1.bin";
//
//
//    //LsmLevelDisk c1;
//
//    //new (&c1) LsmLevelDisk(c2_level.fileName);
//
//    c2_level.lsmLevelDisk = &c2;
//
//    levels.push_back(c2_level);

    // END TEMPORARY CREATE HERE





// BIG DELETE STARTED HERE -------------------------------------------------------------------
//        //CHECK IF THE NEXT LEVEL EXISTS
//
//        //increment counter to check next level
//       levelCounter++;
//
//       // does the next level exist in the vector?
//
//       // yes, it exists
//       if (levelCounter > 0 && levelCounter < levels.size())
//       {
//
//
//
//            /* ********************************************** DEBUG ******************************************************
//            *************************************************************************************************************/
//            cout << "C" << levelCounter+1 << " already exists." << endl;
//            //************************************************************************************************************
//
//            // if it exists, check its file size
//
//            // get size of disk level
//            std::string stringFileName(levels[levelCounter].fileName);
//            cout << levels[levelCounter].fileName << " C" << levelCounter+1 << " file size is - " << LsmLevelDisk::getFileSize(stringFileName) << endl;
//            int fileSize = LsmLevelDisk::getFileSize(stringFileName);
//
//            // if the level to be copied to is small enough
//            if (fileSize < levels[levelCounter].maxFileSize)
//            {
//                /* ********************************************** DEBUG ******************************************************
//                *************************************************************************************************************/
//                cout << "LEVEL " << levelCounter+1 << " HAS ENOUGH ROOM" << endl;
//                //************************************************************************************************************
//
//
////                // create a pointer to the LsmLevelDisk memory location
////                // use levelCounter-1 to get the previous level from which the data is copied
////                LsmLevelDisk *c = levels[levelCounter-1].lsmLevelDisk;
////
////                // copy a portion of disk level to a new array
////
////                // pass root of copy level
////                std::vector<int> arr = (*c).diskLevelCopy((*c).root);
////
////                /* ********************************************** DEBUG ******************************************************
////                *************************************************************************************************************/
////                cout << "DISK ARRAY SIZE IS ----->>>> " << arr.size() << endl;
////                cout << "DISK LEVEL COPY COMPLETE ------------------------->" << endl;
////                //************************************************************************************************************
////
////                const size_t counter2 = arr.size();
//
//                // insert to this level
//                //insertToLevelDisk(arr, count, c1);
//
//                LsmLevelDisk *c_new = levels[levelCounter].lsmLevelDisk;
//
//
//                for (size_t index = 0; index < (counter2); index++)
//                {
//
//                    /* ********************************************** DEBUG ******************************************************
//                    *************************************************************************************************************/
//                    cout << "INSERTING DISK TO DISK -- " << index << " = " << arrDisk[index] << endl;
//                    //************************************************************************************************************
//
//                    // get the instance of LsmLevelDisk that this pointer is pointing at
//                    // and insert to that LsmLevelDisk object
//                    (*c_new).insert(arrDisk[index]);
//                }
//
//               /* ********************************************** DEBUG ******************************************************
//               *************************************************************************************************************/
//               cout << "INSERTED TO DISK LEVEL FROM PREVIOUS LEVEL" << endl;
//               //************************************************************************************************************
//
//
//
//                /* ********************************************** DEBUG ******************************************************
//               *************************************************************************************************************/
//               cout << "DELETING FROM PREVIOUS LEVEL" << endl;
//               //************************************************************************************************************
//
//                /* ********************************************** DEBUG ******************************************************
//                *************************************************************************************************************/
//                cout << levels[levelCounter-1].fileName << " before delete" << endl;
//                cout << "NODES COUNT - " << (*c_old).getNodesCount() << endl;
//                (*c_old).print();
//                //************************************************************************************************************
//
//                for (size_t index = 0; index < counter2; ++index) {
//
//                    /* ********************************************** DEBUG ******************************************************
//                    *************************************************************************************************************/
//                    cout << "DELETING FROM OLD -- " << index << " = " << arrDisk[index] << endl;
//                    //************************************************************************************************************
//                    (*c_old).DelNode(arrDisk[index]);
//                }
//
//                /* ********************************************** DEBUG ******************************************************
//                *************************************************************************************************************/
//                cout << levels[levelCounter-1].fileName << " after delete" << endl;
//                (*c_old).print();
//                //************************************************************************************************************
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//                // get the instance of LsmLevelDisk that this pointer is pointing at
//                // and insert to that LsmLevelDisk object
//
//                //(*c).insert(arr[index]);
//
//
//
//        //        //insertToLevelDisk(arr, count, c1);
//        //        for (size_t index = 0; index < count; ++index)
//        //        {
//        //            cout << "INSERTING FROM WITHIN fileSize check TRUE -- " << index << " = " << arr[index] << endl;
//        //
//        //            //cout << typeid(c1).name() << '\n';
//        //
//        //            // create a pointer to the LsmLevelDisk memory location
//        //            LsmLevelDisk *c = levels[levelCounter].lsmLevelDisk;
//        //
//        //            // get the instance of LsmLevelDisk that this pointer is pointing at
//        //            // and insert to that LsmLevelDisk object
//        //            (*c).insert(arr[index]);
//        //        }
//        //       cout << "INSERT TO DISK LEVEL COMPLETE from FALSE" << endl;
//
//
//
//
//
//            // the level to be copied to is not small enough
//            } else {
//
//            insert here levelCounter
//            for (size_t index = 0; index < (counter2); index++)
//            {
//
//                /* ********************************************** DEBUG ******************************************************
//                *************************************************************************************************************/
//                cout << "INSERTING DISK TO DISK -- " << index << " = " << arrDisk[index] << endl;
//                //************************************************************************************************************
//
//                // get the instance of LsmLevelDisk that this pointer is pointing at
//                // and insert to that LsmLevelDisk object
//                (*c_new).insert(arrDisk[index]);
//            }
//
//            delete from old
//             /* ********************************************** DEBUG ******************************************************
//               *************************************************************************************************************/
//               cout << "DELETING FROM PREVIOUS LEVEL" << endl;
//               //************************************************************************************************************
//
//                /* ********************************************** DEBUG ******************************************************
//                *************************************************************************************************************/
//                cout << levels[levelCounter-1].fileName << " before delete" << endl;
//                cout << "NODES COUNT - " << (*c_old).getNodesCount() << endl;
//                (*c_old).print();
//                //************************************************************************************************************
//
//                for (size_t index = 0; index < counter2; ++index) {
//
//                    /* ********************************************** DEBUG ******************************************************
//                    *************************************************************************************************************/
//                    cout << "DELETING FROM OLD -- " << index << " = " << arrDisk[index] << endl;
//                    //************************************************************************************************************
//                    (*c_old).DelNode(arrDisk[index]);
//                }
//
//                /* ********************************************** DEBUG ******************************************************
//                *************************************************************************************************************/
//                cout << levels[levelCounter-1].fileName << " after delete" << endl;
//                (*c_old).print();
//                //************************************************************************************************************
//
//
//
//            get copy of here
//            /* ********************************************** DEBUG ******************************************************
//            *************************************************************************************************************/
//            cout << "GETTING NEW ARRAY FROM CURRENT DISK LEVEL from fileSize check FALSE" << endl;
//            //************************************************************************************************************
//
//            // create a pointer to the LsmLevelDisk memory location
//            LsmLevelDisk *c_old = levels[levelCounter].lsmLevelDisk;
//
//            // copy a portion of disk level to a new array
//
//            // pass root of copy level
//            std::vector<int> arrDisk = (*c_old).diskLevelCopy((*c_old).root);
//
//            /* ********************************************** DEBUG ******************************************************
//            *************************************************************************************************************/
//            cout << "DISK ARRAY SIZE IS ----->>>> " << arrDisk.size() << endl;
//            cout << "DISK LEVEL COPY COMPLETE ------------------------->" << endl;
//            //************************************************************************************************************
//
//            const size_t counter3 = arrDisk.size();
//
//
//
//            run this recursively until find a small enough level
//
//            }
//
//
//
//
//
//
//
//
//        // if it is too big
//       // no, it doesn't exist
//       } else
//       {
//        /* ********************************************** DEBUG ******************************************************
//        *************************************************************************************************************/
//        cout << "C" << levelCounter+1 << " does not exist." << endl;
//
//        cout << "Creating C" << levelCounter+1 << endl;
//         //************************************************************************************************************
//
//
//
//
//       }





// BIG DELETE ENDED HERE -------------------------------------------------------------------





            //diskLevelCopy()
            // repeat process for next level -->

        // if it doesn't exist, create the next level and do the diskLevelCopy() to the new level

    }





//    cout << "PRINT C1 CONTENTS AFTER INSERTS - " << endl;
//    c1.print();







    for (int i=0; i < levels.size(); i++)
    {
        /* ********************************************** DEBUG ******************************************************
        *************************************************************************************************************/
       //cout << "PRINT C" << levels[i].levelNumber << " CONTENTS AFTER INSERTS - " << endl;
       //************************************************************************************************************
       LsmLevelDisk *c_val = levels[i].lsmLevelDisk;
       //(*c_val).print();
    }

    /* ********************************************** DEBUG ******************************************************
    *************************************************************************************************************/
    //cout << "c0 before delete" << endl;
    //cout << "VALUES COUNT FOR c0 " << c0.getValuesCount() << endl;
    //************************************************************************************************************
    //c0.print();

        for (size_t index = 0; index < count; ++index) {

        /* ********************************************** DEBUG ******************************************************
        *************************************************************************************************************/
        //cout << "DELETING FROM C0 -- " << index << " = " << arr[index] << endl;
        //************************************************************************************************************
        c0.DelNode(arr[index]);


        }

    /* ********************************************** DEBUG ******************************************************
    *************************************************************************************************************/
    //cout << "C0 AFTER DELETE" << endl;
    //c0.print();
    //************************************************************************************************************






    /* ********************************************** DEBUG ******************************************************
    *************************************************************************************************************/
//    int levelsDebugCounter = 10;
//    for (int a = 0; a < levelsDebugCounter; a++)
//    {
//    cout << "-------------------- START - DEBUG DISK LEVEL ----------------------------- " << endl;
//    cout << "C" << a+1 << " file size is - " << LsmLevelDisk::getFileSize(levels[a].fileName) << endl;
//    cout <<  "LEVEL NUMBER - " << levels[a].levelNumber << endl;
//    cout <<  "maxFileSize - " << levels[a].maxFileSize << endl;
//    cout <<  "lsmLevelDisk - " << levels[a].lsmLevelDisk << endl;
//    cout <<  "fileName - " << levels[a].fileName << endl;
//    (*levels[a].lsmLevelDisk).print();
//    cout << endl;
//    cout << "--------------------END - DEBUG DISK LEVEL----------------------------- " << endl;
//    }
    //************************************************************************************************************


// std::vector<int> arr = c0.memoryLevelCopy();
//
//    const size_t count = arr.size();
//    for (size_t index = 0; index < count; ++index) {
//        cout << "INSERTING -- " << index << " = " << arr[index] << endl;
//        c1.insert(arr[index]);
//
//
//    }
//    cout << "PRINT C1 CONTENTS AFTER INSERTS - " << endl;
//    c1.print();


    //char TreeFileName[] = "c1.bin";

    //new (&c1) LsmLevelDisk(TreeFileName);



    // get C1's size --> is it full?



// Is C1 full? - No – copy from C0 to C1 – function called memoryLevelCopy()
//
//	         Yes –
//
//			Is there a C2?
//
//				No – create one and copy C1 to C2 – function called diskLevelCopy()
//
//				Yes -
//
//					Is C2 Full ….



 }

// void LsmTree::insertToLevelDisk(std::vector<int> arr, const size_t count, LsmLevelDisk lsmLevelDisk)
// {
//    for (size_t index = 0; index < count; ++index)
//    {
//        cout << "INSERTING From insertToLevelDisk -- " << index << " = " << arr[index] << endl;
//        lsmLevelDisk.insert(arr[index]);
//    }
// }
