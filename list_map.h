#ifndef __LIST_MAP__
#define __LIST_MAP__

#include "list.h"
#include <string.h>

typedef char *SMapKeyType;
typedef void *SMapValueType;

typedef struct _simple_map_element
{
	SMapKeyType key;
	SMapValueType value;
} SimpleMapElement, *pSimpleMapElement;

typedef struct _simple_map
{
	pList data;
} SimpleMap, *pSimpleMap;

pSimpleMap CreateSMap();
void DeleteSMap(pSimpleMap*);

void AddToSMap(pSimpleMap, SMapKeyType, SMapValueType);

int IsInSMap(pSimpleMap, SMapKeyType);
SMapValueType GetFromSMap(pSimpleMap, SMapKeyType);

#endif	//__LIST_MAP__
