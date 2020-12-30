#define _CRT_SEvE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <locale.h>
#include <iostream> 
#include <vector>
#include <time.h>
#include <stack>
#include <string>
#include <limits>
#include <queue> 
using namespace std;

void BFS(int st, int N);
void BFS_LIST(int st);
void BFS_MY(int st, int N);
int** graph;
int* vis;
int* vis3;
int* qq;
int N, i, j, st, v;
using Edge = int;						// ребро - целое число, указывающее, куда её ведут
using Vertex =  vector<Edge>;			// вершина - набор рёбер
using Graph =  vector<Vertex>;			// граф - набор вершин
Graph graph_1;
vector<bool> visited;					// посещённые вершины 
queue <int> Q;


void BFS(int st, int N)
{
	int r;
	Q.push(st);
	vis[st] = true;
	while (!Q.empty())
	{
		st = Q.front();
		Q.pop();
		printf("%d ", st + 1);
		for (r = 0; r < N; r++)
			if ((graph[st][r] != 0) && (vis[r] == 0))		// ребро существует и вершина не посещена
			{
				Q.push(r);
				vis[r] = true;
			}
	}
}
void BFS_LIST(int st)
{
	queue<int> q;
	q.push(st);											 //в качестве начальной вершины используем введённую
	visited[st] = true;

	while (!q.empty()) 
	{
		v = q.front();									//извлекаем из очереди текущую вершину
		q.pop();
		printf("%d ", v + 1);

		for ( int a : graph_1[v])						//добавляем всех непосещённых
		{    
			if (!visited[a])
			{
				q.push(a);
				visited[a] = true;
			}
		}
	}
}
void BFS_MY(int st, int N)
{	
	int first = 0;
	int last = 0;
	qq[last] = st;
	last++;
	vis[st] = true;
	while (last != first) 
	{
		st = qq[first];
		first++;
		printf("%d ", st + 1);
		for (j = 0; j < N; j++) 
		{
			if ((graph[st][j] == 1) && (vis[j] != 1))
			{
				qq[last] = j;
				last++;
				vis[j] = 1;
			}
		}
	}
}

void main() 
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));
	printf("\n Введите размер матрицы: ");
	scanf_s("%d", &N);
	printf("\n");
	graph = new int* [N];

	for (int i = 0; i < N; i++)
	{
		graph[i] = new int[N];
	}

	vis = new int[N];
	qq = new int[N];
	vis3 = new int[N];

	int ch = 0;
	for (i = 0; i < N; ++i)
	{
		for (j = i; j < N; ++j)
		{
			graph[i][j] = graph[j][i] = rand() % 2;
			graph[i][i] = graph[j][j] = 0;						//Чтобы не было возврата
		}
	}
	printf("   ");

	for (j = 0; j < N; j++)
	{
		printf("%4d  ", j + 1);									//горизонталь
	}
	printf("\n\n");

	for (i = 0; i < N; i++) 
	{

		printf(" %d ", i + 1);									// вертикаль

		for (j = 0; j < N; j++)
		{
			printf("%4d  ", graph[i][j]);
		}
		printf("\n\n");
	}

	graph_1.resize(N);											//размер графа
	for (int i = 0; i < N; i++)									//заполнение матрицами
	{
		for (int j = 0; j < N; j++)
		{
			if (graph[i][j] == 1)
				graph_1[i].push_back(j);
		}
	}
	printf("\n");

	for (int i = 0; i < graph_1.size(); i++)					// вывод списка
	{
		 printf(" Вершина %d смежна с ",i + 1);
		for (int j = 0; j < graph_1[i].size(); j++)
		{
			printf(" %d", graph_1[i][j] + 1);
		}
		printf(" \n");
	}

	for (int i = 0; i < N; i++)									
		vis[i] = 0;												//отмена посещения
	printf(" \n");

	printf("\n Выберите вершину  ");
	scanf_s("%d", &st);
	
	printf("\n Результат обхода в ширину матрицы через класс queue\n ");
	clock_t start1 = clock();
	BFS(st-1, N);
	clock_t end1 = clock();
    printf(" %.3f мс\n", difftime(end1, start1));

	printf("\n\nРезультат обхода в ширину списка смежности\n ");
	visited.resize(N);

	for (int i = 0; i < N; i++) 
	{
		visited[i] = 0; 
	}
	 
	clock_t start3 = clock();
	BFS_LIST(st - 1);
	clock_t end3 = clock();
	printf(" %.3f мс\n", difftime(end3, start3));

	for (int i = 0; i < N; i++) 
	{
		vis[i] = 0;												//отмена посещения
	}

	printf("\n\n Результат обхода в ширину матрицы через самостоятельно очередь\n ");

	for (int i = 0; i < N; i++) 
		vis3[i] = 0;											//отмена посещения

	clock_t start2 = clock();
	BFS_MY(st-1, N); 
	clock_t end2 = clock();
	printf(" %.3f мс\n", difftime(end2, start2));

	system("pause");
}
