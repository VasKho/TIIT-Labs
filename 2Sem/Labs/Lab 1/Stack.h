#pragma once
#ifndef _Stack_H_
#define _Stack_H_
#include <cstddef>

template <typename T>
class Stack
{
private:
    struct list
    {
        T data;
        list* next;
    }*top;
public:
    Stack()
    {
        top = NULL;
    };
    void add(T, int = 0);           //Добавление элементов
    void del();                     //Удаление элемента
    void print();                   //Вывод содержимого
    void sort();                    //Сортировка
    T* read();                      //Считывание содержимого
    int find(T);                    //Поиск по ключу
    int size();                     //Размер
    void unite(Stack);              //Объединение списков
    Stack* cross(Stack);            //Пересечение списков
    bool is_empty();                //Проверка наличия содержимого
};


template <typename T>
void Stack<T>::add(T inf, int pos)
{
    int i = 0;
    list *comp = new list;
    if (pos < 0) std::cout << "Error! Out of range" << std::endl;
    if (pos == 0)
    {
        comp->data = inf;
        comp->next = top;
        top = comp;
    }
    else
    {
        comp = top;
        while (comp)
        {
            int sz = size();
            if (pos > sz) pos = sz;
            list *add = new list;
            if (i + 1 == pos)
            {
                add->data = inf;
                add->next = comp->next;
                comp->next = add;
                return;
            }
            i++;
            comp = comp->next;
        }
    }
}

template <typename T>
void Stack<T>::del()
{
    if (!top) 
    {
        std::cout << "The list is empty" << std::endl;
        return;
    }
    list* comp = new list;
    comp = top;
    top = comp->next;
    comp->data = '\0';
}

template <typename T>
void Stack<T>::print()
{
    list* comp = top;
    while (comp)
    {
        std::cout << comp->data << " ";
        comp = comp->next;
    }
    std::cout << std::endl;
}

template <typename T>
void Stack<T>::sort()
{
    add(0);
  	list *exit = NULL, *cur_top, *temp;
  	if (top->next->next == NULL) return;
  	do 
    {
     	for (cur_top = top; cur_top->next->next  != exit; cur_top = cur_top->next)
        	if (cur_top->next->data  >  cur_top->next->next->data)
            {
            	temp = cur_top->next->next;
            	cur_top->next->next = temp->next;
            	temp->next = cur_top->next;
            	cur_top->next = temp;
        	}
     	exit = cur_top-> next;
  	} while (top->next->next != exit);
    del();
}

template <typename T>
T* Stack<T>::read()
{
    int i = 0, sz = size();
    T* arr;
    arr = new T[sz];
    list* comp = new list;
    comp = top;
    while (comp)
    {
        arr[i] = comp->data;
        i++;
        comp = comp->next;
    }
    return arr;    
}

template <typename T>
int Stack<T>::find(T key)
{
    list* comp = new list;
    comp = top;
    while (comp)
    {
        if (comp->data == key) return key;
        comp = comp->next;
    }
    return -1;
}

template <typename T>
int Stack<T>::size()
{
    int k = 0;
    list* comp = new list, *temp = new list;;
    comp = top;
    while (comp)
    {
        k++;
        comp = comp->next;
    }
    return k;
}

template <typename T>
void Stack<T>::unite(Stack list_add)
{
    int i = list_add.size()-1;
    T* buff = new T[list_add.size()-1];
    buff = list_add.read();
    while(i >= 0)
    {
        add(buff[i]);
        i--;
    }
    delete[] buff;
}

template <typename T>
Stack<T>* Stack<T>::cross(Stack spis)
{
    Stack<T>* crossed;
    list *comp = new list;
    comp = top;
    while (comp)
    {
        if (spis.find(comp->data) != -1) crossed->add(comp->data);
        comp = comp->next;
    }
    return crossed;
}

template <typename T>
bool Stack<T>::is_empty()
{
    if (!top) return true;
    return false;
}
#endif