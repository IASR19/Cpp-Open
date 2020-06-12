#include <iostream>
#include <cmath> 
#include <vector>
#include <stack>
#include <algorithm>
#include <iomanip>

using namespace std;

struct ponto
{
	int x; 
	int y;
};

typedef ponto vetor;


double vetorial(vetor A, vetor B)
{
	return (A.x * B.y - B.x * A.y);
}


vetor cria_vetor(ponto A, ponto B)
{
	vetor AB;
	AB.x = B.x - A.x;
	AB.y = B.y - A.y;
	return AB;
}


int sentido(ponto A, ponto B, ponto C)
{
	vetor AB, AC;
	double resultado;
	AB = cria_vetor(A, B);
	AC = cria_vetor(A, C);
	resultado = vetorial(AB, AC);
	if(resultado > 0)
		return 1;
	else if(resultado < 0)
		return -1;
	else
		return 0;
}

ponto next_to_top(stack <ponto> pilha)
{
	pilha.pop();
	return pilha.top();
}


bool cmp(ponto a, ponto b)
{
	double angA = atan2(a.y, a.x);
	double angB = atan2(b.y, b.x);
	if(angA == angB)
	{
		double distA = hypot(a.x, a.y);
		double distB = hypot(b.x, b.y);
		return distA > distB;
	}
	else
		return angA < angB;
}




stack <ponto> Graham_scan(vector <ponto> pontos)
{
	stack <ponto> pilha;
	ponto pivot;
	pivot = pontos[0];

	for(int i = 1; i < pontos.size(); i++)
	{
		if(pontos[i].y < pivot.y || pontos[i].y == pivot.y && pontos[i].x < pivot.x)
		{
			pivot = pontos[i];
		}
	}
	for(int i = 0; i < pontos.size(); i++)
	{
		if(pivot.x == pontos[i].x && pivot.y == pontos[i].y)
		{
			swap(pontos[i], pontos[0]);
		}
	}

	for(int i = 0; i < pontos.size(); i++)
	{
		pontos[i].x = pontos[i].x - pivot.x;
		pontos[i].y = pontos[i].y - pivot.y;
	}

	sort(pontos.begin() + 1, pontos.end(), cmp);

	for(int i = 0; i < pontos.size(); i++)
	{
		pontos[i].x = pontos[i].x + pivot.x;
		pontos[i].y = pontos[i].y + pivot.y;
	}

	pilha.push(pontos[0]);
	pilha.push(pontos[1]);
	pilha.push(pontos[2]);
	int i = 3;
	while(i < pontos.size())
	{
		if(sentido(next_to_top(pilha), pilha.top(), pontos[i]) == 1) 
		{
			pilha.push(pontos[i]); 
			i++;
		}
		else  
		{
			pilha.pop();
		}
	}
	return pilha;
}


int main()
{
	cout << fixed << setprecision(2);
	vector <ponto> pontos;
	stack <ponto> pilha;
	stack <ponto> pilhaAuxiliar;
	ponto Vaux;
	ponto conta_lado;
	ponto AB;

	double aresta, valor_real = 0;
	int N, x = 0, j = 1;

	cin >> N;

	for(int i = 0; i < N; i++)
	{
		cin >> Vaux.x >> Vaux.y;
		pontos.push_back(Vaux);
	}

	pilha = Graham_scan(pontos);
	pilhaAuxiliar = pilha;

	conta_lado = pilha.top();

	while(!pilhaAuxiliar.empty())
	{
		pilhaAuxiliar.pop();
		x++;
	}

	while( j < x )
	{
		Vaux = next_to_top(pilha);

		AB.x = pilha.top().x - Vaux.x;
		AB.y = pilha.top().y - Vaux.y;

		aresta = pow(pow(AB.x, 2) + pow(AB.y, 2), 0.5);

		valor_real = valor_real + aresta;

		pilha.pop();

		j++;
	}

	AB.x = conta_lado.x - pilha.top().x;
	AB.y = conta_lado.y - pilha.top().y;
	aresta = pow(pow(AB.x, 2) + pow(AB.y, 2), 0.5);

	valor_real = valor_real + aresta;

	cout << valor_real << " m";
}