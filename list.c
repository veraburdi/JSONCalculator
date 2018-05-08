#include "list.h"

#include <stdlib.h>

pList CreateList()
{
	pList lst = (pList) malloc(sizeof(List));
	
	lst->first = lst->last = NULL;
	
	return lst;
}

void DeleteList(pList* lst)
{
	if(lst == NULL)
	{
		return;
	}
	
	ListIterator iter = GetBeginListIterator(*lst);
	while(!IsListIteratorNULL(&iter))
	{
		DeleteListElementByIterator(&iter);
		ListIteratorNext(&iter);
	}
	
	free(*lst);
	*lst = NULL;
}

void PushBackToList(pList lst, void *value)
{
	pListElement new_element = (pListElement) malloc(sizeof(ListElement));
	
	new_element->value = value;
	
	new_element->prev = lst->last;
	new_element->next = NULL;
	
	if(lst->first == NULL)	// empty list
	{
		lst->first = new_element;
	}
	else
	{
		lst->last->next = new_element;
	}
	
	lst->last = new_element;
}
