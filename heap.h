

/* Prevent multiple inclusions                                      */
#ifndef Heap
#define Heap

/* Include Header File for the definition of the Item type        */
#include "defs.h"

void HeapInit( unsigned size);
void InsertHeap(Item i );
void FixUp(Item *queue, int Idx);
void FixDown (Item *queue, int Idx, int N);
Item *EmptyHeap();
Item RemoveHeap();


/* End if: Protect multiple inclusions                              */
#endif
