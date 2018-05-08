#include "list.h"

#include <stdlib.h>

pListIterator CreateBeginListIterator(pList lst)
{
	if(!lst)
		return NULL;
	
	pListIterator itr = (pListIterator) malloc(sizeof(ListIterator));
	itr->list = lst;
	itr->prev = NULL;
	itr->current_value = lst->first;
	//itr->next = lst->first?lst->first->next:NULL;
	
	if(lst->first)
	{
		itr->next = lst->first->next;
	}
	else 
	{
		itr->next = NULL;
	}

	return itr;
}

ListIterator GetBeginListIterator(pList lst)
{
	if(!lst)
	{
		ListIterator itr = { NULL, NULL, NULL, NULL };
		return itr;
	}
	
	//ListIterator itr = {lst, lst->first, NULL, lst->first?lst->first->next:NULL};

	
	if(lst->first)
	{
		ListIterator itr = {lst, lst->first, NULL, lst->first->next};
		return itr;
	}
	else 
	{
		ListIterator itr = {lst, lst->first, NULL, NULL};
		return itr;
	}
}

void DeleteListIterator(pListIterator *itr)
{
	free(*itr);
	*itr = NULL;
}

void DeleteListElementByIterator(pListIterator itr)
{
	if(itr->list == NULL)
	{
		return;
	}
	
	if(itr->prev == NULL)	// first in list
	{
		itr->list->first = itr->next;
	}
	else
	{
		itr->prev->next = itr->next;
	}
	
	if(itr->next == NULL)	// last in list
	{
		itr->list->last = itr->prev;
	}
	else
	{
		itr->next->prev = itr->prev;
	}
	
	if(itr->current_value)
		free(itr->current_value);
	itr->current_value = NULL;
}

int InsertListElementAfterIterator(pListIterator itr, void* value)
{
	if(itr->list == NULL || itr->current_value == NULL)
	{
		return 0;
	}
	
	pListElement element = (pListElement) malloc(sizeof(ListElement));
	element->value = value;
	
	if(itr->next == NULL)	// last in list
	{
		itr->list->last = element;
	}
	else
	{
		itr->next->prev = element;		
	}
	
	if(itr->prev == NULL)
	{
		itr->list->first = element;
	}
	
	element->next = itr->next;
	itr->current_value->next = element;
	element->prev = itr->current_value;
	itr->next = element;
	
	return 1;
}

int ListIteratorNext(pListIterator itr)
{
	if(itr->current_value)
	{
		itr->prev = itr->current_value;
	}
		
	itr->current_value = itr->next;
	if(itr->next)
	{
		itr->next = itr->next->next;
	}
	
	return itr->current_value == NULL;
}

int ListIteratorPrev(pListIterator itr)
{
	if(itr->current_value)
	{
		itr->next = itr->current_value;
	}
	
	itr->current_value = itr->prev;
	if(itr->prev)
	{
		itr->prev = itr->prev->prev;
	}
	
	return itr->current_value == NULL;
}
int ListIteratorHasNext(pListIterator itr)
{
	return itr->next != NULL;
}

int ListIteratorHasPrev(pListIterator itr)
{
	return itr->prev != NULL;
}

int IsListIteratorNULL(pListIterator itr)
{
	return itr->current_value == NULL;
}

void* GetListIteratorValue(pListIterator itr)
{
	if(itr->current_value)
	{
		return itr->current_value->value;
	}
	
	return NULL;
}
