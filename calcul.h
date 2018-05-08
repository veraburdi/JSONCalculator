#ifndef __CALCUL_H__
#define __CALCUL_H__


#include "hash_map.h"
#include "list.h"
#include "JParser.h"

void mainCalculator(pJsonElement json);

int arg_calculator(pJsonElement element);

int sum(pJsonElement arg1, pJsonElement arg2);
int sub(pJsonElement arg1, pJsonElement arg2);
int mul(pJsonElement arg1, pJsonElement arg2);
int c_div(pJsonElement arg1, pJsonElement arg2);

int fromCharToInt(char *string);

#endif

