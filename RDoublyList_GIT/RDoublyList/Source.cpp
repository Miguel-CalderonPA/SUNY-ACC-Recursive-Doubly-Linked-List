/*
Author: Miguel Calderon

Date: 4/17/19

File Name: CalderonRDoublyList

Purpose: The list is implemented with a  doubly linked structure, and uses recursion to access and modify elements in the list.
		Also contains overloaded operators for assignement, merging and subtracting lists

Inputs: What the user puts in the struct, this can be edited later

Outputs: Can print out the list, forwards or backwards, for now just to the console

Assumptions: The user will be handling the exceptions , also pancakes are good

Error Checking: Throws Exceptions for Dupe key, no memory, or not key not there
*/

//Libraries
#include<iostream>
#include<string>
#include"OrdList.h"
#include "ItemType.h"

using namespace std;

int main()
{
	// variables
	OrdListClass list1, list3, list4; // list 2 is created later as a copy constructor
	cout << "OrdListClass Instantiated" << endl;
	
	// Create Test Items and store data
	ItemType item1, item2, item3, item4, item5, item6, item7, item8, item9, item10, item11, item12, item13, item14, item15;
	ItemType testItem;
	item1.key = 123;
	item2.key = 456;
	item3.key = 789;
//	for (short i = 0; i < MORE_MEMORY; i++)
//	{
//		item3.moreMem[i] = i * i;
//	}
	item4.key = 111;
	item5.key = 222;
	item6.key = 333;
	item7.key = 444;
	item8.key = 555;
	item9.key = 777;
	item10.key = 999;

	//~~~~~~~~~~~~~~~Test IsEmpty~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	cout << "Test IsEmpty()" << endl;

	if (list1.IsEmpty())
		cout << "Empty" << endl;
	else
		cout << "Not empty" << endl;

	cout << "Empty: FINE" << endl;


	//~~~~~~~~~~~~~~~Test Insert~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	cout<< endl << "Test Insert" << endl;

	list1.Insert(item4);
	list1.Insert(item3);
	list1.Insert(item2);
	list1.Insert(item5);
	list1.Insert(item1);
	try
	{
		list1.Insert(item1); 
	} // end try
	catch (DuplicateKeyException)
	{
		cout << "Item 1 already in the list test " << endl;
	} // end catch

		cout << "Insert FINE" << endl << endl;
	//~~~~~~~~~~~Test Prints~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	cout << endl << "Test Print" << endl;
	list1.Print();
	cout << endl << "Length: " << list1.GetLength() << endl;
	cout << endl << "Test Reverse Print" << endl;
	list1.PrintReverse();
	cout << endl;

	cout << "Print FINE" << endl << endl;
	cout << "Reverse Print FINE" << endl << endl;

	//~~~~~~~~~~~~~~~Test IsEmpty~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	cout << "Test IsEmpty()" << endl;

	if (list1.IsEmpty())
		cout << "Empty" << endl;
	else
		cout << "Not Empty" << endl;
	cout << endl;

	//~~~~~~~~~~~~~~~Delete~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	cout << "Test Delete()" << endl;

	list1.Delete(item1.key);
	list1.Delete(item4.key);
	try
	{
		list1.Delete(999);
	} // end try
	catch (KeyNotThereException)
	{
		cout << "999 key not there test" << endl;
	} // end catch
	cout << "Delete FINE" << endl << endl;

	//~~~~~~~~~~~Test Prints~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	cout << endl << "Test Print" << endl;
	list1.Print();
	cout << endl << "Length: " << list1.GetLength() << endl;
	cout << endl << "Test Reverse Print" << endl;
	list1.PrintReverse();
	cout << endl;

	//~~~~~~~~~~~~~~~Test Retrieve~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	cout << endl << "Test Retrieve" << endl;
	testItem = list1.Retrieve(item3.key);
	for (short i = 0; i < MORE_MEMORY; i++)
	{
		cout << testItem.key << " MoreMemLocation " << i << ':' << testItem.moreMem[i] << endl;
	}
	// test outputting MoreMemory Value in node
	cout << endl;
	testItem = list1.Retrieve(item5.key);
	cout << testItem.key << " MoreMemLocation " << testItem.moreMem[1] << endl << endl;
	testItem = list1.Retrieve(item2.key);
	cout << testItem.key << " MoreMemLocation " << testItem.moreMem[1] << endl;
	/* extra tests
	testItem = list1.Retrieve(789);
	cout << testItem.key << " MoreMemLocation "  << testItem.moreMem[i] << endl;;
	testItem = list1.Retrieve(789);
	cout << testItem.key << " MoreMemLocation " << testItem.moreMem[i] << endl;
	*/

	try
	{
		testItem = list1.Retrieve(item4.key);
	}
	catch (KeyNotThereException)
	{
		cout << "Item 4 not there test" << endl;
	}

	cout << "Retrieve FINE" << endl << endl;

	//~~~~~~~~~~~Test Clear~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	list1.Clear();
	cout << "Clear FINE" << endl << endl;

	//~~~~~~~~~~~Test Prints~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	cout << endl << "Test Print these should be empty" << endl;
	list1.Print();
	cout << endl << "Length: " << list1.GetLength() << endl;
	cout << endl << "Test Reverse Print" << endl;
	list1.PrintReverse();
	cout << endl;

	//***************************FIRST MAJOR TESTS DONE***********************

	//~~~~~~~~~~~~~TEST Copy Constructor~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	// Fill List 1
	list1.Insert(item1);
	list1.Insert(item2);
	list1.Insert(item3);
	list1.Insert(item4);
	list1.Insert(item5);

	cout << endl << "Test Copy Constructor" << endl;
	OrdListClass list2(list1);

	cout << "Copy Constructor FINE" << endl << endl;

	//~~~~~~~~~~~Test Prints for Copy Constuctor~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	cout << endl << "Test Prints for LIST 1" << endl;
	list1.Print();
	cout << endl << "Length: " << list1.GetLength() << endl;
	cout << endl << "Test Reverse Print" << endl;
	list1.PrintReverse();
	cout << endl;

	cout << endl << "Test Prints for LIST 2" << endl;
	list2.Print();
	//cout << endl << "Length: " << list2.GetLength() << endl;
	cout << endl << "Test Reverse Print" << endl;
	list2.PrintReverse();
	cout << endl;

	list1.Clear();
	list2.Clear();

	/*~~~~~~~~~~~Test Special Cases~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// have to comment out all references to list 2 in previous part 
	cout << endl << "Test Copy Constructor with Special Case" << endl;
	list1.Insert(item1);
	list1.Insert(item2);
	OrdListClass list2(list1); 
	cout << endl << "Test Prints for LIST 1 with Special Case" << endl;
	list1.Print();
	cout << endl << "Length: " << list1.GetLength() << endl;
	cout << endl << "Test Reverse Print" << endl;
	list1.PrintReverse();
	cout << endl;

	cout << endl << "Test Prints for LIST 2 with Special Case" << endl;
	list2.Print();
	cout << endl << "Length: " << list2.GetLength() << endl;
	cout << endl << "Test Reverse Print" << endl;
	list2.PrintReverse();
	cout << endl;

	list1.Clear();
	list2.Clear();
	*/
	//~~~~~~~~~~~~~Test Operator=~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	cout << "TEST OPERATORS" << endl << endl;

	cout << endl << "Test Operator= list3=list2" << endl;
	list3 = list2;

	//~~~~~~~~~~~Test Prints for Operator =~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	cout << endl << "Test Prints for LIST 2" << endl;
	list2.Print();
	cout << endl << "Length: " << list2.GetLength() << endl;
	cout << endl << "Test Reverse Print" << endl;
	list2.PrintReverse();
	cout << endl;

	cout << endl << "Test Prints for LIST 3" << endl;
	list3.Print();
	cout << endl << "Length: " << list3.GetLength() << endl;
	cout << endl << "Test Reverse Print" << endl;
	list3.PrintReverse();
	cout << endl;

	// Clear Lists
	list4.Clear();
	list3.Clear();
	list2.Clear();
	cout << endl << "Empty List 2,3,4" << endl;

	cout << "Operator = FINE" << endl << endl;

	//~~~~~~~~~~~Test Operator +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	cout << endl << "TEST Operator +" << endl;

	// Fill List2
	//*
	list2.Insert(item2);
	list2.Insert(item4);
	list2.Insert(item5);
	list2.Insert(item7);
	list2.Insert(item10);
	//*/

	// Fill List3
	///*
	list3.Insert(item2);
	list3.Insert(item4);
	list3.Insert(item6);
	list3.Insert(item8);
	list3.Insert(item10);
	//*/
	// Fill List4 
	///*
	list4.Insert(item1);
	list4.Insert(item3);
	list4.Insert(item5);
	list4.Insert(item7);
	list4.Insert(item9);
	//*/
	
	list4 = list2 + list3; // Operator + & =
	cout << endl << "List4 Length: " << list4.GetLength() << endl;
	cout << "List3 Length: " << list3.GetLength() << endl;
	cout << "list2 Length: " << list2.GetLength() << endl;

	/*~~~~~~~~~~~Test Prints for Operator+ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	// Operator + and - have built in Prints in them
	cout << endl << "Test  Prints for LIST 2" << endl;
	list2.Print();
	cout << endl << "Length: " << list2.GetLength() << endl;
	cout << endl << "Test Reverse Print" << endl;
	list2.PrintReverse();
	cout << endl;

	cout << endl << "Test  Prints for LIST 3" << endl;
	list3.Print();
	cout << endl << "Length: " << list3.GetLength() << endl;
	cout << endl << "Test Reverse Print" << endl;
	list3.PrintReverse();
	cout << endl;

	cout << endl << "Test  Prints for LIST 4" << endl;
	list4.Print();
	cout << endl << "Length: " << list3.GetLength() << endl;
	cout << endl << "Test Reverse Print" << endl;
	list4.PrintReverse();
	cout << endl;

	//*/
	cout << endl;
	list4.Clear();
	list3.Clear();
	list2.Clear();

	/*~~~~~~~~~~~Test Special Cases~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	// Testing for 1v0, 1v1, 1v3, 2v3, 3v3 elements Either
	//*
	//list2.Insert(item8);
	//list2.Insert(item5);
	//list2.Insert(item6);
	//list2.Insert(item7);
	//list3.Insert(item7);
	//list3.Insert(item5);
	//list3.Insert(item6);
	//list3.Insert(item8);
	//*/

	cout << endl << "Test either Empty list or Special case for OP+" << endl << endl;

	list4 = list3 + list2; // Operator = & +
	cout << endl << "List4 Length: " << list4.GetLength() << endl;
	cout << "List3 Length: " << list3.GetLength() << endl;
	cout << "list2 Length: " << list2.GetLength() << endl;

	
	// Clear Lists
	//cout << endl;
	
	list4.Clear();
	list3.Clear();
	list2.Clear();
	
	cout << "Operator + FINE" << endl << endl;

	//~~~~~~~~~~~Test Operator -~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	cout << endl << "TEST Operator -" << endl << endl;

	// Fill Test Values for List2
	///*
	list2.Insert(item2);
	list2.Insert(item3);
	list2.Insert(item6);
	list2.Insert(item8);
	list2.Insert(item10);
	//*/

	// Fill Test Values for List3
	list3.Insert(item2);
	list3.Insert(item3);
	list3.Insert(item6);
	list3.Insert(item10);

	// Extra Test Exception
	try 
	{
		list3.Insert(item9);
	} // end try
	catch (DuplicateKeyException)
	{
		cout << "Oops key Item 9 is already there" << endl;
	} // end

	// Fill List4 
	//*
	list4.Insert(item2);
	list4.Insert(item3);
	list4.Insert(item5);
	list4.Insert(item7);
	list4.Insert(item9);
	//*/

	list4 = list2 - list3; // Operator = & -
	// Length of Lists
	cout << endl << "List4 Length: " << list4.GetLength() << endl;
	cout << "List3 Length: " << list3.GetLength() << endl;
	cout << "list2 Length: " << list2.GetLength() << endl;
	cout << endl;

	/*~~~~~~~~~~~Test Prints for Operator- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Operator + and - have built in Prints in them
	cout << endl << "LIST 2 after Op+" << endl;
	list2.Print();
	cout << endl << "Length: " << list2.GetLength() << endl;
	cout << endl << "Test Reverse Print" << endl;
	list2.PrintReverse();
	cout << endl;

	cout << endl << "LIST 3 after Op+" << endl;
	list3.Print();
	cout << endl << "Length: " << list3.GetLength() << endl;
	cout << endl << "Test Reverse Print" << endl;
	list3.PrintReverse();
	cout << endl;

	cout << endl << "LIST 4 after Op+" << endl;
	list4.Print();
	cout << endl << "Length: " << list3.GetLength() << endl;
	cout << endl << "Test Reverse Print" << endl;
	list4.PrintReverse();
	cout << endl;

	//*/
	cout << endl;
	// Clears Lists
	list4.Clear();
	list3.Clear();
	list2.Clear();

	/*~~~~~~~~~~~Test Special Cases~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	// Testing for 1v0, 1v1, 1v3, 2v3, 3v3 elements Either
	//*
	//list2.Insert(item8);
	//list2.Insert(item5);
	//list2.Insert(item6);
	//list2.Insert(item7);
	//list3.Insert(item7);
	//list3.Insert(item5);
	//list3.Insert(item6);
	//list3.Insert(item8);

	/*cout << endl;
	// Clears Lists
	list4.Clear();
	list3.Clear();
	list2.Clear();
	//*/

	cout << endl << "Test either Empty Lists or Special Cases for Op+" << endl;
	list4 = list2 - list3; // Operator = & -
	cout << endl << "List4 Length: " << list4.GetLength() << endl;
	cout << "List3 Length: " << list3.GetLength() << endl;
	cout << "list2 Length: " << list2.GetLength() << endl;

	/*~~~~~~~~~~~Test Prints for Operator -~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	cout << endl << "LIST 2 after Op-" << endl;
	list2.Print();
	cout << endl << "Length: " << list2.GetLength() << endl;
	cout << endl << "Test Reverse Print" << endl;
	list2.PrintReverse();
	cout << endl;

	cout << endl << "LIST 3 after Op-" << endl;
	list3.Print();
	cout << endl << "Length: " << list3.GetLength() << endl;
	cout << endl << "Test Reverse Print" << endl;
	list3.PrintReverse();
	cout << endl;

	cout << endl << "LIST 4 after Op-" << endl;
	list4.Print();
	cout << endl << "Length: " << list3.GetLength() << endl;
	cout << endl << "Test Reverse Print" << endl;
	list4.PrintReverse();
	cout << endl;

	//*/
	cout << endl;
	cout << "Operator - FINE" << endl << endl;

	/*********************END SECOND MAJOR TESTS******************************/

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~Test MAX Memory Exception~~~~~~~~~~~~~~~~~~~~
	int size = 1000; // test size adding 5 more 0's will fill memory, but adding even 1 more 0 causes stack overflow error
	KeyType uno = 1;	// if I put more mem to 10000 I get chkstk.asm error, that only goes away in new workspace
	OrdListClass list5;
	item15.key = 1;
	//for (short i = 0; i < MORE_MEMORY; i++)
	//{
	//	item15.moreMem[i] = i * i* i; // fill random memory
	//}
	try
	{
		for (int i = 0; i < size; i++)
		{
			item15.key = item15.key + uno; // add to self
			try
			{
				list5.Insert(item15);
			} // end try
			catch (DuplicateKeyException)
			{
				cout << "Dupe key" << endl;
			} // end catch
		} // end for
	}
	catch(OutOfMemoryException)
	{
		cout << "OOF out of Memory" << endl;
	}



	cout << "Praise Be" << endl;
	system("pause");
	return 0;
}