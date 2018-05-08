#include <stdio.h>
#include "JParser.h"
#include "calcul.h"
#include "hash_map.h"

int main()
{
    pJsonElement json = JParser("calcul.txt");
    mainCalculator(json);

    DeleteJSON(json);

    return 0;
}