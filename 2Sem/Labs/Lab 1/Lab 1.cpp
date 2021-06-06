#include <iostream>
#include "Stack.h"

using namespace std;

int main()
{
    Stack<int> test, list_to_add;           //Объявление
    cout << "Добавление элементов: ";
    test.add(2, 0);                         //Добавление элементов
    test.add(5);
    test.add(7);
    test.add(3, 1);
    test.add(8, 10);
    test.print();                           //Вывод содержимого
    int sz = test.size();                   //Размер
    cout << "Размер списка: " << sz << endl;
    int* arr = new int[sz];
    cout << "Считывание содержимого: ";
    arr = test.read();                      //Считывание содержимого
    for (int i = 0; i < sz; i++) cout << arr[i] << " ";
    cout << endl;
    cout << "Сортировка: ";
    test.sort();                            //Сортировка
    test.print();
    cout << "Удаление элемента: ";
    test.del();                             //Удаление элемента
    test.print();
    cout << "Поиск по ключу:" << endl;
    cout << test.find(5) << endl;           //Поиск по ключу
    cout << test.find(0) << endl;
    cout << "Провека наличия содержимого: " << list_to_add.is_empty() << endl;    //Проверка наличия содержимого
    list_to_add.add(9);
    list_to_add.add(7);
    int sz1 = list_to_add.size();
    int t = (sz > sz1)? sz1 : sz;
    Stack<int> *crossed = new Stack<int>[t];
    cout << "Пересечение списков: ";
    crossed = list_to_add.cross(test);      //Пересечение списков
    crossed->print();
    cout << "Объединение списков: ";
    test.unite(list_to_add);                //Объединение списков
    test.print();
    return 0;
}