/*
Jeremy Lafond
jalafond
pa5
*/
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

//struct
typedef struct NodeObj
{
	int data;
	struct NodeObj* prev;
	struct NodeObj* next;
}NodeObj;

typedef NodeObj* Node;

typedef struct ListObj
{
	Node front;
	Node back;
	Node cursor;
	int index;
	int length;
}ListObj;

//constructors/deconstructors
Node newNode(int data)
{
	Node D = malloc(sizeof(NodeObj));
	D->prev = NULL;
	D->next = NULL;
	D->data = data;
	return D;
}

void freeNode(Node* pN)
{
	if(pN != NULL && *pN !=NULL)
	{
		free(*pN);
		*pN = NULL;
	}
}

List newList(void)
{
	List L;
	L = malloc(sizeof(ListObj));
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->index = -1;
	L->length = 0;
	return L;
}

void freeList(List* pL)
{
	if(pL!=NULL && *pL!=NULL)
	{
		Node temp = (*pL)->front;	
		while(temp!=NULL)
		{
			Node tempCursor = temp;
			temp = temp->next;
			free(tempCursor);
		}
		free(*pL);
		*pL = NULL;
	}
}

//accessors----------------------------------------------------------------------------
int length(List L)
{
	if(L == NULL)
	{
		fprintf(stderr, "List error: length was called on an undefined list.\n");
		exit(1);
	}
	//else
	return L->length;
}

//returns index of cursor if defined 
//otherwise returns -1
int index(List L)
{
	if(L == NULL)
	{
		fprintf(stderr, "List error: index was called on while index was not defined.\n");
		exit(1);
	}
	if(L->length == 0)
	{
		return -1;
	}
	//else
	return L->index;
}

//returns front element(precond: length() > 0)
int front(List L)
{
	if(L == NULL)
	{
		fprintf(stderr, "List error: front was called on while index was not defined.\n");
		exit(1);
	}
	if(L->length == 0)
	{
		fprintf(stderr, "List error: front was called on an empty list or front is not defined.\n");
		exit(1);
	}
	return L->front->data;
}

//returns back element(precond: length() > 0)
int back(List L)
{
	if(L == NULL)
	{
		fprintf(stderr, "List error: back was called on while index was not defined.\n");
		exit(1);
	}
	if(length(L) == 0)
	{
		fprintf(stderr, "List error: back was called on an empty list or front is not defined.\n");
		exit(1);
	}
	return L->back->data;
}

//returns cursor element so long as length() > 0 and index() > 0
int get(List L)
{
	if(L->length == 0)
	{
		fprintf(stderr, "List error: get() was called on an empty list.\n");
		exit(1);
	}
	if(L->index == -1)
	{
		fprintf(stderr, "List error: get() was called while cursor was not defined.\n");
		exit(1);
	}
	if(L == NULL)
	{
		fprintf(stderr, "List error: get() was called on an undefined list.\n");
		exit(1);
	}
	return L->cursor->data;
}

//return true if List A and List B are the same sequence
//ignore cursor
int equals(List A, List B)
{
	int boolv = 1;
	if(A == NULL || B == NULL)
	{
		fprintf(stderr, "List error: equals() was called on an undefined list.\n");
		exit(1);
	}
	if(A->length == B-> length)
	{
		Node ls = A->front;
		Node rs = B->front;
		while(boolv && ls != NULL)
		{		
			boolv = (ls->data == rs->data);
			ls = ls->next;
			rs = rs->next;
		}
		return boolv;
	}
	else
	{
		return 0;
	}
}

//manipulators-------------------------------------------------------------------------

//resets list to original state
void clear(List L)
{
	if(L == NULL)
	{
		fprintf(stderr, "List error: clear() was called on an undefined list.\n");
		exit(1);
	}
	else
	{
		Node temp = L->front;
		while(temp != NULL)
		{
			Node tempCursor = temp;
			temp = temp->next;
			free(tempCursor);
		}
		L->cursor = L->front = L->back = NULL;
		L->index = -1;
		L->length = 0;
	}
}

// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L)
{
	if(L == NULL)
	{
		fprintf(stderr, "List error: moveFront() was called on an undefined list.\n");
		exit(1);
	}
	if(L->length > 0)
	{
		L->cursor = L->front;
		L->index = 0;
	}
	return;
}

// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveBack(List L)
{
	if(L == NULL)
	{
		fprintf(stderr, "List error: moveBack() was called on an undefined list.\n");
		exit(1);
	}
	if(L->length > 0)
	{
		L->cursor = L->back;
		L->index = L->length - 1;
	}
	return;
}

// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L)
{
	if(L == NULL)
	{
		fprintf(stderr, "List error: movePrev() was called on an undefined list.\n");
		exit(1);
	}
	if(L->cursor == L->front)
	{
		L->cursor = NULL;
		L->index = -1;
		return;
	}
	if(L->cursor == NULL)
	{
		return;
	}
	if(L->cursor != NULL && L->cursor != L->front)
	{
		L->cursor = L->cursor->prev;
		L->index--;
		return;
	}
}

// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L)
{
	if(L == NULL)
	{
		fprintf(stderr, "List error: moveNext() was called on an undefined list.\n");
		exit(1);
	}
	if(L->cursor != NULL && L->cursor == L->back)
	{
		L->cursor = NULL;
		L->index = -1;
		return;
	}
	if(L->cursor == NULL)
	{
		return;
	}
	if(L->cursor != NULL && L->cursor != L->back)
	{
		L->cursor = L->cursor->next;
		L->index++;
		return;
	}
}

// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(List L, int data)
{
	if(L == NULL)
	{
		fprintf(stderr, "List error: prepend() was called on an undefined list.\n");
		exit(1);
	}
	Node newFront = newNode(data);
	if(L->length == 0)
	{
		L->front = L->back = newFront;
		L->length++;
		return;
	}
	if(L->length > 0 && L->cursor != NULL)
	{
		newFront->next = L->front;
		L->front->prev = newFront;
		L->front = newFront;
		L->length++;
		L->index++;
		return;
	}
	if(L->length > 0 && L->cursor == NULL)
	{
		newFront->next = L->front;
		L->front->prev = newFront;
		L->front = newFront;
		L->length++;
		return;
	}

}

// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, int data)
{
	if(L == NULL)
	{
		fprintf(stderr, "List error: append() was called on an undefined list.\n");
		exit(1);
	}
	Node newBack = newNode(data);
	if(L->length == 0)
	{
		L->back = L->front = newBack;
		L->length++;	
		return;
	}
	if(L->length > 0)
	{
		L->back->next = newBack;
		newBack->prev = L->back;
		L->back = newBack;
		L->length++;
		return;
	}
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data)
{
	if(L == NULL)
	{
		fprintf(stderr, "List error: insertBefore() was called on an undefined list.\n");
		exit(1);
	}
	if(L->length == 0)
	{
		fprintf(stderr, "List error: insertBefore() was called on an empty list.\n");
		exit(1);
	}
	if(L->index == -1)
	{
		fprintf(stderr, "List error: insertBefore() was called on empty list.\n");
		exit(1);
	}
	if(length(L) > 0 && index(L) >= 0)
	{
		Node newStuff = newNode(data);
		if(L->cursor == L->front)
		{	
			L->cursor->prev = newStuff;
			newStuff->next = L->cursor;
			L->front = newStuff;
			L->length++;
			L->index++;
		}
		else
		{
			Node temp = L->cursor;
			temp = temp->prev;
			newStuff->next = L->cursor;
			newStuff->prev = temp;
			temp->next = newStuff;
			L->cursor->prev = newStuff;
			L->length++;
			L->index++;
		}
	}
}

// Inserts new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data)
{
	if(L == NULL)
	{
		fprintf(stderr, "List error: insertAfter() was called on an undefined list.\n");
		exit(1);
	}
	if(L->length == 0)
	{
		fprintf(stderr, "List error: insertAfter() was called on an empty list.\n");
		exit(1);
	}
	if(L->index == -1)
	{
		fprintf(stderr, "List error: insertAfter() was called with an undefined cursor.\n");
		exit(1);
	}
	if(L->length > 0 && L->index >= 0)
	{
		Node newStuff = newNode(data);
		if(L->cursor == L->back)
		{
			L->back = newStuff;
		}
		newStuff->prev = L->cursor;
		newStuff->next = L->cursor->next;
		if(L->cursor->next != NULL)
		{
			L->cursor->next->prev = newStuff;
		}
		L->cursor->next = newStuff;
		L->length++;
	}
}

// Deletes the front element. Pre: length()>0
void deleteFront(List L)
{
	if(L == NULL)
	{
		fprintf(stderr, "List error: deleteFront() was called on an undefined list\n");
		exit(1);
	}
	if(L->length == 0)
	{
		fprintf(stderr, "List error: deleteFront() was called on an empty list\n");
		exit(1);
	}
	if(L->length == 1)
	{
		clear(L);
		return;
	}
	Node temp = L->front;
	if(L->cursor == L->front)
	{
		L->cursor = NULL;
	}
	L->front = L->front->next;
	L->front->prev = NULL;
	L->length--;
	L->index--;
	freeNode(&temp);
	return;
}

// Deletes the back element. Pre: length()>0
void deleteBack(List L)
{
	if(L == NULL)
	{
		fprintf(stderr, "List error: deleteBack() was called on an undefined list\n");
		exit(1);
	}
	if(L->length == 0)
	{
		fprintf(stderr, "List error: deleteBack() was called on an empty list\n");
		exit(1);
	}
	if(L->length == 1)
	{
		clear(L);
		return;
	}
	Node temp = L->back;
	if(L->cursor == L->back)
	{
		L->cursor = NULL;
		L->index = -1;
	}
	L->back = L->back->prev;
	L->back->next = NULL;
	L->length--;
	freeNode(&temp);
	return;
}

// Deletes cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
// Other methods
void delete(List L)
{
	if(L == NULL) 
	{
    	fprintf(stderr, "List error: delete() called on undefined list\n");
    	exit(1);
    }
    if(L->length == 0) 
    {
    	fprintf(stderr, "List error: delete() called on an empty List\n");
    	exit(1);
    }
    if(L->cursor == NULL) 
    {
    	fprintf(stderr, "List error: delete() called with an undefined cursor\n");
    	exit(1);
    }
    if(L->length > 0 && L->index >= 0)
    {
    	if(L->cursor == L->back) 
    	{
    		deleteBack(L);
    		return;
    	}
    	if(L->cursor == L->front)
    	{
    		deleteFront(L);
    		return;
    	}
   		else
    	{
    		Node temp = L-> cursor;
    		L->cursor->prev->next = L->cursor->next;
    		L->cursor->next->prev = L->cursor->prev;
    		L->cursor = NULL;
    		L->index = -1;
    		L->length--;
    		freeNode(&temp);
    		return;
    	}
    }
}
//other stuff--------------------------------------------------------------------------

// Prints a String representation of this List 
//consisting of a space separated sequence of integers, 
//with front on left.
void printList(FILE* out, List L)
{
	Node D = NULL;

	if(L == NULL)
	{
		fprintf(stderr, "List error: printList() was called on an undefined list\n");
		exit(1);
	}	
	if(length(L) > 0)
	{
		for(D = L->front; D != NULL && D->next != NULL; D = D->next)
		{
			fprintf(out, "%d ", D->data);
		}
		if(D->next == NULL && D != NULL)
		{
			fprintf(out, "%d", D->data);
		}
	}
}

// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L)
{
	List copy = newList();
	Node tempFront = L->front;
	while(tempFront != NULL)
	{
		append(copy, tempFront->data);
		tempFront = tempFront->next;
	}
	copy->length = L->length;
	return copy;
}