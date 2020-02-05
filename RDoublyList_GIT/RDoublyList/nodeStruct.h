#pragma once
#include"ItemType.h"
struct node
{
	ItemType data;
	node* prev;
	node* next;
};