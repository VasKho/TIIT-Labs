#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#ifndef _SET_H_
#define _SET_H_
#define MAX_LENGTH 255
#define TUPLE_START '<'
#define TUPLE_END '>'
#define SET_BEGIN '{'
#define SET_END '}'
#define DEFINE_SYMBOL '='
#define TERMINATE ';'
#define DIVIDE_SYMBOL ','




// Cтруктура под элемент множества
struct Element
{
    int def;
    char* simple_el;
    struct Element* next_el;
    struct Element* subset;
};

// Cтруктура под множество
typedef struct
{
    char* name;
    struct Element* elements;
}set;

// Добавление элемента в множество
void add(set*, struct Element*, int);

// Считывание самих множеств
void scan_set(FILE*, set*, int);

// Вывод множества
void print_set(set);

// Сравнение элементов
int compare_elements(set*, struct Element*, struct Element*);

void dfs(set*, set*, set*);
#endif