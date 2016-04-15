#ifndef LSMLEVELDISK_H
#define LSMLEVELDISK_H

//#include<BTreeNode.h>
#include <stdio.h> // added to satisfy requirement for NULL

#include <fstream>
#include <iostream>
#include <vector>

//using namespace std;

#define M 5  // Order of B-tree: M link fields in each node

typedef long dtype;

enum status_disk {Disk_InsertNotComplete, Disk_Success, Disk_DuplicateKey,
    Disk_Underflow, Disk_NotFound};

struct node_disk {
    int n;        // Number of items stored in a node (n < M)
    dtype k[M-1]; // Data items (only the first n in use)
    long p[M];    // 'Pointers' to other nodes (n+1 in use)
};



class LsmLevelDisk {
public:
    LsmLevelDisk();
    LsmLevelDisk(const char *TreeFileName);
    ~LsmLevelDisk();

    static int disk_total_nodes_count;
    static int disk_total_values_count;

    std::vector<long> disk_arr_2;


    void insert(dtype x);
    void insert(const char *InpFileName);
    void print(){std::cout << "LsmLevelDisk - Contents:\n"; pr(root, 0);}
    void DelNode(dtype x);
    void ShowSearch(dtype x);
    static int getFileSize(const std::string &fileName);
    std::vector<long> getNValues(long r, long total_disk_nodes_count);
    std::vector<long> getNValuesX(long r, long total_disk_nodes_count, int disk_counter_limit);
    std::vector<long> diskLevelCopy(long r);
    std::vector<long> diskLevelCopyX(long r, int current_level_max_values);

    int disk_calculateNodesCount(long r);
    int disk_calculateValuesCount(long r);
    int getNodesCount(long r);
    int getValuesCount(long r);

    // search for the value
    bool search_value(dtype x);

    long root, FreeList;

private:
    enum {NIL=-1};
//    long root, FreeList;
    node_disk RootNode;
    std::fstream file;
    status_disk ins(long r, dtype x, dtype &y, long &u);
    void pr(long r, int nSpace);
    int NodeSearch(dtype x, const dtype *a, int n)const;
    status_disk del(long r, dtype x);
    void ReadNode(long r, node_disk &Node);
    void WriteNode(long r, const node_disk &Node);
    void ReadStart();
    long GetNode();
    void FreeNode(long r);

};

#endif
