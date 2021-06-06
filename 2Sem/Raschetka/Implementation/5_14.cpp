#include <iostream>
#include <stdlib.h>
#include <vector>

std::vector<std::vector<int>> graph;    //Массив для хранения СС графа
/* used - отметка посещена вершина или нет,
   tin - время входа поиска в глубину в вершину u,
   up - минимум из времени захода в саму вершину tin[u], времен захода 
   в каждую из вершин p, являющуюся концом некоторого обратного ребра (u,p), 
   а также из всех значений up[v] для каждой вершины v, являющейся 
   непосредственным сыном u в дереве поиска.*/
std::vector<int> used, tin, up;
//output - файл вывода
FILE* output = fopen("result.txt", "w+t");
int timer;

void dfs (int, int = -1);

int main (int argc, char* argv[])
{
    /* n - количество вершин графа,
       m - количество рёбер графа */
    int n, m;
    char sym;
    //input - файл ввода
    FILE* input = fopen(argv[1], "r");
    fscanf(input, "%d %d", &n, &m);
    graph.resize(n+1); used.resize(n+1);
    tin.resize(n+1); up.resize(n+1);
    int i = 0, j = 0;
    //Считываем СС в массив graph
    while (i < m)
	{
		graph.push_back(std::vector<int>());
		j = 0;
		while ((sym = fgetc(input)) != '\n') 
		{
			if (feof(input)) break;
			if (sym != ' ') graph[i].push_back(atoi(&sym));
		}
		i++;
	}
    fclose(input);
    timer = 1;
    //Запускаем DFS из каждой ещё не просмотренной вершины
    for(int u = 1; u <= n; u++)
    if (!used[u]) dfs(u);
    fclose(output);
    return 0;
}


//Функция поиска минимального из двух элементов
int min (int a, int b)
{
    return (a < b)? a : b;
}


/* Функция поиска в глубину, где
   v - вершина начала поиска,
   p - конец обратного ребра (v,p) */
void dfs (int v, int p)
{
    /* to - некоторый потомок вершины v,
       children - количество потомков вершины v*/
    int to, children;
    //Отмечаем вершину v как посещённую
    used[v] = true;
    tin[v] = up[v] = timer++;
    children = 0;
    /* Просматриваем все вершины to, являющиеся потомками вершины v.
       Возможны три случая:
       1. (v, to) ребро дерева, просматриваемое в обратном направлении (т.е. to = p)
       2. (v, to) обратное ребро (т.е. used[to] = 1 и to ≠ p)
       3. (v, to) ребро дерева (т.е. used[to] = 0)*/
    for (int i = 0; i < graph[v].size(); i++)
    {
        //to присвоим ребро номер i
        to = graph[v][i];
        //Если встречено обратное ребро, то пропускаем его
        if (to == p)  continue;
        //Если вершина to уже посещена, то (v, to) обратное ребро. Пересчитаем значение up[v].
        if (used[to]) up[v] = min (up[v], tin[to]);
        else
        {
            //Если встречен случай 3, то запускаем DFS из вершины to
            dfs (to, v);
            //Пересчитываем значение up[v]
            up[v] = min (up[v], up[to]);
            //Если up[to] >= tin[v] и v не является корнем, то v - точка сочленения
            if ((up[to] >= tin[v]) && (p != -1)) fprintf (output, "%d\n", v);
            children++;
        }
    }
    //Если v - корень и у него больше одного потомка, то v - точка сочленения
    if ((p == -1) && (children > 1)) fprintf (output, "%d\n", v);
}