#ifndef LSMLEVELMEMORY_H
#define LSMLEVELMEMORY_H

typedef long dtype;

#include <stdio.h>
#include <fstream>
#include <iomanip>
//#include <stdlib.h>
#include <vector>
#include <ctype.h>
#include <iostream>
#include <cstdlib>

enum status {InsertNotComplete, Success, DuplicateKey,
   Underflow, NotFound};

#define M 5  // Order of B-tree: M link fields in each node

using namespace std;
#include <stdio.h> // added to satisfy requirement for NULL

struct node {
   int n;        // Number of items stored in a node (n < M)
   dtype k[M-1]; // Data items (only the first n in use)
   node *p[M];   // Pointers to other nodes (n+1 in use)
};

#define M 5  // Order of B-tree: M link fields in each node

class LsmLevelMemory {
public:



    static int total_nodes_count;
    static int total_values_count;

    LsmLevelMemory(): root(NULL){}
    void insert(dtype x);
    void print()const{std::cout << "LsmLevelMemory - Contents:\n"; pr(root, 0);}
    //void printValuesCount()const{std::cout << "TOTAL IS -----> "; getValuesCount(root);}
    int getNodesCount();
    void DelNode(dtype x);
    void ShowSearch(dtype x)const;
    bool search_value(dtype x)const;
    std::vector<long> getNValues(const node *r, int c0TotalNodes, bool copyAllFromC0)const;
    std::vector<long> memoryLevelCopy(LsmLevelMemory *c0, bool copyAllFromC0);
    int getValuesCount();
private:
    node *root;
    status ins(node *r, dtype x, dtype &y, node* &u);
    void pr(const node* r, int nSpace)const;
    int calculateNodesCount(const node* r) const;
    int calculateValuesCount(const node *r)const;

    int NodeSearch(dtype x, const dtype *a, int n)const;
    status del(node *r, dtype x);
};

#endif // LsmLevelMemory_H
