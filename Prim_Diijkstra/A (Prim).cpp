#include <iostream>
#include <vector>
#include <climits>
using namespace std;

#define MAX 100

struct no{
	int v;
	int peso;   	
};

struct grafo{
	int n_vertices;
	int n_arestas;
	vector <no> adj[MAX];
};

void cria_aresta(grafo &G, int u, int v, int peso, bool direcionado)
{
	no aux; // variavel auxiliar
	aux.v = v; // vertice de destinoo
	aux.peso = peso; // peso da aresta
	G.adj[u].push_back(aux); // Adiciona a aresta auxiliar na lista de adj. de u
	
	if (direcionado == false) // Se a aresta nao eh direcionada
	{
		cria_aresta(G,v,u,peso,true); // Cria uma aresta no sentido inverso
	}
}

// Encontra a árvore geradora mínima (MST - Minimal Spanning Tree)
void prim(grafo &GRAFO, int v_inicio)
{
	int custo_total = 0;
	bool na_arvore[GRAFO.n_vertices];
	int distancia[GRAFO.n_vertices];
	int pai[MAX];
	int v_atual;
	int v;
	int peso;
	int dist;

	// no inicio...
	for(int i = 0; i < GRAFO.n_vertices;i++)
	{
		na_arvore[i] = false; // ...todos estao fora da arvore geradora minima (MST)
		distancia[i] = INT_MAX;// a distancia de todos para a MST eh INFINITA
		pai[i] = -1; // ninguem tem pai
	}

	distancia[v_inicio] = 0; // distancia do vertice inicial para a arvore eh 0 (ele vai ser o primeiro a ser colocado na arvore)
	v_atual = v_inicio;

	while(na_arvore[v_atual] == false) // enquanto houver um vertice fora da arvore geradora minima
	{
		na_arvore[v_atual] = true; // adiciona o vertice atual na arvore
		custo_total = custo_total + distancia[v_atual]; // adiciona o peso da aresta que ligou o vertice a arvore(se for o primeiro, o custo sera 0)

		for(int i = 0;i < GRAFO.adj[v_atual].size();i++) // varrendo a lista de adj.s do vertice atual( para encontrar possiveis distancias menores da arvore para outros vertices)
		{
			v = GRAFO.adj[v_atual][i].v;
			peso = GRAFO.adj[v_atual][i].peso;

			if((distancia[v] > peso) && (na_arvore[v] == false))
			{

				distancia[v] = peso;
				pai[v] = v_atual;

			}

		}
		v_atual = 0;
		dist = INT_MAX;

		for(int i = 0;i < GRAFO.n_vertices;i++) // descobrindo qual o vertice esta mais proximo da arvore
		{

			if((na_arvore[i] == false) && (dist > distancia[i]))
			{
				dist = distancia[i];
				v_atual = i;

			}

		}
	}
	cout << "Custo total = " << custo_total << endl;

}



int main()
{
	grafo G;
	
	cin >> G.n_vertices >> G.n_arestas;
	
	int ui, vi, di;
	
	for(int i=1; i<=G.n_arestas; i++)
	{
		cin>>ui>>vi>>di;
		cria_aresta(G,ui,vi,di,0);
	}
	
	prim(G,ui);
	return 0;
}
