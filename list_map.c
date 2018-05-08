#include "list_map.h"

#include <stdlib.h>

int SKeysAreEqual(SMapKeyType a, SMapKeyType b);
pSimpleMapElement GetMapElementFromSMap(pSimpleMap map, SMapKeyType key);

pSimpleMap CreateSMap()
{
	pSimpleMap map = (pSimpleMap) malloc(sizeof(SimpleMap));
	
	map->data = CreateList();
	
	return map;
}

void DeleteSMap(pSimpleMap *map)
{
	if(map == NULL)
	{
		return;
	}
	
	ListIterator iter;
	for(iter = GetBeginListIterator((*map)->data);
		!IsListIteratorNULL(&iter);
		ListIteratorNext(&iter))
	{
		free(GetListIteratorValue(&iter));
		DeleteListElementByIterator(&iter);
	}
	
	DeleteList(&(*map)->data);
	
	free(*map);
	*map = NULL;
}

void AddToSMap(pSimpleMap map, SMapKeyType key, SMapValueType value)
{
	// if exists
	pSimpleMapElement element = GetMapElementFromSMap(map, key);
	
	if(element)
	{
		element->value = value;
		return;
	}
	
	// add new
	pSimpleMapElement new_element = (pSimpleMapElement) malloc(sizeof(SimpleMapElement));
	new_element->key = key;
	new_element->value = value;
	
	PushBackToList(map->data, new_element);
}

int IsInSMap(pSimpleMap map, SMapKeyType key)
{
	pSimpleMapElement element = GetMapElementFromSMap(map, key);
	
	return element != NULL;
}

SMapValueType GetFromSMap(pSimpleMap map, SMapKeyType key)
{
	pSimpleMapElement element = GetMapElementFromSMap(map, key);
	
	return element?element->value:NULL;
}

pSimpleMapElement GetMapElementFromSMap(pSimpleMap map, SMapKeyType key)
{
	ListIterator iter;
	for(iter = GetBeginListIterator(map->data);
		!IsListIteratorNULL(&iter);
		ListIteratorNext(&iter))
	{
		pSimpleMapElement current = (pSimpleMapElement) GetListIteratorValue(&iter);
		
		if(SKeysAreEqual(key, current->key))
		{
			return current;
		}
	}
	
	return NULL;
}


int SKeysAreEqual(SMapKeyType a, SMapKeyType b)
{
	return strcmp(a, b) == 0;
}
