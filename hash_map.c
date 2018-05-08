#include "hash_map.h"

#include <stdlib.h>
#include <string.h>

int HKeysAreEqual(HMapKeyType a, HMapKeyType b);
pHashMapElement GetMapElementFromHMap(pHashMap map, HMapKeyType key);
unsigned hash_func(unsigned size, HMapKeyType key);

pHashMap CreateHMap(unsigned size)
{	
	if(size == 0)
		return NULL;
	
	pHashMap map = (pHashMap) malloc(sizeof(HashMap));
	map->size = size;
	
	map->data = (pList*) malloc(size * sizeof(pList));
	
	int i;
	for(i=0; i<size; i++)
		map->data[i] = CreateList();
	
	return map;
}

void DeleteHMap(pHashMap* _map)
{
	pHashMap map = *_map;
	
	int i;
	for(i=0; i<map->size; i++)
	{
		ListIterator iter;
		for(iter = GetBeginListIterator(map->data[i]);
			!IsListIteratorNULL(&iter);
			ListIteratorNext(&iter))
		{
			free(GetListIteratorValue(&iter));
			DeleteListElementByIterator(&iter);
		}
		
		DeleteList(&(map->data[i]));
	}
	
	free(map->data);
	
	free(*_map);
	*_map = NULL;
}

void AddToHMap(pHashMap map, HMapKeyType key, HMapValueType value)
{
	pHashMapElement element = GetMapElementFromHMap(map, key);
	
	if(element)
	{
		element->value = value;
		return;
	}
	
	element = (pHashMapElement) malloc(sizeof(HashMapElement));
	element->key = key;
	element->value = value;
	
	unsigned hash = hash_func(map->size, key);
	PushBackToList(map->data[hash], element);
}

int IsInHMap(pHashMap map, HMapKeyType key)
{
	pHashMapElement element = GetMapElementFromHMap(map, key);
	
	return element != NULL;
}

HMapValueType GetFromHMap(pHashMap map, HMapKeyType key)
{
	pHashMapElement element = GetMapElementFromHMap(map, key);
	
	return element?element->value:NULL;
}

pHashMapElement GetMapElementFromHMap(pHashMap map, HMapKeyType key)
{
	unsigned hash = hash_func(map->size, key);
	
	ListIterator iter;
	for(iter = GetBeginListIterator(map->data[hash]);
		!IsListIteratorNULL(&iter);
		ListIteratorNext(&iter))
	{
		pHashMapElement current = (pHashMapElement) GetListIteratorValue(&iter);
		
		if(HKeysAreEqual(key, current->key))
		{
			return current;
		}
	}
	
	return NULL;
}

pList HMapGetKeys(pHashMap map)
{
	pList list = CreateList();
	
	int i;
	for(i=0; i<map->size; i++)
	{
		ListIterator iter;
		for(iter = GetBeginListIterator(map->data[i]);
			!IsListIteratorNULL(&iter);
			ListIteratorNext(&iter))
		{
			pHashMapElement current = (pHashMapElement) GetListIteratorValue(&iter);
			PushBackToList(list, current->key);
		}
	}
	
	return list;
}

unsigned hash_func(unsigned size, HMapKeyType key)
{
	int hash = 7;
	unsigned len = strlen(key);
	
	int i;
	for(i=0; i<len; i++)
		hash = hash*31 + key[i];
	
	return hash % size;
}

int HKeysAreEqual(HMapKeyType a, HMapKeyType b)
{
	return strcmp(a, b) == 0;
}
