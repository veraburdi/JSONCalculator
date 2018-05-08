#ifndef __LIST_H__
#define __LIST_H__

typedef struct _list_element
{
	void *value;
	struct _list_element *next;
	struct _list_element *prev;
} ListElement, *pListElement;

typedef struct _list
{
	pListElement first;
	pListElement last;
} List, *pList;

pList CreateList();
void DeleteList(pList*);

void PushBackToList(pList, void*);

typedef struct _list_iterator
{
	pList list;
	
	pListElement current_value;
	
	pListElement prev;
	pListElement next;
} ListIterator, *pListIterator;

pListIterator CreateBeginListIterator(pList);
ListIterator GetBeginListIterator(pList);
void DeleteListIterator(pListIterator*);

void DeleteListElementByIterator(pListIterator);
int InsertListElementAfterIterator(pListIterator, void*);

int ListIteratorNext(pListIterator);
int ListIteratorPrev(pListIterator);
int ListIteratorHasNext(pListIterator);
int ListIteratorHasPrev(pListIterator);

int IsListIteratorNULL(pListIterator);

void* GetListIteratorValue(pListIterator);

//void DeleteListFragmentBetweenIterators(pListIterator from, pListIterator to);

#endif	//__LIST_H__
