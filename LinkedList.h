/*
 *  File name: LinkedList.h
 *
 *  Author: 2013 Fall Semester AED Team
 *
 *  Release date: 2013/10/04
 *
 *  Description: Header file for an Abstract Implementation of a
 *               Linked List
 *
 *  Data type list:
 *    Linked list node: LinkedList
 *
 *  Function list:
 *    A) Initialization & Termination
 *        initLinkedList
 *        freeLinkedList
 *
 *    B) Properties
 *        lengthLinkedList
 *
 *    C) Navigation
 *        getNextNodeLinkedList
 *
 *    D) Lookup
 *        getItemLinkedList
 *
 *    E) Insertion
 *        insertUnsortedLinkedList
 *
 *    F) Sorted linked lists
 *       insertSortedLinkedList
 *
 *  Dependencies:
 *    stdio.h
 *    stdlib.h
 *    defs.h
 *
 *  Version: 1.0
 *
 *  Change log: N/A
 *
 */


/* Prevent multiple inclusions                                      */
#ifndef LinkedListHeader
#define LinkedListHeader



/* Include Header File for the definition of the Item type        */
#include "defs.h"


typedef struct _LinkedList
{
	Item this;
	struct _LinkedList *next;
	
}LinkedList;


/*
 *  Function:
 *    freeLinkedList
 *
 *  Description:
 *    Frees the memory allocated to a linked list.
 *
 *  Arguments:
 *    Pointer to the first element of a linked list:
 *      (LinkedList *) first
 *    Function to free the memory allocated to the items:
 *      void freeItem(Item)
 *
 *  Return value:
 *    None
 */
void freeLinkedList(LinkedList * first, void (* freeItemFnt)(Item));





/*
 *  Function:
 *    getNextNodeLinkedList
 *
 *  Description:
 *    Returns the next node of a linked list.
 *
 *  Arguments:
 *    Pointer to the current linked list node:
 *        (LinkedList *) node
 *
 *  Return value:
 *    Returns the pointer to the next node of a linked list. NULL
 *   is returned in case the current node is empty or there is no
 *   node following the current node.
 */
LinkedList * getNextNodeLinkedList(LinkedList * node);



/*
 *  Function:
 *    getItemLinkedList
 *
 *  Description:
 *    Gets the item of a linked list node.
 *
 *  Arguments:
 *    Pointer to a linked list node:
 *        (LinkedList *) node
 *
 *  Return value:
 *    Returns the pointer to the item of a linked list node. NULL
 *   is returned if the node is NULL (or if the item is NULL).
 */
Item getItemLinkedList(LinkedList * node);



/*
 *  Function:
 *    insertUnsortedLinkedList
 *
 *  Description:
 *    Creates a new linked list node.
 *
 *  Arguments:
 *    Item to associate to the new node:
 *      Item this
 *    Pointer to the next node:
 *      (LinkedList *) next
 *
 *  Return value:
 *    Returns the pointer to the new node.
 */
LinkedList * insertLinkedList(LinkedList * next, Item this);




/* End if: Protect multiple inclusions                              */
#endif
