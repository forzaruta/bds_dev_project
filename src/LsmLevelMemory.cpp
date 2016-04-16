#include "LsmLevelMemory.h"
#include "LsmTree.h"

#include <vector>

void LsmLevelMemory::insert(dtype x)
{  node *pNew;
   dtype xNew;

   status code = ins(root, x, xNew, pNew);
   //if (code == DuplicateKey)
      //cout << "Duplicate key ignored.\n";
   if (code == InsertNotComplete)
   {  node *root0 = root;
      root = new node;
      root->n = 1; root->k[0] = xNew;
      root->p[0] = root0; root->p[1] = pNew;
   }
}

status LsmLevelMemory::ins(node *r, dtype x, dtype &y, node* &q)
{  // Insert x in *this. If not completely successful, the
   // integer y and the pointer q remain to be inserted.
   // Return value:
   //    Success, DuplicateKey or InsertNotComplete.
   node *pNew, *pFinal;
   int i, j, n;
   dtype xNew, kFinal;
   status code;
   if (r == NULL){q = NULL; y = x; return InsertNotComplete;}
   n = r->n;
   i = NodeSearch(x, r->k, n);
   if (i < n && x == r->k[i]) return DuplicateKey;
   code = ins(r->p[i], x, xNew, pNew);
   if (code != InsertNotComplete) return code;
   // Insertion in subtree did not completely succeed;
   // try to insert xNew and pNew in the current node:
   if (n < M - 1)
   {  i = NodeSearch(xNew, r->k, n);
      for (j=n; j>i; j--)
      {  r->k[j] = r->k[j-1]; r->p[j+1] = r->p[j];
      }
      r->k[i] = xNew; r->p[i+1] = pNew; ++r->n;
      return Success;
   }
   // Current node is full (n == M - 1) and will be split.
   // Pass item k[h] in the middle of the augmented
   // sequence back via parameter y, so that it
   // can move upward in the tree. Also, pass a pointer
   // to the newly created node back via parameter q:
   if (i == M - 1) {kFinal = xNew; pFinal = pNew;} else
   {  kFinal = r->k[M-2]; pFinal = r->p[M-1];
      for (j=M-2; j>i; j--)
      {  r->k[j] = r->k[j-1]; r->p[j+1] = r->p[j];
      }
      r->k[i] = xNew; r->p[i+1] = pNew;
   }
   int h = (M - 1)/2;
   y = r->k[h];             // y and q are passed on to the
   q = new node;            // next higher level in the tree
   // The values p[0],k[0],p[1],...,k[h-1],p[h] belong to
   // the left of k[h] and are kept in *r:
   r->n = h;
   // p[h+1],k[h+1],p[h+2],...,k[M-2],p[M-1],kFinal,pFinal
   // belong to the right of k[h] and are moved to *q:
   q->n = M - 1 - h;
   for (j=0; j < q->n; j++)
   {  q->p[j] = r->p[j + h + 1];
      q->k[j] = (j < q->n - 1 ? r->k[j + h + 1] : kFinal);
   }
   q->p[q->n] = pFinal;
   return InsertNotComplete;
}

void LsmLevelMemory::pr(const node *r, int nSpace)const
{  if (r)
   {  int i;
      cout << setw(nSpace) << "";

      for (i=0; i < r->n; i++)
         cout << setw(3) << r->k[i] << " ";
      cout << endl;

        for (i=0; i <= r->n; i++) pr(r->p[i], nSpace+8);
    }
}

int counter = 0;

std::vector<long> arr;

std::vector<long> LsmLevelMemory::getNValues(const node *r, int c0TotalNodes, int c0TotalValues, bool copyAllFromC0)const
{

    /* ********************************************** DEBUG ******************************************************
    *************************************************************************************************************/
//    cout << "THE SIZE OF R " << sizeof(r) << endl;
//    cout << "THE COUNTER VALUE " << counter << endl;
//    cout << "THE TOTAL NODES IN C0 IS " << " " << c0TotalNodes  << endl;
//    cout << "THE SELECTED PERCENT OF THE TOTAL NODES IS " << c0TotalNodes / 2 << endl;
//    cout << "SHOULD WE COPY ALL NODES? " << copyAllFromC0 << endl;
    // ***********************************************************************************************************

    int counter_limit;

    if (copyAllFromC0)
    {

        counter_limit = c0TotalValues;

    } else {


        counter_limit = (int) c0TotalNodes / 2;
    }

    if (r)
    {
        int i;
        int j;

        //int pointer_position = 0;

             for (i=0; i < r->n; i++)
              {
                    if (counter < counter_limit)
                    {

                        arr.push_back(r->k[i]);
                        counter += 1;

                        /* ********************************************** DEBUG ******************************************************
                        *************************************************************************************************************/
                        //cout << setw(3) << "adding to array - value " << r->k[i] << endl;
                        //************************************************************************************************************
                    }
              }

//              counter += 1;

            //if (counter < counter_limit)
            //{
                for (j=0; j <= r->n; j++)
                {
                    getNValues(r->p[j],c0TotalNodes, c0TotalValues, copyAllFromC0);
                }
            //}
    }

    /* ********************************************** DEBUG ******************************************************
    *************************************************************************************************************/
//    cout << "ARRAY SIZE - " << arr.size() << endl;
//    cout << "ARRAY VALUES - " << endl;
//
//    // DEBUG - PRINT THE ARRAY'S VALUES
//    const size_t count = arr.size();
//    for (size_t index = 0; index < count; ++index) {
//        cout << index << " = " << arr[index] << endl;
//    }
    //************************************************************************************************************

    return arr;
}

std::vector<long> LsmLevelMemory::memoryLevelCopy(LsmLevelMemory *c0, bool copyAllFromC0)
{
    node *r = root;

    /* ********************************************** DEBUG ******************************************************
    *************************************************************************************************************/
    //cout << "HERE IS THE TOTAL NODES COUNT FROM INSIDE getNValues --------------> " << (*c0).getNodesCount() << endl;
    //(*c0).print();
    //************************************************************************************************************

    int c0TotalNodes = (*c0).getNodesCount();
    int c0TotalValues = (*c0).getValuesCount();

    return getNValues(root, c0TotalNodes, c0TotalValues, copyAllFromC0);
}

int LsmLevelMemory::total_nodes_count = 0;
int LsmLevelMemory::calculateNodesCount(const node *r)const
{
    if (r)
    {
        int i;
        total_nodes_count++;
        for (i=0; i <= r->n; i++) calculateNodesCount(r->p[i]);
    }
    return total_nodes_count;
}

int LsmLevelMemory::getNodesCount()
{
    // get the root node to start
    node *r = root;

    // set the counter to start at 0
    LsmLevelMemory::total_nodes_count = 0;

    return calculateNodesCount(r);
}

int LsmLevelMemory::total_values_count = 0;
int LsmLevelMemory::calculateValuesCount(const node *r)const
{
    if (r)
    {
        int i;
        for (i=0; i < r->n; i++) total_values_count++;
        for (i=0; i <= r->n; i++) calculateValuesCount(r->p[i]);
    }
    return total_values_count;
}


//{  if (r)
//   {  int i;
//      cout << setw(nSpace) << "";
//
//      for (i=0; i < r->n; i++)
//         cout << setw(3) << r->k[i] << " ";
//      cout << endl;
//
//        for (i=0; i <= r->n; i++) pr(r->p[i], nSpace+8);
//    }
//}
//    if (r != NIL)
//    {
//        int i;
//        node_disk Node; ReadNode(r, Node);
//        for (i=0; i < Node.n; i++) disk_total_values_count++;
//        for (i=0; i <= Node.n; i++) disk_calculateValuesCount(Node.p[i]);
//    }
//    return disk_total_values_count;





int LsmLevelMemory::getValuesCount()
{
    // get the root node to start
    node *r = root;

    // set the counter to start at 0
    LsmLevelMemory::total_values_count = 0;

    return calculateValuesCount(r);
}

int LsmLevelMemory::NodeSearch(dtype x, const dtype *a, int n)const
{  int i=0;
   while (i < n && x > a[i]) i++;
   return i;
}

void LsmLevelMemory::ShowSearch(dtype x)const
{  cout << "Search path:\n";
   int i, j, n;
   node *r = root;
   while (r)
   {  n = r->n;
      for (j=0; j<r->n; j++) cout << " " << r->k[j];
      cout << endl;
      i = NodeSearch(x, r->k, n);
      if (i < n && x == r->k[i])
      {  cout << "Key " << x << " found in position " << i
            << " of last displayed node.\n";
         return;
      }
      r = r->p[i];
   }
   cout << "Key " << x << " not found.\n";
}

bool LsmLevelMemory::search_value(dtype x)const
{  cout << "Search path:\n";
   int i, j, n;
   node *r = root;
   while (r)
   {  n = r->n;
      for (j=0; j<r->n; j++) cout << " " << r->k[j];
      cout << endl;
      i = NodeSearch(x, r->k, n);
      if (i < n && x == r->k[i])
      {  cout << "Key " << x << " found in position " << i
            << " of last displayed node.\n";
         return true;
      }
      r = r->p[i];
   }
   cout << "Key " << x << " not found.\n";
   return false;
}

void LsmLevelMemory::DelNode(dtype x)
{  node *root0;
   switch (del(root, x))
   {
   case NotFound:
      //cout << x << " not found.\n";
      break;
   case Underflow:
      root0 = root;
      root = root->p[0];
      delete root0;
      break;
   }
}

status LsmLevelMemory::del(node *r, dtype x)
{  if (r == NULL) return NotFound;
   int i, j, pivot, n = r->n;
   dtype *k = r->k;  // k[i] means r->k[i]
   const int nMin = (M - 1)/2;
   status code;
   node **p = r->p, *pL, *pR;       // p[i] means r->p[i]
   i = NodeSearch(x, k, n);
   if (p[0] == NULL) // *r is a leaf
   {  if (i == n || x < k[i]) return NotFound;
      // x == k[i], and *r is a leaf
      for (j=i+1; j < n; j++)
      {  k[j-1] = k[j]; p[j] = p[j+1];
      }
      return
      --r->n >= (r==root ? 1 : nMin) ? Success : Underflow;
   }
   // *r is an interior node, not a leaf:
   if (i < n && x == k[i])
   {  // x found in an interior node. Go to left child
      // *p[i] and follow a path all the way to a leaf,
      // using rightmost branches:
      node *q = p[i], *q1; int nq;
      for (;;)
      {  nq = q->n; q1 = q->p[nq];
         if (q1 == NULL) break;
         q = q1;
      }
      // Exchange k[i] (= x) with rightmost item in leaf:
      k[i] = q->k[nq-1];
      q->k[nq - 1] = x;
   }
   // Delete x in leaf of subtree with root p[i]:
   code = del(p[i], x);
   if (code != Underflow) return code;
   // There is underflow; borrow, and, if necessary, merge:
   // Too few data items in node *p[i]
   if (i > 0 && p[i-1]->n > nMin) // Borrow from left sibling
   {  pivot = i - 1; // k[pivot] between pL and pR:
      pL = p[pivot]; pR = p[i];
      // Increase contents of *pR, borrowing from *pL:
      pR->p[pR->n + 1] = pR->p[pR->n];
      for (j=pR->n; j>0; j--)
      {  pR->k[j] = pR->k[j-1];
         pR->p[j] = pR->p[j-1];
      }
      pR->n++;
      pR->k[0] = k[pivot];
      pR->p[0] = pL->p[pL->n];
      k[pivot] = pL->k[--pL->n];
      return Success;
   }
   if (i<n && p[i+1]->n > nMin) // Borrow from right sibling
   {  pivot = i; // k[pivot] between pL and pR:
      pL = p[pivot]; pR = p[pivot+1];
      // Increase contents of *pL, borrowing from *pR:
      pL->k[pL->n] = k[pivot];
      pL->p[pL->n + 1] = pR->p[0];
      k[pivot] = pR->k[0];
      pL->n++; pR->n--;
      for (j=0; j < pR->n; j++)
      {  pR->k[j] = pR->k[j+1];
         pR->p[j] = pR->p[j+1];
      }
      pR->p[pR->n] = pR->p[pR->n + 1];
      return Success;
   }
   // Merge; neither borrow left nor borrow right possible.
   pivot = (i == n ? i - 1 : i);
   pL = p[pivot]; pR = p[pivot+1];
   // Add k[pivot] and *pR to *pL:
   pL->k[pL->n] = k[pivot];
   pL->p[pL->n + 1] = pR->p[0];
   for (j=0; j < pR->n; j++)
   {  pL->k[pL->n + 1 + j] = pR->k[j];
      pL->p[pL->n + 2 + j] = pR->p[j+1];
   }
   pL->n += 1 + pR->n;
   delete pR;
   for (j=i+1; j < n; j++)
   {  k[j-1] = k[j]; p[j] = p[j+1];
   }
   return
   --r->n >= (r == root ? 1 : nMin) ? Success : Underflow;
}



//getTotalValuesCount()
//
// {
//
// int total_values = 0;
//   int total_nodes = 0;
//   int i, j, n;
//   node *r = root;
//
//
//
//    //int special_total = 0;
////   if (r)
////   {  int i;
////      cout << setw(5) << "";
////
////        for (i=0; i < r->n; i++) cout << i << endl;
////
////
////      for (i=0; i < r->n; i++)
////
////         cout << setw(3) << r->k[i] << " ";
////      cout << endl;
////      for (i=0; i <= r->n; i++) pr(r->p[i], 5+8);
////   }
//
//  // cout << "SPECIAL TOTAL - " << special_total << endl;
//
//
//
////   while (r)
////   {  n = r->n;
////
////        cout << "DIS IS N -" << n << endl;
////
////
////      total_nodes += 1;
////      for (j=0; j<r->n; j++) total_values += 1; cout << "N Value - " << n << " " << r->k[j];
////
////      while (i < n) i++;
////      //cout << endl;
////
////      r = r->p[i];
////
////      cout << "r after assignment " << r << endl;
////   }
//
//
//
//    cout << "THE TOTAL NODES COUNT IS --> " << my_pr(r, 0) << endl;
//
//
//   //void my_pr
//
//
//
//
//
//
//   cout << "the r->n value " << r->n << endl;
//
//   while (r)
//   {  n = r->n;
//      total_nodes += 1;
//      for (j=0; j<r->n; j++) total_values += 1; cout << "N Value - " << n << " " << r->k[j];
//
//      while (i < n) i++;
//      //cout << endl;
//
//      r = r->p[i];
//
//      //cout << "r after assignment " << r << endl;
//   }
//
//    //std::cout  << "THE VALUES TOTAL AMOUNT IS - " << total_values << endl;
//    //std::cout  << "THE NODES TOTAL AMOUNT IS  - " << total_nodes << endl;
//
//    return total_nodes;
//
//
//
//
//}
