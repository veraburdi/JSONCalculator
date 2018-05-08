#include "JParser.h"
#include "list.h"
#include "hash_map.h"
#include "calcul.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void mainCalculator(pJsonElement element)
{
    if (element->type != JSON_MAP || !IsInHMap(element->value, "calculate"))
    {
        printf("Wrong structure of calculator-JSON \n");
        return;
    }

    //printf("mainCalaculator started \n");
    pJsonElement root = GetFromHMap(element->value, "calculate");

    int answer = arg_calculator(root);
    printf(" = %d \n", answer);
    //printf("mainCalaculator finished \n");
}



int arg_calculator(pJsonElement element)
{
    if (!element)
    {
        printf("arg_calculator error: element couldn't be found\n");
        return 0;
    }

    //printf("arg_calaculator started \n");

    if (element->type == JSON_VALUE)
    {
        return fromCharToInt(element->value);
    }

    if (element->type == JSON_MAP)
    {

        int res;

        pJsonElement arg1 = GetFromHMap(element->value, "arg1");
        pJsonElement arg2 = GetFromHMap(element->value, "arg2");

        if (IsInHMap(element->value, "sum"))
        {
            element = GetFromHMap(element->value, "sum");
            pJsonElement arg1 = GetFromHMap(element->value, "arg1");
            pJsonElement arg2 = GetFromHMap(element->value, "arg2");

            res = sum(arg1, arg2);	
        }

        if (IsInHMap(element->value, "sub"))
        {
            element = GetFromHMap(element->value, "sub");

            pJsonElement arg1 = GetFromHMap(element->value, "arg1");
            pJsonElement arg2 = GetFromHMap(element->value, "arg2");

            res = sub(arg1, arg2);
        }

        if (IsInHMap(element->value, "mul"))
        {
            element = GetFromHMap(element->value, "mul");

            pJsonElement arg1 = GetFromHMap(element->value, "arg1");
            pJsonElement arg2 = GetFromHMap(element->value, "arg2");

            res = mul(arg1, arg2);
        }

        if (IsInHMap(element->value, "div"))
        {
            element = GetFromHMap(element->value, "div");

            pJsonElement arg1 = GetFromHMap(element->value, "arg1");
            pJsonElement arg2 = GetFromHMap(element->value, "arg2");

            res = c_div(arg1, arg2);
        }

        //printf("arg_calaculator finished \n");

        return res;
    }

    printf("arg_calculator error with operation : %s", element->key);
}



int sum(pJsonElement arg1, pJsonElement arg2)
{
    printf("( ");

    int a = arg_calculator(arg1);
    if (arg1->type == JSON_VALUE)
    {
        printf("%d", a);
    }

    printf(" + ");

    int b = arg_calculator(arg2);
    if (arg2->type == JSON_VALUE)
    {
        printf("%d", b);
    }

    printf(" )");

    return (a + b);
}

int sub(pJsonElement arg1, pJsonElement arg2)
{
    printf("( ");

    int a = arg_calculator(arg1);
    if (arg1->type == JSON_VALUE)
    {
        printf("%d", a);
    }

    printf(" - ");

    int b = arg_calculator(arg2);
    if (arg2->type == JSON_VALUE)
    {
        printf("%d)", b);
    }

    printf(" )");

    return (a - b);
}

int mul(pJsonElement arg1, pJsonElement arg2)
{
    printf("( ");

    int a = arg_calculator(arg1);
    if (arg1->type == JSON_VALUE)
    {
        printf("%d", a);
    }

    printf(" * ");

    int b = arg_calculator(arg2);
    if (arg2->type == JSON_VALUE)
    {
        printf("%d", b);
    }

    printf(" )");

    return (a * b);
}

int c_div(pJsonElement arg1, pJsonElement arg2)
{
    printf("( ");

    int a = arg_calculator(arg1);
    if (arg1->type == JSON_VALUE)
    {
        printf("%d", a);
    }
    printf(" / ");

    int b = arg_calculator(arg2);
    if (arg2->type == JSON_VALUE)
    {
        printf("%d", b);
    }

    printf(" )");

    return (a / b);
}


int fromCharToInt(char *string)
{
	int a = 0;
	for(int i = 0; i < strlen(string); i++)
	{
		a = a*10 + (int)(string[i] - '0');
	}
	return a;
 
}