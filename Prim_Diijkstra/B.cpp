#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <stack>

#define MAX 100
using namespace std;

struct no
{
	int v;
	int peso;
};

struct grafo
{
	int n_vertices;
	int n_arestas;
	vector <no> adj[MAX];
};

void cria_aresta(grafo &G, int u, int v, int peso, bool direcionado)
{
	no nova_aresta;
	nova_aresta.v = v;
	nova_aresta.peso = peso ;
	G.adj[u].push_back(nova_aresta);
	if(!direcionado)
	{
		cria_aresta(G, v, u, peso, true);
	}
}

void mostra_cami_per(int pai[], int v_fim)
{
	stack <int> pilha;
	int aux;

	aux = v_fim;

	while(aux != -1)
	{
		pilha.push(aux);
		aux = pai[aux];
	}

	while(!pilha.empty())
	{
		cout << pilha.top() << " ";
		pilha.pop();
	}
	cout << endl;

}

int dijkstra(grafo G, int v_ini, int v_fim)
{
	int distancia[G.n_vertices];
	int pai[G.n_vertices];
	int vis[G.n_vertices];
	int u;
	int dist;
	bool cami_per = false;
	for(int i = 0; i < G.n_vertices; i++)
	{
		vis[i] = 0;
		pai[i] = -1;
		distancia[i] = INT_MAX;
	}
	distancia[v_ini] = 0;
	u = v_ini;
	while(!vis[u])
	{
		vis[u] = 1;

		for(int i = 0; i < G.adj[u].size(); i++)
		{
			int v = G.adj[u][i].v;
			if(v == v_fim)
				cami_per = true;
			int custo = G.adj[u][i].peso;
			if(distancia[v] > distancia[u] + custo)
			{
				distancia[v] = distancia[u] + custo;
				pai[v] = u;
			}
		}

		u = 0;
		dist = INT_MAX;

		for(int i = 0; i < G.n_vertices; i++)
		{
			if(!vis[i] && dist > distancia[i])
			{
				u = i;
				dist = distancia[i];
			}
		}
	}

	if(cami_per)
	{
		cout << distancia[v_fim] << endl;
		mostra_cami_per(pai, v_fim);
	}
	return distancia[v_fim];

}

void deleta_grafo(grafo &G)
{
	for(int i = 0; i < G.n_vertices; i++)
	{
		G.adj[i].clear();
	}
	G.n_vertices = 0;
	G.n_arestas = 0;
}

int main()
{
	int V;
	int L;
	int S;
	int Ci;
	int Di;
	int T;
	bool cami_per = false;
	grafo G;

	cin >> T;

	for(int i = 1; i <= T; i++)
	{
		cin >> G.n_vertices;

		for(int j = 0; j < G.n_vertices; j++)
		{
			cin >> S;

			for(int k = 0; k < S; k++)
			{
				cin >> Ci;
				cin >> Di;
				cria_aresta(G, j, Ci, Di, false);
			}
		}

		cin >> V;
		cin >> L;

		cout << endl;
		cout << "Caso #" << i << endl;
		dijkstra(G, V, L);

		deleta_grafo(G);
	}
	return 0;
}
