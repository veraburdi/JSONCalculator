#ifndef __J_PARSER_H__
#define __J_PARSER_H__

#include "hash_map.h"
#include "list.h"


typedef enum JsonElementValueType
{
	JSON_VALUE,
	JSON_ARRAY,
	JSON_MAP
} JsonElementValueType;

typedef struct JsonElement
{
	JsonElementValueType type;
	char *key;
	void *value;
} JsonElement, *pJsonElement;

pJsonElement JParser (char *filename);

void skipDelimiters(char **p);

char* CopyTag(char **p);

pJsonElement ParseJData(char **json_data);
pHashMap ParseJMap(char **json_data);
pList ParseJList(char **json_data);

void DeleteJSON(pJsonElement element);

#endif