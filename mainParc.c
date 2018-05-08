#include <stdio.h>
#include "JParser.h"
#include "hash_map.h"

int main()
{
    pJsonElement json = JParser("data.json.txt");

    DeleteJSON(json);

    return 0;
}
