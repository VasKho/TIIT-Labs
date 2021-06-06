#include "Sets.h"

struct Element element;

// Переменные для обнаружения нарушения вложенности скобок
int tuple_count = 0;
int set_count = 0;
int amount_of_sets = 0;

//константы разрешённых символов
const char* allowed_name_symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_";
const char* allowed_symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_{}<>,;=\n";
// Инициализация множества
// Входные данные:
// s - инициализируемое множество
void SetInit(set s)
{
    s.name = NULL;
    s.elements = NULL;
    return;
}

// Добавление элемента, который является множеством, в множество
// Входные данные:
// start_1 - адрес ячейки назначения
// start_2 - адрес ячейки источника
void add_sub(struct Element* start_1, struct Element* start_2)
{
	struct Element* sub_1 = start_1, *sub_2 = start_2; 
	// С помощью цикла переписываем все элементы из одного множества во второе
	while (sub_2 != NULL)
	{
		// Если встречена ячейка с множеством, то рекурсивно записываем его
		if (sub_2->subset != NULL)
		{
			sub_1->subset = (struct Element*)malloc(sizeof(struct Element));
			sub_1->def = sub_2->def;
			add_sub(sub_1->subset, sub_2->subset);
		}
		// Если нет, то просто переносим информацию
		else 
		{
			sub_1->simple_el = sub_2->simple_el;
			// В случае, когда мы дошли до конца читаемого множества
			// выходим из цикла
			if (sub_2 == NULL) return;
		}
		// Создаём следующую ячейку для записи и
		// переходим на неё
		if (sub_1->next_el == NULL && sub_2->next_el != NULL) sub_1->next_el = (struct Element*)malloc(sizeof(struct Element));
		sub_1 = sub_1->next_el;
		sub_2 = sub_2->next_el;

	}
	return;
}

// Добавление элемента в множество
// Входные данные:
// set_to_add (to) - множество, в которое добавляется элемент
// element_to_add - адрес ячейки для добавления
// is_a_link - значение, показывающее, передаём ли мы множество целиком, или только единичный элемент
void add(set* set_to_add, struct Element* element_to_add, int is_a_link)
{
	struct Element* component = set_to_add->elements, *current_element = element_to_add;
	// Проверяем, является ли элемент первым в множестве
	if (set_to_add->elements == NULL) 
	{
		// Если да, то выделяем память под него
		// и ставим туда component
		set_to_add->elements = (struct Element*)malloc(sizeof(struct Element));
		component = set_to_add->elements;
	}
	else 
	{
		// Если нет, то спускаемся вниз списка и
		// выделяем память под следующий элемент
		while (component->next_el != NULL) component = component->next_el;
		component->next_el = (struct Element*)malloc(sizeof(struct Element));
		component = component->next_el;
	}

	// Проверяем, является ли добавляемы элемент ячейкой с множеством
	if (is_a_link)
	{
		// Если да, то в component выделяем память под subset 
		// Записываем def и вызываем функцию добавления множества
		component->subset = (struct Element*)malloc(sizeof(struct Element));
		component->def = 1;
		add_sub(component->subset, current_element);
	}
	else if (current_element->subset != NULL)
	{
		// Если да, то в component выделяем память под subset 
		// Записываем def и вызываем функцию добавления множества
		component->subset = (struct Element*)malloc(sizeof(struct Element));
		component->def = current_element->def;
		add_sub(component->subset, current_element->subset);
	}
	// Если нет, то просто переносим информацию из одной ячейки в другую
	else component->simple_el = current_element->simple_el;
}

// Проверка недопустимых символов в именах
// Входные данные:
// sym - символ для проверки
void check_names(char sym)
{
	if (strchr(allowed_symbols, sym) == 0)
	{
		printf("Syntax error!\n");
		exit(1);
	}
}

// Считывание элемента
// Входные данные:
// src - файл для считывания
// location - адрес текущего читающегося элемента
// sym - текущий читающийся символ
void scan_el(FILE* src, struct Element* location, char* sym) 
{
	//Буфер для считывания элемента
	char buff[MAX_LENGTH] = "";
	while (*sym != TERMINATE) 
	{
		switch (*sym)
		{
			case SET_BEGIN: 
				//Создать сабсет, проглотить "{", рекурсивно считать в location->subset всё, что входит в сабсет
				location->subset = (struct Element*)malloc(sizeof(struct Element));
				location->def = 1;
				*sym = fgetc(src);
				set_count++;
				scan_el(src, location->subset, sym);
				break;
			case TUPLE_START:
				//Создать сабсет, проглотить {, рекурсивно считать в location->subset всё, что входит в сабсет
				location->subset = (struct Element*)malloc(sizeof(struct Element));
                location->def = 2;
                *sym = fgetc(src); 
				tuple_count++;                   
				scan_el(src, location->subset, sym);
				break;
			case TUPLE_END:
				//закончить чтение текущего символа после символов-терминаторов.
				//Мы попадём на тот же символ снова, если функция вернулась из рекурсивного вызова
				//в таком случае, считываем следующий символ и идём дальше
				if (strlen(buff) != 0) 
				{
					location->simple_el = (char*)malloc(strlen(buff)+1);
				 	strncat(location->simple_el, buff, strlen(buff)+1);
					*sym = fgetc(src);
					tuple_count--;
	 			 	return;
				}
				else 
				{
					tuple_count--;
				 	*sym = fgetc(src);
				 	return;
				}
			case SET_END: 
				//закончить чтение текущего символа после символов-терминаторов.
				//Если попадаем на закрывающий символ снова, а буфер пуст, значит мы считывали подмножество подмножества
				//в таком случае, считываем следующий символ, возвращаемся из рекурсивной функции и идём дальше
				if (strlen(buff) != 0) 
				{
					location->simple_el = (char*)malloc(strlen(buff)+1);
				 	strncat(location->simple_el, buff, strlen(buff)+1);
					*sym = fgetc(src);
					set_count--;
	 			 	return;
				}
				else 
				{
					set_count--;
					*sym = fgetc(src);
					return;
				}
			case DIVIDE_SYMBOL:
				/* С запятой отдельная ситуация, т.к она является причиной для создания next_el
					В таком случае заканчиваем чтение текущего символа и созаём следующий. Переходим на следующий символ в файле и сканим след.элемент
				*/
				if (strlen(buff) != 0)
				{
					location->simple_el = (char*)malloc(strlen(buff)+1);
					strncat(location->simple_el, buff, strlen(buff)+1);
				}
				*sym = fgetc(src);
				location->next_el = (struct Element*)malloc(sizeof(struct Element));
				scan_el(src, location->next_el, sym);
        		return;
			default:
				check_names(*sym);
				strncat(buff, sym, 1);
				*sym = fgetc(src);
		}
	}
}

// Считывание множества
// Входные данные:
// src - файл для считывания
// st - массив для чтения множеств
// k - количество множеств для прочтения
void scan_set(FILE* src, set* st, int k) 
{
	//выходим, если множеств нет.
	if (k == 0) 
	{
		printf("Syntax error!");
		exit(1);
	} 
	else amount_of_sets = k;
	// Предварительно проверяем весь файл на наличие недопустимых символов ввода
	// два символа нужны, чтобы проверить, нет ли запятых перед\после специальных символов
	char symbol, previous_symbol;
	while (1)
	{
		symbol = fgetc(src);
		if (feof(src)) break;
		if (strchr(allowed_symbols, symbol) == 0 || //если недопустимый символ
		(symbol == DIVIDE_SYMBOL && (previous_symbol == TUPLE_START || previous_symbol == SET_BEGIN)) || //или запятая сразу после открытия множества
		(previous_symbol == DIVIDE_SYMBOL && (symbol == TUPLE_END || symbol == SET_END)) || // или запятая прямо перед закрытием!
		(previous_symbol == TUPLE_END || previous_symbol == SET_END) && (strchr(allowed_name_symbols, symbol) != 0) ||  // или после закрытия множества идёт обычное имя
		((strchr(allowed_name_symbols, symbol) != 0) && (symbol == TUPLE_START || symbol == SET_BEGIN) ) //или в имени встретилось множество
		)
		{
			printf("Syntax error!\n");
			exit(1);
		}
		previous_symbol = symbol;

	}
	fseek(src, 0, SEEK_SET);
	char sym = '\0';
	int i = 0;
	// Запускаем цикл, считывающий k множеств
	while (i < k)
	{
		// Инициализируем множество st[i]
		SetInit(st[i]);
		sym = '\0'; 
		char buff[MAX_LENGTH] = "";
		// Считывание имени множества с проверкой на недопустимые символы в нём
		while ((sym = fgetc(src)) != DEFINE_SYMBOL)
		{
			check_names(sym);
			strncat(buff, &sym, 1);
		}
		st[i].name = (char*)malloc(strlen(buff)+1);
		strncat(st[i].name, buff, strlen(buff)+1);
		// Проверка, что после имени множества идёт само множество
		// Перескакиваем на первый элемент множества
		if ((sym=fgetc(src)) != SET_BEGIN) 
		{
			printf("Syntax error!");
			exit(1);
		}
		sym = fgetc(src);
		set_count++;
		// Выделение памяти под первый эл. множества
		st[i].elements = (struct Element*)malloc(sizeof(struct Element));
		st[i].elements->def = 1;
		// Запишем его адрес в переменную location
		struct Element* location = st[i].elements;
		// Считываем элементы множества
		while (sym != TERMINATE) scan_el(src, location, &sym);
		// Переходим на новое множество
		i++;
		// Проверяем, не нарушена ли вложенность скобок
		if (set_count != 0 || tuple_count != 0)
		{
			printf("Syntax error!");
			exit(1);
		}
    	sym = fgetc(src);
	}
}

// Вывод элементов
// Входные данные:
// el - адрес ячейки текущего элемента
// closing_symbol - показатель характера множества
void print_elements(struct Element* el, int closing_symbol) 
{	
	// Проверяем closing_symbol, определяя является ли элемент множеством
	switch (closing_symbol)
	{
		case 1:
			printf("{");
			break;
		case 2:
			printf("<");
			break;
	}
	// Проверяем, является ли текущий элемент множеством
	// Если да, то рекурсивно печатаем его элементы
	// Если нет, то просто печатаем элемент
	// Дополнительно проверяем, является ли множество пустым
	if (el->subset != NULL) print_elements(el->subset, el->subset->def);
	else if (el->simple_el != NULL) printf("%s", el->simple_el);
	// Если печаталось множество, то закрываем его
	switch (closing_symbol) 
	{
		case 1:
			printf("}");
			break;
		case 2: 
			printf(">");
			break;
	}
	// Если следующий элемент существует, то ставим запятую и печатаем его
	if (el->next_el != NULL)
	{
		printf(",");
		print_elements(el->next_el, el->next_el->def);
		return;
	}
}

// Вывод множества
// Входные данные:
// s - множество для вывода
void print_set(set s)
{
	// Открываем и закрываем начальное множество (символы "{" и "}" )
    printf("%s={", s.name);
    print_elements(s.elements, 0);
	printf("};\n");
}

// Сравнение элементов, являющихся множествами
// Входные данные:
// sets - начальные элементы всех множеств. Необходима для вызова compare_elements
// start_1 - адрес начала первого элемента
// start_2 - адрес начала второго элемента
// type_of_sub - характер множества (ориентированное или неориентированное)
int compare_subs(set* sets, struct Element* start_1, struct Element* start_2, int type_of_sub)
{
	//если оба (подмножества) пусты - они одинаковы.
	//if такой большой, потому что надо проверить, что в подмножестве нет элементов (т.е simple_el и subset пусты)
	if ( (start_1 == NULL || (start_1->simple_el == NULL && start_1->subset == NULL) ) && (start_2 == NULL || (start_2->simple_el == NULL && start_2->subset == NULL) ) ) return 1;
	//если одно (подмножество) пустое, а другое нет - не одинаковы
	else if ((start_1 == NULL || (start_1->simple_el == NULL && start_1->subset == NULL) ) || (start_2 == NULL || (start_2->simple_el == NULL && start_2->subset == NULL) )) return 0;
	struct Element* location_1 = start_1;
	struct Element* location_2 = start_2;
	int number_of_entries = 0, number_of_same_elements = 0;
	// Если сравниваем неориентированнаые множества, то
	// Два множества равны, когда их мощности одинаковы и
	// Для любого элемента из первого множества есть равный элемент во втором
	// Т.е. number_of_entries == number_of_same_elements
	if (type_of_sub == 1)
	{
		//проверяем, есть ли каждый элемент первого множества...
		while(location_1 != NULL)
		{
			number_of_entries++;
			int found_in_second_set=0;
			//...во втором множестве.
			while(location_2 != NULL) {
				if(compare_elements(sets, location_1, location_2)) 
				{
					//если нашли, выходим из цикла по второму множеству
					number_of_same_elements++;
					found_in_second_set=1;
					break;
				}
				//если не нашли, ищем дальше по второму множеству
				location_2 = location_2->next_el;
			}
			//если нет, множества не могут быть равными, выходим.
			if (!found_in_second_set) return 0;
			//если всё-таки есть соответствие, проверяем следующий элемент первого множества 
			location_1 = location_1->next_el;
		}
		if (number_of_entries == number_of_same_elements) return 1;
		else return 0;
	}
	else if (type_of_sub == 2)
	{
		while (location_1 != NULL && location_2 != NULL)
		{
			// Сравниваем два элемента и, если они равны, переходим на следующие
			// Если нет, то кортежи не равны
			if (compare_elements(sets, location_1, location_2))
			{
				location_1 = location_1->next_el;
				location_2 = location_2->next_el;
			}
			else return 0;
		}
		// Проверяем, что оба кортежа одной длины
		if (location_1 == NULL && location_2 == NULL) return 1;
		else return 0;
	}
	return 0;
}

//выясняет, является ли имя указателем на множество
//sets - объект со всеми первыми элементами множеств
//name - имя, которое мы ищем
//result - указатель на Element, куда нужно записать первый элемент множества. Если такого множества нет, то =NULL
struct Element* find_set_by_name(set* sets, char* name) {
	for(int i=0; i<amount_of_sets; i++)
	{
		if (strcmp(sets[i].name,name) == 0) 
		{
			return sets[i].elements;
		}
	}
	return NULL;
}


// Сравнение элементов
// Входные данные:
// set_1 - множество, содержащее первый элемент
// set_2 - множество, содержащее второй элемент
// location_1 - адрес первого элемента
// location_2 - адрес второго элемента
int compare_elements(set* sets, struct Element* location_1, struct Element* location_2)
{
	//если оба элемента пусты, вернуть, что они одинаковы
	if (location_1 == NULL && location_2 == NULL) return 1;
	//если они не одновременно null, но один из них null, то они отличаются :D
	if (location_1 == NULL || location_2 == NULL) return 0;

	// Проверяем, являются ли location_1 и location_2 адресами начала элементов-множеств. Если да, сравниваем элементы-множества
	if (location_1->subset != NULL && location_2->subset != NULL && location_1->def == location_2->def) 
		return compare_subs(sets, location_1->subset, location_2->subset, location_1->def);

	// Если нет, то сравниваем элементы, но тогда надо понять, какие типы у обоих элементов
	// есть 4 варианта: имя-имя, имя-подмножество, подмножество-имя, подмножество-подмножество (уже проверили выше). Проверяем в порядке сложности
	if (location_1->simple_el != NULL || location_2->simple_el != NULL)		
	{
		//сначала проверим, являются ли location_1->simple_el и location_2->simple_el ссылками на множества
		struct Element *set1 = NULL, *set2 = NULL;
		if (location_1->simple_el != NULL) set1 = find_set_by_name(sets, location_1->simple_el);
		if (location_2->simple_el != NULL) set2 = find_set_by_name(sets, location_2->simple_el);

		//вариант 1: имя-имя
		if (location_1->simple_el != NULL && location_2->simple_el != NULL) 
		{
		
			//Если simple_el одинаковые, то элементы одинаковые
			if (strcmp(location_1->simple_el, location_2->simple_el) == 0) return 1;

			//если нет, то сравниваем множества, на которые указывают simple_el
			else 
			{
				if(set1 != NULL && set2 != NULL) return compare_subs(sets, set1, set2, 1);
				//если оба имени не пусты, но при этом не оба имени указывают на множества, они по определению равны быть не могут
				else return 0;
			}

 
		}

		//вариант 2-3: имя и множество\множество и имя.
		if (set1 != NULL && location_2->def == 1 && location_2->subset != NULL) return compare_subs(sets, set1, location_2->subset, 1);
		else if (set2 != NULL && location_1->def == 1 && location_1->subset != NULL) return compare_subs(sets, set2, location_1->subset, 1);

		//если так вышло, что оба имени никуда не указывают, или вы сравниваете множество с кортежем, то элементы равны не будут
		else return 0;


	}
	return 0;
}

void dfs(set* sets, set* set_1, set* set_2)
{
    // location - адрес элемента первого множества
	struct Element* location_1 = set_1->elements;
	struct Element* location_2 = set_2->elements;
	int found_in_set = 0;

	//для каждого элемента в множестве 0. цикл 1
    while (location_2 != NULL)
	{
		location_1 = set_1->elements;
		while(location_1 != NULL)
		{
			if (compare_elements(sets, location_1, location_2))
			{
				found_in_set = 1;
				break;
			}
			if (location_1->next_el != NULL) location_1 = location_1->next_el;
				else break;
		}
		if (found_in_set == 0) add(set_1, location_2, 0);
		else found_in_set = 0;
		location_2 = location_2->next_el;
	}
}