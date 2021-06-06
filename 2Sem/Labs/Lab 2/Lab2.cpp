#include <iostream>
#include <fstream>
#define inf 100000
#define _inf -10000

using namespace std;

int min(int, int);

int main()
{
    ifstream fin("cicle.in");                                   //Input
    int n;
    fin >> n;
    int **matx = new int*[n];
    for (int i = 0; i < n; i++) matx[i] = new int[n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        fin >> matx[i][j];
    fin.close();
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (matx[i][k] < inf && matx[k][j] < inf)
                matx[i][j] = min(matx[i][j], matx[i][k] + matx[k][j]);
            }
        }
    }
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (matx[i][k] < inf && matx[k][k] < 0 && matx[k][j] < inf)
                matx[i][j] = _inf;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) printf("%10d", matx[i][j]);
        cout << endl;
    }
    
    ofstream fout("cicle.out");                                 //Output
    int k = 0, pos = 0;
    for (int i = 0; i < n; i++)
        if (matx[i][i] == _inf)
        {
            pos = i;
            break;
        }
    for (int i = 0; i < n; i++)
    if (matx[i][pos] == _inf) ++k;
    if (k) fout << "YES\n" << ++k << '\n';
        else fout << "NO\n";
    for (int i = pos; i < n; i++) if (matx[i][pos] == _inf) fout << i + 1 << ' ';
    if (k) fout << pos + 1;
    fout.close();
    return 0;
}


int min (int a, int b)
{
    return (a < b)? a : b;
}