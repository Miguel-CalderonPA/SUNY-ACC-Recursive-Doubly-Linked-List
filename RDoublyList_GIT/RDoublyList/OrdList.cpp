//Libraries
#include<iostream>
#include"ItemType.h"
#include"nodeStruct.h"
#include"OrdList.h"
using namespace std;

//=========================Constuctors==========================================

//~~~~~~~~~~~~~~~~~~~~~~~~~Constructor~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

OrdListClass::OrdListClass()
{
	// set PDMs to default values
	tail = nullptr;
	count = 0;
	memFull = false;									// flag for if full
} // end constructor

//~~~~~~~~~~~~~~~~~~~~~~~~Copy Constructor Wrapper of sorts~~~~~~~~~~~~~~~~~~~~~~

OrdListClass::OrdListClass(/*in*/const OrdListClass &origList)
{
	if (!origList.IsEmpty())
	{
		tail = Allocate();								// dedicate more memory
		tail->data = origList.tail->data;				// copy tails
		rCopyConstructor(tail, origList.tail->next, origList.tail); // call recursive CC
	} // end if 1
	else												// else empty
	{
		tail = nullptr;									// set default
	} // end else 1
	count = origList.count;								// copy count pdm
	memFull = origList.memFull;							// copy memFull pdm
} // end copy constructor

//~~~~~~~~~~~~~~~~~~~~~~~~~Recursive Copy Constructor Helper

void OrdListClass::rCopyConstructor(/*in*/node* traverse,/*in*/ node* origTraverse,/*in*/node* origtail)
{
	if (origTraverse->data.key == origtail->data.key)	// if traverseerse equals tail
	{
		tail->prev = traverse;							// add to end of list
		traverse->next = tail;							// reset last element to tail
	}// end if 1
	else												// else keys not equal
	{
		traverse->next = Allocate();					// dedicate more memory
		traverse->next->data = origTraverse->data;		//copy data
		traverse->next->prev = traverse;				// rework links
		rCopyConstructor(traverse->next, origTraverse->next, origtail); // call self
	} // end else 1

} // end recursive CC

//===============================Mutators==========================================

//~~~~~~~~~~~~~~~~~~~~~~~~~Insert Wrapper~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void OrdListClass::Insert(/*in*/ItemType newItem)
{

	if (!IsFull())
	{
		if (IsEmpty())
		{
			tail = Allocate();							// dedicate memory to tail
			tail->data = newItem;						// copy data
			count++;
		} // end if 2
		else											// else not empty
		{
			rInsert(tail->next, newItem);				// call r version
		} // end else 1
	} // end if 1
} // end Insert

//~~~~~~~~~~~~~~~~~~~~~~~~~Recursive Insert

void OrdListClass::rInsert(/*in*/ node* trav,/*in*/ ItemType newItem)
{
	if (newItem.key >= tail->data.key)					// if new item is the same or bigger than tail
	{
		if (tail->data.key == newItem.key)				// new item is same as tail
		{
			throw DuplicateKeyException();
		} // end if 2
		else // if new item is bigger
		{
			node* temp = Allocate();					// dedicate new memory
			temp->data = newItem;						// copy data
			temp->prev = tail;							// add to end of list
			temp->next = tail->next;					// rework links
			tail->next->prev = temp;					// set first elements previous to new tail
			tail->next = temp;							// rework last link
			tail = temp;								// new tail
			count++;
		}// end else 1
	} // end if 1
	else if (newItem.key == trav->data.key)				// if keys are the same
	{
		throw DuplicateKeyException();
	} // end else if 1
	else if (newItem.key > trav->data.key)				// if key is greater keep searching
	{
		rInsert(trav->next, newItem);					// call self
	}// end else if 2
	else												// else key is less than you have found the position
	{
		node* temp = Allocate();						// dedicate new memory
		temp->data = newItem;							// copy data

		// rework links & add node
		temp->prev = trav->prev;
		temp->next = trav;
		trav->prev->next = temp;
		trav->prev = temp;

		count++;
	}// end else 2
} // end recursive insert

//~~~~~~~~~~~~~~~~~~~~~~~~~Delete Wrapper~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void OrdListClass::Delete(/*in*/KeyType target)
{
	// if outside bounds of list
	if (!IsEmpty() && (!(target > tail->data.key)))
	{
		rDelete(tail->next, target);					// call r version
	} // end if 1
	else												// else in bounds
	{
		throw KeyNotThereException();
	} // end else 1

} // end delete wrapper

//~~~~~~~~~~~~~~~~~~~~~~~~~Recursive Delete

void OrdListClass::rDelete(/*in*/node* trav,/*in*/KeyType target)
{	// if last recursive call or target is the key
	if ((trav->data.key == tail->data.key) || (target == tail->data.key))
	{
		if (tail->data.key == target)					// if target is key
		{
			if (tail->next == tail)						// if tail is last element remaining
			{
				delete tail;
				tail = nullptr;
				count--;
			} // end if 3
			else										//else tail is the key looking to be deleted
			{
				node* temp = tail->prev;				// set temp to new tail
				tail->next->prev = tail->prev;			// set first element to new tail
				tail->prev->next = tail->next;			// set new tail to first element

				// rid of dangling pointers & delete (I know nullptr is redundant, but it feels correct)
				tail->next = nullptr;
				tail->prev = nullptr;
				delete tail;

				tail = temp;							// finally set new tail
				count--;
			} // end else 1
		}// end if 2
		else											// else not base case
		{
			throw KeyNotThereException();
		} // end else 2
	} // end if 1
	else if (target == trav->data.key) // if found
	{
		node* temp = trav->next;
		// rework links
		trav->next->prev = trav->prev;
		trav->prev->next = trav->next;

		// rid of dangling pointers & delete (I know nullptrs is redundant, but it feels correct)
		trav->next = nullptr;
		trav->prev = nullptr;
		delete trav;			//hits here for stack overflow when testing if mem full
		trav = temp;
		count--;
	} // end else if 1
	else if (target > trav->data.key)					// else if target greater, keep searching
	{
		rDelete(trav->next, target);					// call self
	} // end else if 2
	else												// if less than, not in list
	{
		throw KeyNotThereException();
	}// end else 3
} // end recursive delete

//~~~~~~~~~~~~~~~~~~~~~~~~~Clear Wrapper~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void OrdListClass::Clear()
{
	if (!IsEmpty())
	{
		rClear(tail->next);								// call r version
	} // end if 1
	cout << "List Deleted" << endl;
} // end clear

//~~~~~~~~~~~~~~~~~~~~~~~~~Recursive Clear

void OrdListClass::rClear(/*in*/node* traverse)
{
	if (!IsEmpty())
	{
		node* temp = traverse->next;					// preserve next node
		Delete(traverse->data.key);						// delete this node
		if (!IsEmpty())									// just deducts a function call if list empty
			rClear(temp);								// send next
	} // end if 1
} // end recursive clear


//==========================Observer Predicators===================================

//~~~~~~~~~~~~~~~~~~~~~~~~~IsFull~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool OrdListClass::IsFull() const
{
	return memFull;										// return if memory exception thrown
} // end IsFull

//~~~~~~~~~~~~~~~~~~~~~~~~~IsEmpty~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool OrdListClass::IsEmpty() const
{
	return (tail == nullptr);
} // end IsEmpty

//==========================Observer Summarizers===================================

//~~~~~~~~~~~~~~~~~~~~~~~~~Print Wrapper~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void OrdListClass::Print() const
{
	if (!IsEmpty())
		rPrint(tail);									// call r version
	else
	{
			cout << "I can't find anything to print!" << endl;
	}
} // end print

//~~~~~~~~~~~~~~~~~~~~~~~~~Recursive Print

//recursive print
void OrdListClass::rPrint(/*in*/const node* traverse) const
{
	if (traverse->data.key != tail->next->data.key)		// if not end of list
		rPrint(traverse->prev);							// call self
	cout << (traverse->data.key) << endl;				// un wind print
} // end recursive Print

//~~~~~~~~~~~~~~~~~~~~~~~~~Reverse Print Wrapper~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void OrdListClass::PrintReverse() const
{
	if (!IsEmpty())
		rPrintRev(tail->next);							// call r version
	else
	{
		cout << "I can't find anything to reverse print! " << endl;
	} // end else 
		
} // end PrintReverse

//~~~~~~~~~~~~~~~~~~~~~~~~~Recursive Reverse Print

void OrdListClass::rPrintRev(/*in*/const node* traverse) const
{
	if (traverse->data.key != tail->data.key)			// if not end of list
		rPrintRev(traverse->next);						// call self
	cout << (traverse->data.key) << endl;				// unwind rprint
} // end recursive reverse print

//==========================Observer Accessor======================================

//~~~~~~~~~~~~~~~~~~~~~~~~~Retrieve Wrapper~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ItemType OrdListClass::Retrieve(/*in*/KeyType target) const
{
	if (IsEmpty())
		throw KeyNotThereException();
	else												// else not empty
	{
		ItemType retItem;								// define item
		rRetrieve(tail->next, retItem, target);			// call r version
		return retItem;									// send item
	} // end else 1

} // end Retrieve

//~~~~~~~~~~~~~~~~~~~~~~~~~Recursive Retrieve

void OrdListClass::rRetrieve(/*in*/ node* trav,/*in & out*/ ItemType& retItem,/*in*/ KeyType target) const
{

	if (trav->data.key == tail->data.key)				// if tail == item 
	{
		if (trav->data.key != target)					// if traverse is not data
		{
			throw KeyNotThereException();
		} // end if 2
		else											// else traverse is data
		{
			retItem = trav->data;
		} // end else 1
	} // end if 1
	else												// if not end of list
	{
		if (trav->data.key != target)					// if traverse is not target
		{
			rRetrieve(trav->next, retItem, target);		// keep searching
		} // end if 2
		else											// if traverse is target
		{
			retItem = trav->data;						// set traverse item to retItem
		} // end else 2
	} // end if 1
}

//~~~~~~~~~~~~~~~~~~~~~~~~~GetLength~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int OrdListClass::GetLength()
{
	return count;
} // end GetLength

//==========================Overload Operator======================================

//~~~~~~~~~~~~~~~~~~~~~~~~~Operator Assignment~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void OrdListClass::operator=(/*in*/const OrdListClass &orig)
{
	Clear();												
	if (!orig.IsEmpty())									
	{				
		tail = Allocate();									// dedicate more memory
		tail->data = orig.tail->data;						// copy data
		rCopyConstructor(tail, orig.tail->next, orig.tail);	// call recursive CC
		// copy PDMs
		count = orig.count;									
		memFull = orig.memFull;
	} // end if 1
	else													// if empty
	{// set default PDMs
		tail = nullptr;
		count = 0;
		memFull = false;
	} // end else 1
	
}// end Operator =

//~~~~~~~~~~~~~~~~~~~~~~~~~Operator Union~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

OrdListClass OrdListClass::operator+(/*in*/const OrdListClass &otherList) const
{
	OrdListClass unionList(otherList);						// copy other list
	node* traverse;											// traverse this*
	node* traverseUnion;									// traverse new list
	int ctTraverse;
	bool lastLoop = false;
															// if one of the list is empty, just assign the other
	if (IsEmpty())
	{
		unionList = otherList;
	} // end if 1
	else if (otherList.IsEmpty())
	{
		unionList = *this;
	} // end else if 1
	else if ((count == 1) || (unionList.count == 1))		// if either one has one element		
	{
		ctTraverse = 0;
		if (count == 1)
		{
			try
			{
				unionList.Insert(tail->data);				// try and if fail, its already there
			} // end try
			catch(DuplicateKeyException)
			{
				// do nothing throw DuplicateKeyException
			} // end catch
		} // end if 2
		else if (unionList.count == 1)				
		{
			if (tail->data.key > unionList.tail->data.key)	// if this* tail is bigger 
			{												// set new tail to this* tail
				node* temp = unionList.Allocate();			// dedicate new memory
				temp->data = tail->data;					// copy data
				temp->prev = unionList.tail;				// add to end of list
				temp->next = unionList.tail->next;			// rework links
				unionList.tail->next->prev = temp;			// set first elements previous to new tail
				unionList.tail->next = temp;				// rework last link
				unionList.tail = temp;						// new tail
				unionList.count++;
			}// end if 3

			traverse = tail->next;							// set to this* head
			traverseUnion = unionList.tail->next;			// set to new list head
			while (count != ctTraverse)						// while there are elements to add
			{
				if (traverse->data.key < traverseUnion->data.key)
				{// add new node
					node* temp = unionList.Allocate();		// dedicate new memory
					temp->data.key = traverse->data.key;	// copy data

					// rework links
					temp->next = traverseUnion;
					temp->prev = traverseUnion->prev;
					traverseUnion->prev->next = temp;
					traverseUnion->prev = temp;
					traverse = traverse->next;				// set next
					unionList.count++;
				} // end if 4
				else if (traverse->data.key == traverseUnion->data.key) // same its already in the list
				{
					traverse = traverse->next;				// set next
					//throw DuplicateKeyException();
					traverseUnion = traverseUnion->next;	// set new list next
				} // end else if 4	
				else
					traverseUnion = traverseUnion->next;	//set new list next

				ctTraverse++;
			} // end while
		} // end else if 3
	}// end else if 2
	else													// if more than one element in each
	{
		if (tail->data.key > otherList.tail->data.key)
		{// new node
			unionList.tail = unionList.Allocate();			// dedicate new memory
			unionList.tail->data = tail->data;				// copy data
		}// end if 5
		traverse = tail->next;								// traverse this*
		traverseUnion = unionList.tail->next;
		while ((tail->data.key != traverse->data.key) || lastLoop)	// while still traversing this* list or if on last loop
		{
			if (traverse->data.key < traverseUnion->data.key)
			{// add new node
				node* temp = unionList.Allocate();			//dedicate new memory
				temp->data.key = traverse->data.key;		// copy data

				// rework links
				temp->next = traverseUnion;
				temp->prev = traverseUnion->prev;
				traverseUnion->prev->next = temp;
				traverseUnion->prev = temp;

				if (!lastLoop)								// if not last loop
					traverse = traverse->next;				// keep traversing this*

				unionList.count++;
			}// end if 6
			else if (traverse->data.key == traverseUnion->data.key)	// if they equal dont add
			{
				if (!lastLoop)								// if not last loop
					traverse = traverse->next;				// keep traversing this*
				//throw DuplicateKeyException();
				traverseUnion = traverseUnion->next;		// keep traversing union
			} // end else if 5
			else
				traverseUnion = traverseUnion->next;		// keep traversing union

			if ((traverse->data.key == tail->data.key) && lastLoop == false) // if one more pass
				lastLoop = true;							// then last loop

			else if ((traverse->data.key == tail->data.key) && lastLoop == true) // if last pass
				lastLoop = false;							// then end
		}// end while
	}// end else 1
	///* TESTING PURPOSES
	cout << endl << "Other List " << endl;
	otherList.Print();
	cout << endl << "This List Print " << endl;
	Print();
	cout << endl << "Unioned List " << endl;
	unionList.Print();
	cout << endl;
	 //*/
	return unionList;
}// end operator +

//~~~~~~~~~~~~~~~~~~~~~~~~~Operator Difference~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

OrdListClass OrdListClass::operator-(/*in*/const OrdListClass &otherList) const
{

//	OrdListClass otherListCopy = otherList;					//assign other list
	OrdListClass differenceList(*this);						//copy this* list
	node* traverseOther;									// traverse other list
	node* traverseInter;									// traverse difference list
	int ctTraverse;
	bool lastLoop = false;
	if (IsEmpty() || otherList.IsEmpty())					// if either are empty
	{														// Assign this* to difference
		differenceList = *this;
	} // end if 1
	else if ((differenceList.count == 1) || (otherList.count == 1))	// if one element in either list
	{
		ctTraverse = 0;
		if (differenceList.count == 1)						// if one element in new list
		{
			traverseOther = otherList.tail->next;
			// while  new list data is not equal to other && while they're still nodes to traverse
			while ((differenceList.tail->data.key != traverseOther->data.key) && (ctTraverse != otherList.count))
			{
				traverseOther = traverseOther->next;		// traverse other
				ctTraverse++;
			} // end while

			if (differenceList.tail->data.key == traverseOther->data.key)	// if the same tails call delete 
			{
				differenceList.Delete(differenceList.tail->data.key);
			}// end if 3
		} // end if 2
		else
		{
			traverseInter = differenceList.tail->next;		// traverse new
			// while new list is not the same as other list && they're still nodes to traverse
			while ((traverseInter->data.key != otherList.tail->data.key) && (ctTraverse != differenceList.count))
			{
				traverseInter = traverseInter->next;		// traverse new
				ctTraverse++;
			} // end while

			if (traverseInter->data.key == otherList.tail->data.key) // if node equals other list tail
			{
				if (traverseInter->data.key == differenceList.tail->data.key)// if node equals its own tail
				{
					differenceList.Delete(traverseInter->data.key);	// call delete
				} // end if 5
				else
				{
					node* temp = traverseInter;

					// rework links
					traverseInter->next->prev = traverseInter->prev;
					traverseInter->prev->next = traverseInter->next;

					// being safe
					traverseInter->next = nullptr;
					traverseInter->prev = nullptr;
					delete traverseInter;
					traverseInter = temp;					// preserve traverse
					differenceList.count--;
				}// end else 2
			} // end if 4
		}// end else 1
	} // end else if 1
	else
	{
		traverseOther = otherList.tail->next;				// set to other head
		traverseInter = differenceList.tail->next;			// set to new list head
		while (((otherList.tail->data.key != traverseOther->data.key) || lastLoop) && (!differenceList.IsEmpty()))
		{

			if (traverseOther->data.key == traverseInter->data.key) // if delete
			{
				if (traverseOther->data.key == differenceList.tail->data.key) // if tail is delete target
				{
					if (differenceList.tail->next->data.key == differenceList.tail->data.key) // if last element in list
					{
						differenceList.Delete(traverseInter->data.key);	// if tail use delete
					} // end if 8
					else
					{
						differenceList.Delete(traverseInter->data.key);	//if tail use delete
					} // end else 3
				} // end if 7
				else
				{
					node* temp = traverseInter->next;		//preserve traverse
					
					// rework links
					traverseInter->next->prev = traverseInter->prev;
					traverseInter->prev->next = traverseInter->next;

					// be safe
					traverseInter->next = nullptr;
					traverseInter->prev = nullptr;
					delete traverseInter;
					traverseInter = temp;					// preserve traverse
					differenceList.count--;

				} // end else 4
				if (!lastLoop)								// if last loop
					traverseOther = traverseOther->next;	//traverse other

			} // end if 6
			else if (traverseOther->data.key < traverseInter->data.key) // if other less than new
			{
				if (!lastLoop)								// if last loop
					traverseOther = traverseOther->next;	// traverse other

			} // end else if 3
			else
				traverseInter = traverseInter->next;		// else traverse new list

			// if other is same as other last pass
			if ((traverseOther->data.key == otherList.tail->data.key) && lastLoop == false)
				lastLoop = true;

			// if other is same as other, end loop
			else if ((traverseOther->data.key == otherList.tail->data.key) && lastLoop == true)
				lastLoop = false;

		}
		
	} // end else 3
	///* TESTING PURPOSES
	cout << endl << "Other List " << endl;
	otherList.Print();
	cout << endl << "This List Print " << endl;
	Print();
	cout << endl << "Difference List " << endl;
	differenceList.Print();
	cout << endl;
	//*/
	return differenceList;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~Allocate~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

node* OrdListClass::Allocate()
{
	try
	{
		node* temp = new node; // dedicate new memory

		//point to self
		temp->next = temp; 
		temp->prev = temp;
		memFull = false;
		return (temp); // return new memory
	}// end try
	catch (bad_alloc)
	{
		memFull = true;									// if bad allocation, set full and throw exception
		throw OutOfMemoryException();
	} // end catch
} // end Allocate

  //~~~~~~~~~~~~~~~~~~~~~~~~~Deconstructor~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

OrdListClass::~OrdListClass()
{
	Clear(); // delete the entire list
}


//*****************************END*************************************************
