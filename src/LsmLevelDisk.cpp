#include "LsmLevelDisk.h"

#include <stdio.h>
#include <fstream>
#include <iomanip>
//#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>

typedef long dtype;

using namespace std;

LsmLevelDisk::LsmLevelDisk()
{

}

LsmLevelDisk::LsmLevelDisk(const char *TreeFileName)
{  std::ifstream test(TreeFileName, std::ios::in);
    // Remove  "| std::ios::nocreate" if your compiler does not accept it.
    int NewFile = test.fail();
    test.clear(); test.close();
    if (NewFile)
    {  file.open(TreeFileName, std::ios::out | std::ios::in |
                 std::ios::trunc | std::ios::binary);
        // std::ios::binary required with MSDOS, but possibly
        // not accepted with other environments.
        root = FreeList = NIL;
        long start[2] = {NIL, NIL};
        file.write((char*)start, 2 * sizeof(long));
    }  else
    {  long start[2];
        file.open(TreeFileName, std::ios::out | std::ios::in |
                   std::ios::binary); // See above note.
        file.seekg(-1L, std::ios::end);
        char ch;
        file.read(&ch, 1); // Read signature.
        file.seekg(0L, std::ios::beg);
        file.read((char *)start, 2 * sizeof(long));
        if (ch != sizeof(int))
        {  std::cout << "Wrong file format.\n"; exit(1);
        }
        root = start[0]; FreeList = start[1];
        RootNode.n = 0;   // Signal for function ReadNode
        ReadNode(root, RootNode);
        print();
    }
}

LsmLevelDisk::~LsmLevelDisk()
{  long start[2];
    file.seekp(0L, std::ios::beg);
    start[0] = root; start[1] = FreeList;
    file.write((char*)start, 2 * sizeof(long));
    // The remaining code of this destructor is slightly
    // different from that in the first print of the book.
    // The length of the final binary file, including the
    // signature byte at the end, will now always be an odd
    // number, as it should be. There is a similar change in
    // the function GetNode.I am grateful to Chian Wiz from
    // Singapore, who showed me the possibility of a 'file leak',
    // that is, an unused byte, which sometimes caused problems
    // with the program 'showfile', when this was applied to
    // this binary file. Such problems should no longer occur.
    // L. A.
    char ch = sizeof(int); // Signature
    file.seekg(0L, std::ios::end);
    if ((file.tellg() & 1) == 0)
        file.write(&ch, 1);
    // If the current file length is an even number, a
    // signature is added; otherwise it is already there.
    file.close();
}

void LsmLevelDisk::insert(dtype x)
{  long pNew;
    dtype xNew;
    status_disk code = ins(root, x, xNew, pNew);
    //if (code == Disk_DuplicateKey)
        //std::cout << "Duplicate key ignored.\n";
    if (code == Disk_InsertNotComplete)
    {  long root0 = root;
        root = GetNode();
        RootNode.n = 1; RootNode.k[0] = xNew;
        RootNode.p[0] = root0; RootNode.p[1] = pNew;
        WriteNode(root, RootNode);
    }
}

void LsmLevelDisk::insert(const char *InpFileName)
{  std::ifstream InpFile(InpFileName, std::ios::in);
    if (InpFile.fail())
    {  std::cout << "Cannot open input file " << InpFileName
        << std::endl;
        return;
    }
    dtype x;
    while(InpFile >> x) insert(x);
    InpFile.clear(); InpFile.close();
}





//int disk_counter = 0;

std::vector<long> disk_arr;

std::vector<long> LsmLevelDisk::getNValues(long r, long total_disk_nodes_count)
{
    /* ********************************************** DEBUG ******************************************************
    *************************************************************************************************************/
    //cout << "DISK - total_disk_nodes_count VALUE IS - " << total_disk_nodes_count << endl;
    //cout << "DISK - NNODES VALUE IS - " << Nnodes << endl;
    //cout << "DISK - THE COUNTER AND NNODES VALUES " << disk_counter << " " << Nnodes  << endl;
    //************************************************************************************************************

    int disk_counter_limit = total_disk_nodes_count / 2;

    int disk_counter = 0;

    if (r != NIL)
   {
        int i;
        node_disk Node; ReadNode(r, Node);



        int j;

        /* ********************************************** DEBUG ******************************************************
        *************************************************************************************************************/
        //cout << "DISK - THE SIZE OF R " << sizeof(r) << endl;
        //************************************************************************************************************

        int pointer_position = 0;



             for (i=0; i < Node.n; i++)
              {
                    if (disk_counter < disk_counter_limit) {

                        disk_arr.push_back(Node.k[i]);

                        /* ********************************************** DEBUG ******************************************************
                        *************************************************************************************************************/
                        //cout << setw(3) << "DISK - adding to array - value " << Node.k[i] << endl;
                        //************************************************************************************************************
                    }
              }

              disk_counter += 1;



            if (disk_counter < disk_counter_limit)
            {
//
                for (j=0; j <= Node.n; j++)
                {
                    LsmLevelDisk::getNValues(Node.p[j], total_disk_nodes_count);
                }
//            }
       }
   }

    /* ********************************************** DEBUG ******************************************************
    *************************************************************************************************************/
//    cout << "DISK - ARRAY SIZE - " << disk_arr.size() << endl;
//    cout << "DISK - ARRAY VALUES - " << endl;
//
//    // DEBUG - PRINT THE ARRAY'S VALUES
//    const size_t disk_count = disk_arr.size();
//    for (size_t index = 0; index < disk_count; ++index) {
//        cout << index << " = " << disk_arr[index] << endl;
//    }
    //************************************************************************************************************

    return disk_arr;
}

std::vector<long> disk_arr_2;
std::vector<long> LsmLevelDisk::getNValuesX(long r, long total_disk_nodes_count, int total_to_pass_next_level)
{


    /* ********************************************** DEBUG ******************************************************
    *************************************************************************************************************/
    //cout << "DISK - total_disk_nodes_count VALUE IS - " << total_disk_nodes_count << endl;
    //cout << "DISK - NNODES VALUE IS - " << Nnodes << endl;
    //cout << "DISK - THE COUNTER AND NNODES VALUES " << disk_counter << " " << Nnodes  << endl;
    //************************************************************************************************************

    //int disk_counter_limit = total_disk_nodes_count / 2;

    //cout << "TOTAL NODES - " << total_disk_nodes_count << " total to pass next level " << total_to_pass_next_level << endl;


    //cout << "TOTAL TO PASS ' " << total_to_pass_next_level << endl;

    int disk_counter = 0;

    if (r != NIL)
   {
        int i;
        node_disk Node; ReadNode(r, Node);



        int j;


        int pointer_position = 0;


















//             for (i=0; i < Node.n; i++)
//              {
//                    if (disk_counter < total_to_pass_next_level && disk_counter < total_disk_nodes_count) {
//
//                        disk_arr_2.push_back(Node.k[i]);
//
//                        if (disk_arr_2.size() <= total_to_pass_next_level)
//                        {
//                            return disk_arr_2;
//                        }
//                        cout << "size of array disk array AFTER total_to_pass_next_level FILLED " << disk_arr_2.size() << endl;

                    for (i=0; i < Node.n; i++)
                    {
                    if (disk_arr_2.size() <= total_to_pass_next_level) {

                        disk_arr_2.push_back(Node.k[i]);
                    } else {

                        disk_arr_2.pop_back();


                        return disk_arr_2;


























                        //disk_counter += 1;

                        /* ********************************************** DEBUG ******************************************************
                        *************************************************************************************************************/
                        //cout << setw(3) << "DISK - adding to array - value " << Node.k[i] << endl;
                        //************************************************************************************************************
                    }
              }

              disk_counter += 1;



            if (disk_counter < total_to_pass_next_level && disk_counter < total_disk_nodes_count)
            {
//
                for (j=0; j <= Node.n; j++)
                {
                    LsmLevelDisk::getNValuesX(Node.p[j], total_disk_nodes_count, total_to_pass_next_level);
                }
//            }
       }
   }

    /* ********************************************** DEBUG ******************************************************
    *************************************************************************************************************/
//    cout << "DISK - ARRAY SIZE - " << disk_arr_2.size() << endl;
//    cout << "DISK - ARRAY VALUES - " << endl;
//
//    // DEBUG - PRINT THE ARRAY'S VALUES
//    const size_t disk_count = disk_arr_2.size();
//    for (size_t index = 0; index < disk_count; ++index) {
//        cout << index << " = " << disk_arr_2[index] << endl;
//    }
    //************************************************************************************************************


    return disk_arr_2;
}

std::vector<long> LsmLevelDisk::diskLevelCopy(long r)
{

    long total_disk_nodes_count = getNodesCount(r);

    //node *r = root;
    long root = r;

    return LsmLevelDisk::getNValues(root, total_disk_nodes_count);
}

std::vector<long> LsmLevelDisk::diskLevelCopyX(long r, int total_to_pass_next_level )
{
    disk_arr_2.clear();

    long total_disk_nodes_count = getNodesCount(r) ;



    //node *r = root;
    long root = r;


    std::vector<long> v = LsmLevelDisk::getNValuesX(root, total_disk_nodes_count, total_to_pass_next_level);
    //v.erase( unique( v.begin(), v.end() ), v.end() );


    set<long> s;
    unsigned size = v.size();
    for( unsigned i = 0; i < size; ++i ) s.insert( v[i] );
    v.assign( s.begin(), s.end() );

    return v;
}

int LsmLevelDisk::disk_total_nodes_count = 0;
int LsmLevelDisk::disk_calculateNodesCount(long r)
{
    if (r != NIL)
    {
        int i;
        node_disk Node; ReadNode(r, Node);
        disk_total_nodes_count++;
        for (i=0; i <= Node.n; i++) disk_calculateNodesCount(Node.p[i]);
    }
    return disk_total_nodes_count;
}

int LsmLevelDisk::getNodesCount(long r)
{
    long root = r;

    // set the counter to start at 0
    LsmLevelDisk::disk_total_nodes_count = 0;

    return disk_calculateNodesCount(root);
}

int LsmLevelDisk::disk_total_values_count = 0;
int LsmLevelDisk::disk_calculateValuesCount(long r)
{
    if (r != NIL)
    {
        int i;
        node_disk Node; ReadNode(r, Node);
        for (i=0; i < Node.n; i++) disk_total_values_count++;
        for (i=0; i <= Node.n; i++) disk_calculateValuesCount(Node.p[i]);
    }
    return disk_total_values_count;





//    {  if (r != NIL)
//    {  int i;
//        std::cout << std::setw(nSpace) << "";
//        node_disk Node; ReadNode(r, Node);
//        for (i=0; i < Node.n; i++) std::cout << Node.k[i] << " ";
//        std::cout << std::endl;
//        for (i=0; i <= Node.n; i++) pr(Node.p[i], nSpace+8);
//    }
//}






}

int LsmLevelDisk::getValuesCount(long r)
{
    long root = r;

    // set the counter to start at 0
    LsmLevelDisk::disk_total_values_count = 0;

    return disk_calculateValuesCount(root);
}

status_disk LsmLevelDisk::ins(long r, dtype x, dtype &y, long &q)
{  // Insert x in *this. If not completely successful, the
    // integer y and the pointer q remain to be inserted.
    // Return value:
    //    Success, DuplicateKey or InsertNotComplete.
    long pNew, pFinal;
    int i, j, n;
    dtype xNew, kFinal;
    status_disk code;
    if (r == NIL){q = NIL; y = x; return Disk_InsertNotComplete;}
    node_disk Node, NewNode;
    ReadNode(r, Node);
    n = Node.n;
    i = NodeSearch(x, Node.k, n);
    if (i < n && x == Node.k[i]) return Disk_DuplicateKey;
    code = ins(Node.p[i], x, xNew, pNew);
    if (code != Disk_InsertNotComplete) return code;
    // Insertion in LsmLevelDisk did not completely succeed;
    // try to insert xNew and pNew in the current node:
    if (n < M - 1)
    {  i = NodeSearch(xNew, Node.k, n);
        for (j=n; j>i; j--)
        {  Node.k[j] = Node.k[j-1]; Node.p[j+1] = Node.p[j];
        }
        Node.k[i] = xNew; Node.p[i+1] = pNew; ++Node.n;
        WriteNode(r, Node); return Disk_Success;
    }
    // Current node is full (n == M - 1) and will be split.
    // Pass item k[h] in the middle of the augmented
    // sequence back via parameter y, so that it
    // can move upward in the tree. Also, pass a pointer
    // to the newly created node back via parameter q:
    if (i == M - 1) {kFinal = xNew; pFinal = pNew;} else
    {  kFinal = Node.k[M-2]; pFinal = Node.p[M-1];
        for (j=M-2; j>i; j--)
        {  Node.k[j] = Node.k[j-1]; Node.p[j+1] = Node.p[j];
        }
        Node.k[i] = xNew; Node.p[i+1] = pNew;
    }
    int h = (M - 1)/2;
    y = Node.k[h];           // y and q are passed on to the
    q = GetNode();           // next higher level in the tree
    // The values p[0],k[0],p[1],...,k[h-1],p[h] belong to
    // the left of k[h] and are kept in *r:
    Node.n = h;
    // p[h+1],k[h+1],p[h+2],...,k[M-2],p[M-1],kFinal,pFinal
    // belong to the right of k[h] and are moved to *q:
    NewNode.n = M - 1 - h;
    for (j=0; j < NewNode.n; j++)
    {  NewNode.p[j] = Node.p[j + h + 1];
        NewNode.k[j] =
        (j < NewNode.n - 1 ? Node.k[j + h + 1] : kFinal);
    }
    NewNode.p[NewNode.n] = pFinal;
    WriteNode(r, Node); WriteNode(q, NewNode);
    return Disk_InsertNotComplete;
}

void LsmLevelDisk::pr(long r, int nSpace)
{  if (r != NIL)
    {  int i;
        std::cout << std::setw(nSpace) << "";
        node_disk Node; ReadNode(r, Node);
        for (i=0; i < Node.n; i++) std::cout << Node.k[i] << " ";
        std::cout << std::endl;
        for (i=0; i <= Node.n; i++) pr(Node.p[i], nSpace+8);
    }
}

int LsmLevelDisk::NodeSearch(dtype x, const dtype *a, int n)const
{  int middle, left=0, right = n - 1;
    if (x <= a[left]) return 0;
    if (x > a[right]) return n;
    while (right - left > 1)
    {  middle = (right + left)/2;
        (x <= a[middle] ? right : left) = middle;
    }
    return right;
}

void LsmLevelDisk::ShowSearch(dtype x)
{  std::cout << "Search path:\n";
    int i, j, n;
    long r = root;
    node_disk Node;
    while (r != NIL)
    {  ReadNode(r, Node);
        n = Node.n;
        for (j=0; j<Node.n; j++) std::cout << " " << Node.k[j];
        std::cout << std::endl;
        i = NodeSearch(x, Node.k, n);
        if (i < n && x == Node.k[i])
        {  std::cout << "Key " << x << " found in position " << i
            << " of last displayed node.\n";
            return;
        }
        r = Node.p[i];
    }
    std::cout << "Key " << x << " not found.\n";
}

void LsmLevelDisk::DelNode(dtype x)
{  long root0;
    switch (del(root, x))
    {
        case Disk_NotFound:
            //std::cout << x << " not found.\n";
            break;
        case Disk_Underflow:
            root0 = root;
            root = RootNode.p[0]; FreeNode(root0);
            if (root != NIL) ReadNode(root, RootNode);
            break;
    }
}

status_disk LsmLevelDisk::del(long r, dtype x)
{  if (r == NIL) return Disk_NotFound;
    node_disk Node;
    ReadNode(r, Node);
    int i, j, pivot, n = Node.n;
    dtype *k = Node.k;  // k[i] means Node.k[i]
    const int nMin = (M - 1)/2;
    status_disk code;
    long *p = Node.p, pL, pR;       // p[i] means Node.p[i]
    i = NodeSearch(x, k, n);
    if (p[0] == NIL)  // Are we dealing with a leaf?
    {  if (i == n || x < k[i]) return Disk_NotFound;
        // x == k[i]
        for (j=i+1; j < n; j++)
        {  k[j-1] = k[j]; p[j] = p[j+1];
        }
        Node.n--;
        WriteNode(r, Node);
        return Node.n >= (r==root ? 1 : nMin) ?
        Disk_Success : Disk_Underflow;
    }
    // *r is an interior node, not a leaf:
    if (i < n && x == k[i])
    {  // x found in an interior node. Go to left child
        // and follow a path all the way to a leaf,
        // using rightmost branches:
        long q = p[i], q1; int nq; node_disk Node1;
        for (;;)
        {  ReadNode(q, Node1);
            nq = Node1.n; q1 = Node1.p[nq];
            if (q1 == NIL) break;
            q = q1;
        }
        // Exchange k[i] (= x) with rightmost item in leaf:
        k[i] = Node1.k[nq-1];
        Node1.k[nq - 1] = x;
        WriteNode(r, Node); WriteNode(q, Node1);
    }
    // Delete x in leaf of suLsmLevelDisk with root p[i]:
    code = del(p[i], x);
    if (code != Disk_Underflow) return code;
    // There is underflow; borrow, and, if necessary, merge:
    // Too few data items in node *p[i]
    node_disk NodeL, NodeR;
    if (i > 0)
    {  pivot = i - 1; pL = p[pivot]; ReadNode(pL, NodeL);
        if (NodeL.n > nMin) // Borrow from left sibling
        {  // k[pivot] between pL and pR:
            pR = p[i];
            // Increase contents of *pR, borrowing from *pL:
            ReadNode(pR, NodeR);
            NodeR.p[NodeR.n + 1] = NodeR.p[NodeR.n];
            for (j=NodeR.n; j>0; j--)
            {  NodeR.k[j] = NodeR.k[j-1];
                NodeR.p[j] = NodeR.p[j-1];
            }
            NodeR.n++;
            NodeR.k[0] = k[pivot];
            NodeR.p[0] = NodeL.p[NodeL.n];
            k[pivot] = NodeL.k[--NodeL.n];
            WriteNode(pL, NodeL); WriteNode(pR, NodeR);
            WriteNode(r, Node);
            return Disk_Success;
        }
    }
    pivot = i;
    if (i < n)
    {  pR = p[pivot+1]; ReadNode(pR, NodeR);
        if (NodeR.n > nMin) // Borrow from right sibling
        {  // k[pivot] between pL and pR:
            pL = p[pivot]; ReadNode(pL, NodeL);
            // Increase contents of *pL, borrowing from *pR:
            NodeL.k[NodeL.n] = k[pivot];
            NodeL.p[NodeL.n + 1] = NodeR.p[0];
            k[pivot] = NodeR.k[0];
            NodeL.n++; NodeR.n--;
            for (j=0; j < NodeR.n; j++)
            {  NodeR.k[j] = NodeR.k[j+1];
                NodeR.p[j] = NodeR.p[j+1];
            }
            NodeR.p[NodeR.n] = NodeR.p[NodeR.n + 1];
            WriteNode(pL, NodeL); WriteNode(pR, NodeR);
            WriteNode(r, Node);
            return Disk_Success;
        }
    }
    // Merge; neither borrow left nor borrow right possible.
    pivot = (i == n ? i - 1 : i);
    pL = p[pivot]; pR = p[pivot+1];
    // Add k[pivot] and *pR to *pL:
    ReadNode(pL, NodeL); ReadNode(pR, NodeR);
    NodeL.k[NodeL.n] = k[pivot];
    NodeL.p[NodeL.n + 1] = NodeR.p[0];
    for (j=0; j < NodeR.n; j++)
    {  NodeL.k[NodeL.n + 1 + j] = NodeR.k[j];
        NodeL.p[NodeL.n + 2 + j] = NodeR.p[j+1];
    }
    NodeL.n += 1 + NodeR.n;
    FreeNode(pR);
    for (j=i+1; j < n; j++)
    {  k[j-1] = k[j]; p[j] = p[j+1];
    }
    Node.n--;
    WriteNode(pL, NodeL); WriteNode(r, Node);
    return
    Node.n >= (r == root ? 1 : nMin) ? Disk_Success : Disk_Underflow;
}

void LsmLevelDisk::ReadNode(long r, node_disk &Node)
{  if (r == NIL) return;
    if (r == root && RootNode.n > 0) Node = RootNode; else
    {  file.seekg(r, std::ios::beg);
        file.read((char*)&Node, sizeof(node_disk));
    }
}

void LsmLevelDisk::WriteNode(long r, const node_disk &Node)
{  if (r == root) RootNode = Node;
    file.seekp(r, std::ios::beg);
    file.write((char*)&Node, sizeof(node_disk));
}

void LsmLevelDisk::ReadStart()
{  long start[2];
    file.seekg(0L, std::ios::beg);
    file.read((char *)start, 2 * sizeof(long));
    root = start[0]; FreeList = start[1];
    ReadNode(root, RootNode);
}

long LsmLevelDisk::GetNode()  // Modified (see also the destructor ~LsmLevelDisk)
{  long r;
    node_disk Node;
    if (FreeList == NIL)
    {  file.seekp(0L, std::ios::end); // Allocate space on disk; if
        r = file.tellp() & ~1;    // file length is an odd number,
        WriteNode(r, Node);       // the new node will overwrite
    }  else                      // signature byte at end of file
    {  r = FreeList;
        ReadNode(r, Node);        // To update FreeList:
        FreeList = Node.p[0];     // Reduce the free list by 1
    }
    return r;
}


void LsmLevelDisk::FreeNode(long r)
{  node_disk Node;
    ReadNode(r, Node);
    Node.p[0] = FreeList;
    FreeList = r;
    WriteNode(r, Node);
}

bool LsmLevelDisk::search_value(dtype x)
{  std::cout << "Search path:\n";
    int i, j, n;
    long r = root;
    node_disk Node;
    while (r != NIL)
    {  ReadNode(r, Node);
        n = Node.n;
        for (j=0; j<Node.n; j++) std::cout << " " << Node.k[j];
        std::cout << std::endl;
        i = NodeSearch(x, Node.k, n);
        if (i < n && x == Node.k[i])
        {  std::cout << "Key " << x << " found in position " << i
            << " of last displayed node.\n";
            return true;
        }
        r = Node.p[i];
    }
    std::cout << "Key " << x << " not found.\n";
    return false;
}

int LsmLevelDisk::getFileSize(const std::string &fileName)
{
    std::ifstream file(fileName.c_str(), std::ifstream::in | std::ifstream::binary);

    if(!file.is_open())
    {
        return -1;
    }

    file.seekg(0, std::ios::end);
    int fileSize = file.tellg();
    file.close();

    return fileSize;
}
