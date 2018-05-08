#include "JParser.h"
#include "list.h"
#include "hash_map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


pJsonElement JParser(char *filename)
{
	FILE *json_file = fopen(filename, "rt");

    if (!json_file)
    {
        printf("file getting error\n");
        return NULL;
    }

    fseek(json_file, 0, SEEK_END);

    unsigned size = ftell(json_file);

    fseek(json_file, 0, SEEK_SET);

    printf("file size is %u\n", size);
    char *Json_data = (char *)malloc(sizeof(char) * (size + 1));
    Json_data[size] = '\0';

    fread(Json_data, size, 1, json_file);
    fclose(json_file);

    printf("Main Parsing started:\n");
    pJsonElement element = ParseJData(&Json_data);
    printf("Main Parsing finished\n");
	
    return element;
}



pJsonElement ParseJData(char **Json_data)
{
	skipDelimiters(Json_data);
	
	if(**Json_data != '{' && **Json_data != '[' && **Json_data != '"')
	{
		printf("First symbol is not \" or { or [ \n");
		return NULL;
	}
	
	pJsonElement element = (pJsonElement) malloc(sizeof(JsonElement));
	element->key = NULL;
	element->value = NULL;

	if(**Json_data == '{')
	{
		printf("Element is map\n");
		element->type = JSON_MAP;
		element->value = ParseJMap(Json_data);
        return element;
	}
	
	if(**Json_data == '[')
	{
		printf("Element is array\n");
		element->type = JSON_ARRAY;
		element->value = ParseJList(Json_data);
        return element;
	}
	
	if(**Json_data == '"')
	{
		element->type = JSON_VALUE;
		element->value = CopyTag(Json_data);
		printf("Element is value: %s\n", (char *)element->value);
        return element;
	}
			
	if(!element->value)
	{
		printf("Main JSON structure error\n");
		return NULL;
	}
	
}



pHashMap ParseJMap(char **Json_data)
{
    printf("ParseJMap started\n");

    pHashMap map = CreateHMap(10);

    *Json_data = *Json_data + 1;

    while (**Json_data != '\0')
    {

        skipDelimiters(Json_data);

        if(**Json_data == '}')
		{
            printf("ParseJMap finished (} character found)\n");
            //printf("%s\n", *Json_data);
			*Json_data += 1;
			break;
		}

        if (**Json_data != '"')
        {
            printf("key not found\n");
            return NULL;
        }

        char *key = CopyTag(Json_data);
        *Json_data += 1;
        printf("key is  %s\n", key);

        skipDelimiters(Json_data);

        if (**Json_data != ':')
        {
            printf("colon not found\n");
            return NULL;
        }
        *Json_data += 1;
        skipDelimiters(Json_data);

        pJsonElement element = ParseJData(Json_data);

        if (**Json_data == '"')
            *Json_data += 1;

        if (!element)
        {
            printf("element error\n");
            return NULL;
        }

        element->key = key;

        AddToHMap(map, key, element);
        skipDelimiters(Json_data);

        if(**Json_data == ',')
		{
			*Json_data += 1;
		} else {
			if(**Json_data != '}')
			{
				printf("'}' not found \n");
				return NULL;
			}
		}		

     
    }

    printf("ParseJMap finished \n");

    return map;
}



pList ParseJList(char **Json_data)
{

    printf("ParseJList started\n");

    pList lst = CreateList();

    while (**Json_data != ']')
    {
        *Json_data += 1;
        skipDelimiters(Json_data);
        if (**Json_data != '{')
        {
            printf("not found map for list\n");
            return NULL;
        }
        pJsonElement element = ParseJData(Json_data);

        if (**Json_data == '"')
            *Json_data += 1;

        PushBackToList(lst, element);
        skipDelimiters(Json_data);
        if (**Json_data == ']')
        {
            printf(" out\n");
            *Json_data += 1;
            return lst;
        }

        if(**Json_data == ',')
		{
			*Json_data += 1;
		} else {
			skipDelimiters(Json_data);;
			if(**Json_data != ']')
			{
				printf("Closing bracer ']' not found");
				return NULL;
			}
		}
    }
    return lst;
}



void skipDelimiters(char **p)
{
    //printf("skipdelimiters started \n");
    //printf("%s", *p);
    while ((**p == '\n') || (**p == '\t') || (**p == ' ') || (**p == '\r'))
    {
        //printf("1\n");
        *p += 1;
    }
    //printf("skipdelimiters finished \n");
    //printf("%s", *p);
}



char* CopyTag(char **p)
{
    //printf("copytag started \n");
    if (**p != '"')
    {
        printf("Copy Tag error\n");
        return NULL;
    }

    char *beg = *p;
    *p += 1;
    while (**p != '"')
        *p += 1;

    unsigned size = (int)(*p - beg) - 1;
    char *res = (char *)malloc(sizeof(char) * (size + 1));

    memcpy(res, beg + 1, size);
    res[size] = '\0';
    //printf("copytag finished \n");
    return res;
}



void DeleteJSON(pJsonElement element)
{
    if(element == NULL)
    {
        printf("DeleteJSON error, element couldn't be found\n");
        return;
    }
    
    //printf("Enter DeleteJSON\n");
    
    if(element->type == JSON_VALUE)
    {
        //printf("Delete value %s\n", element->key);
        
        free(element->value);
    }
    else if(element->type == JSON_ARRAY)
    {
        //printf("Delete list %s\n", element->key);
        ListIterator iter;
        for(iter = GetBeginListIterator(element->value);
            !IsListIteratorNULL(&iter);
            ListIteratorNext(&iter))
        {
            DeleteJSON(GetListIteratorValue(&iter));
            DeleteListElementByIterator(&iter);
        }
        
        free(element->value);
    }
    else if(element->type == JSON_MAP)
    {
        //printf("Delete map %s\n", element->key);
        
        pHashMap map = element->value;
        
        pList keys = HMapGetKeys(map);
        
        ListIterator iter;
        for(iter = GetBeginListIterator(keys);
            !IsListIteratorNULL(&iter);
            ListIteratorNext(&iter))
        {
            char *key = GetListIteratorValue(&iter);
            DeleteJSON((pJsonElement)GetFromHMap(map, key));
        }
        
        DeleteList(&keys);
        
        DeleteHMap(&map);
    }

    //printf("DeleteJSON finished\n");
}