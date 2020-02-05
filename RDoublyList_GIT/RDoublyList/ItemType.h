//*************************************************************************************************
/*									Struct Definition
Author: 
Date: 
Project: Doubly Linked Recursive List
Filename: ItemType.h
Purpose: This file contains the struct ItemType and KeyType definitions for the OrdList Class.
*/

#ifndef ITEM_TYPE
#define ITEM_TYPE

// Named Constants
const int MORE_MEMORY = 10; //1000;	//when put to 10000 I get chkstk.asm error	// Size of the array to allocate more memory

// Type Definitions
typedef int KeyType;			// key used to order the list

typedef double MemArray[MORE_MEMORY];	// filler for record 

struct ItemType
{
	KeyType key;				// The key used to find list elements.
	MemArray moreMem;

}; // End struct ItemType

#endif

// note - increasing the size of the MORE_MEMORY constant will increase the size of each node, thereby allowing you to test the OutofMemoryException easier. 