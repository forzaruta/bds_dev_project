// Copyright(c) 1996 Leendert Ammeraal. All rights reserved.
// This program text occurs in Chapter 7 of
//
//   nethergod (1996) Algorithms and Data Structures in C++,
//       Chichester: John Wiley.

/* disktree:
 Demonstration program for a B-tree on disk. After
 building the B-tree by entering integers on the
 keyboard or by supplying them as a text file, we can
 insert and delete items via the keyboard. We can also
 search the B-tree for a given item. Each time, the tree
 or a search path is displayed. In contrast to program
 btree, program disktree writes, reads and updates nodes
 on disk, using a binary file. The name of this file is
 to be entered on the keyboard. If a B-tree with that
 name exists, that B-tree is used; otherwise such a file
 is created.
 Caution:
 Do not confuse the (binary) file for the B-tree with
 the optional textfile for input data. Use different
 file-name extensions, such as .bin and .txt.
 */
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include <iostream>
#include <cstdlib>
#include <LsmTree.h>
#include <thread>

// for the string creation in the delete file loop
#include <sstream>

int main()
{

    //long pagesize = std::sysconf(_SC_PAGE_SIZE);

    //cout << pagesize << endl;

    // 10       = number of levels for the lsm tree
    // 10485760 = passing 10,485,760 bytes or 10mb as max file size for c1
    // 2        = double size for each additional level
    // true     = should the entire c0 level be copied during rollingMerge() ?
    // .8       = what percentage of c1's size should the max size on c0 be before merge roll occurs?
    // 2        = merge strategy, defaults to 2

    //LsmTree lsm_tree(10, 10485760, 2, true);
    LsmTree lsm_tree(5, 10485760, 2, true, .8, 2);


//    dtype x1 = 0;
//    while (x1 < 3000)
//    {
//        //cout << "INSERTING TO LSM TREE VALUE " << x1 << endl;
//        lsm_tree.insert_value(x1);
//        x1 += 1;
//    }

    srand ( time(NULL) );
    for (int t=0;t<10000;t++)
    {
        long random_x;
        random_x = rand() % 1000000;
        lsm_tree.insert_value(random_x);
    }


    //lsm_tree.printStats();

    // test insert read delete
    //lsm_tree.insert_value(1636);
    //lsm_tree.read_value(1636);
    //lsm_tree.delete_value(1636);


    // delete the c1-n.bin files after the program runs
    for (int x = 1; x <= 10; x++)
    {
        int a = x;
        stringstream ss;
        ss << a;
        string str = ss.str();
        string fileName2 = "c" + str + ".bin";
        remove(fileName2.c_str());
    }



    // detect how many threads are available

    //may return 0 when not able to detect
    unsigned concurentThreadsSupported = thread::hardware_concurrency();
    cout << "Threads Supported - " << concurentThreadsSupported << endl;





//    std::cout <<
//    "Demonstration program for a B-tree on disk. The\n"
//    "structure of the B-tree is shown by indentation.\n"
//    "For each node, the number of links to other nodes\n"
//    "will not be greater than " << M <<
//    ", the order M of the B-tree.\n" <<
//    "The B-tree representation is similar to the\n"
//    "table of contents of a book. The items stored in\n"
//    "each node are displayed on a single line.\n\n";
//    char TreeFileName[50];
//    std::cout <<
//    "Enter name of (possibly nonexistent) BINARY file for\n"
//    "the B-tree: ";
//    std::cin >> std::setw(50) >> TreeFileName;
//    Btree t(TreeFileName);
//    std::cout <<
//    "\nEnter a (possibly empty) sequence of integers,\n"
//    "followed by a slash (/):\n";
//    dtype x;
//    char ch = 0;
//    while (std::cin >> x, !std::cin.fail())
//    { t.insert(x); ch = 1;
//    }
//    if (ch) t.print();
//    std::cin.clear(); std::cin >> ch; // Skip terminating character
//    std::cout <<  "\nDo you want data to be read from a text"
//    "file? (Y/N): ";
//    std::cin >> ch;
//    if (toupper(ch) == 'Y')
//    {  char InpFileName[50];
//        std::cout << "Name of this textfile: ";
//        std::cin >> std::setw(50) >> InpFileName;
//        t.insert(InpFileName);
//        t.print();
//    }
//    for (;;)
//    {  std::cout <<
//        "\nEnter an integer, followed by I, D, or S (for\n"
//        "Insert, Delete and Search), or enter Q to quit: ";
//        std::cin >> x >> ch;
//        if (std::cin.fail()) break;
//        ch = toupper(ch);
//        switch(ch)
//        {
//            case 'S': t.ShowSearch(x); break;
//            case 'I': t.insert(x); break;
//            case 'D': t.DelNode(x); break;
//            default:
//                std::cout << "Invalid command, use S, I or D\n"; break;
//        }
//        if (ch == 'I' || ch == 'D') t.print();
//    }
//    return 0;
}
