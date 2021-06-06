
#include <stdio.h>
#include <stdlib.h>
#include "libraries/Sets.h"

FILE* src;

int main(int argc, char* argv[])
{
    if(!(src = fopen(argv[1], "r"))) printf("Can not open file!");
    set* test;
    int k = 0;
    while(!feof(src)) if (fgetc(src) == DEFINE_SYMBOL) k++;
    test = (set*)malloc(k*sizeof(set));
    fseek(src, 0, SEEK_SET);
    scan_set(src, test, k);
    for (int i = 0; i < k; i++) 
        print_set(test[i]);
    set Union;
    Union.name = "Union";
	Union.elements = NULL;
    struct Element* temp = test[0].elements;
    while (temp != NULL)
    {
        add(&Union, temp, 0);
        temp = temp->next_el;
    }
    for (int i = 1; i < k; i++)
        dfs(test, &Union, &test[i]);
        print_set(Union);
    return 0;
}
