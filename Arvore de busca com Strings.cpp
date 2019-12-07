#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

typedef struct No
{
	string info;
	struct No* esq;
	struct No* dir;
} arvore;

arvore* criar(string info, arvore* esq, arvore* dir)
{
	arvore* arv = new arvore;
	arv->info = info;
	arv->esq = esq;
	arv->dir = dir;

	return arv;
} // inicializacao da árvore.

arvore* destruir(arvore* arv)
{
	if(arv != NULL)
	{
		destruir(arv->esq);
		destruir(arv->dir);

		delete arv;
	}
	return NULL;
} // destroi a árvore.
int maiorIgual(string onde, string oQue)
{
	// cout << "Comparando as palavras " << oQue << " e " << onde << ".\n";
	int aux;

	if(onde.size() < oQue.size())
	{
		aux = onde.size();
		// cout << "A palavra " << onde << " tem menos letras.\n";
	}
	else
	{
		aux = oQue.size();
		if(onde.size() > oQue.size())
		{
			// cout << "A palavra " << oQue << " tem menos letras.\n";
		}
		else
		{
			// cout << "As palavras tem a mesma quantidade de letras.\n";
		}

	}

	for(int i = 0; i < aux; i++)
	{
		if(int(onde[i]) > int(oQue[i]))
		{
			return 0; // retorna 0 para valor onde menor
		}
		else if(int(onde[i]) < int(oQue[i]))
		{
			return 1; // retorna 1 para valor oQue menor
		}
	}

	return 2; // retorna 2 para caso de palavras iguais
}

void contador(arvore* arv, int& contadorFolhas, int& contadorNos)
{
	if(arv == NULL)
	{
		return;
	}

	// Incrementa os Nós

	contadorNos++;

	if(arv->dir == NULL && arv->esq == NULL)
	{
		// Incrementa Folhas

		contadorFolhas++;
	}

	contador(arv->esq, contadorFolhas, contadorNos);
	contador(arv->dir, contadorFolhas, contadorNos);
}

arvore* buscar(arvore* arv, string v)
{
	if(arv == NULL)
	{
		cout << "Elemento nao encontrado!\n";

		return NULL;
	}
	else
	{
		switch(maiorIgual(arv->info, v))
		{
		case 0:
			cout << "saindo de " << arv->info << " buscando na esquerda" << endl;

			return buscar(arv->esq, v);

			break;
		case 1:
			cout << "saindo de " << arv->info << " buscando na direita" << endl;

			return buscar(arv->dir, v);

			break;
		default:
			cout << "achei! " << arv->info << endl;

			return arv;

			break;
		}
	}
} // busca de um elemento na árvore
arvore* inserir(arvore* arv, string v)
{
	cout << "inserindo elemento: " << v << endl;
	if(arv == NULL)
	{
		arv = criar(v, NULL, NULL);
		cout << "criando arvore" << endl;
	}
	else
	{
		switch(maiorIgual(arv->info, v))
		{
		case 0:
			cout << "inserindo na esquerda" << endl;
			arv->esq = inserir(arv->esq, v);

			break;
		default:
			cout << "inserindo na direita" << endl;
			arv->dir = inserir(arv->dir, v);

			break;
		}
	}

	return arv;
} // inserção de um elemento na árvore.
arvore* remover(arvore* arv, string v)
{
	cout << "Buscando elemento: " << v << " para remocao" << endl;
	if(arv == NULL)
	{
		cout << "Elemento para remocao nao encontrado!" << endl;
		return NULL;
	}
	else // Caso encontrou o elemento para remoção
	{
		switch(maiorIgual(arv->info, v))
		{
		case 0: // Valor a ser removido eh menor que o do Nó atual. Subarvore da esquerda
			cout << "saindo de " << arv->info << " buscando na esquerda" << endl;
			arv->esq = remover(arv->esq, v);
			break;
		case 1: // Valor a ser removido eh maior que o do Nó atual. Subarvore da direita
			cout << "saindo de " << arv->info << " buscando na direita" << endl;
			arv->dir = remover(arv->dir, v);
			break;
		default: // Encontrou o Nó a remover
			if(arv->esq == NULL && arv->dir == NULL) // Caso 1: no sem filhos
			{
				cout << "estou em " << arv->info << " caso 1: nao tem filhos" << endl;
				delete arv;
				arv = NULL;
			}
			// Caso 2: Nó só tem um filho
			else if(arv->esq == NULL) // Caso 2.1: Só tem o filho da esquerda
			{
				cout << "estou em " << arv->info << " caso 2.1: soh tem filhos maiores" << endl;
				arvore* aux = arv;
				arv = arv->dir;
				delete aux;
			}
			else if(arv->dir == NULL) // Caso 2.2: Só tem o filho da direita
			{
				cout << "estou em " << arv->info << " caso 2.2: so tem filhos menores" << endl;
				arvore* aux = arv;
				arv = arv->esq;
				delete aux;
			}
			else // Caso 3: Nó tem dois filhos
			{
				cout << "estou em " << arv->info << " caso 3: tem dois filhos" << endl;
				arvore* aux = arv->esq;
				cout << "buscando maior valor da subarvore pela esquerda" << endl;
				while (aux->dir != NULL)
				{
					aux = aux->dir;
				}
				cout << "trocando " << aux->info << " por " << v << endl;
				arv->info = aux->info;
				aux->info = v;
				arv->esq = remover(arv->esq, v);
			}
			break;
		}
	}
	return arv;
} // remove um elemento da arvore.
bool estaVazia(arvore* arv) // Booleano para vazio ou nao
{
	if(arv == NULL)
	{
		cout << "A arvore esta vazia!" << endl;
	}
	else
	{
		cout << "A arvore nao esta vazia!" << endl;
	}
	return arv == NULL;
} // retorna um booleano indicando se a árvore está vazia.
bool ehEstritamenteBinaria(arvore* arv)
{
	if(arv == NULL)
	{
		cout << "Erro, arvore inexistente" << endl;
		return false;
	}
	else if(arv->esq == NULL && arv->dir == NULL)
	{
		return true;
	}
	else if(arv->esq != NULL && arv->dir != NULL)
	{
		return (ehEstritamenteBinaria(arv->esq) && ehEstritamenteBinaria(arv->dir));
	}
	else
	{
		return false;
	}
} // retorna um booleano indicando se a árvore é estritamente binária.
bool ehQuaseCompleta(arvore* arv) // Parametro adicional valor
{
	int contagemFolhas = 0;
	int contagemNos = 0;

	contador(arv, contagemFolhas, contagemNos);

	// Não Estrita.
	if(contagemFolhas % 2 == 0 && 2 * contagemFolhas == contagemNos - 1)
	{
		// É quase completa
		return true;
	}
	// Estritamente Binária
	else if(contagemFolhas % 2 != 0 && 2 * contagemFolhas - 1 == contagemNos - 1)
	{
		// É quase completa
		return true;
	}
	return false;
} // retorna um booleano indicando se a árvore é quase completa.
bool ehCompletaCheia(arvore* arv)
{
	if(arv == NULL)
	{
		cout << "Erro, arvore inexistente" << endl;
		return false;
	}
	else if(arv->esq != NULL && arv->dir != NULL)
	{
		return (ehCompletaCheia(arv->esq) && ehCompletaCheia(arv->dir));
	}
	else if(arv->esq == NULL && arv->dir == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
} // retorna um booleano indicando se a árvore é completa (cheia).
void preOrdem(arvore* arv)
{
	if(arv == NULL)
	{
		return;
	}
	cout << arv->info << endl;
	preOrdem(arv->esq);
	preOrdem(arv->dir);
} // visita e imprime os elementos da árvore em PRÉ-ORDEM (“RED”).
void emOrdem(arvore* arv)
{
	if(arv == NULL)
	{
		return;
	}
	emOrdem(arv->esq);
	cout << arv->info << endl;
	emOrdem(arv->dir);
} // visita e imprime os elementos da árvore EM-ORDEM (“ERD”).

void posOrdem(arvore* arv)
{
	if(arv == NULL)
	{
		return;
	}
	posOrdem(arv->esq);
	posOrdem(arv->dir);
	cout << arv->info << endl;
} // visita e imprime os elementos da árvore em PÓS-ORDEM (“EDR”).


void menu()
{
	bool sair = false;
	int opcao;
	string valor;

	cout << "--------------\n" << endl;
	cout << "Uma arvore foi criada!" << endl;
	cout << "--------------\n" << endl;

	arvore* arv = NULL;

	while(!sair)
	{
		cout << "--------------" << endl;
		cout << "MENU\n" << endl;
		cout << "1. Inserir novo elemento na arvore" << endl;
		cout << "2. Remover elemento da arvore" << endl;
		cout << "3. Verificar se um elemento esta na arvore" << endl;
		cout << "4. Verificar se a arvore esta vazia" << endl;
		cout << "5. Imprimir PreOrdem" << endl;
		cout << "6. Imprimir EmOrdem" << endl;
		cout << "7. Imprimir PosOrdem" << endl;
		cout << "8. Estritamente binaria?" << endl;
		cout << "9. Quase completa?" << endl;
		cout << "10. Completa?" << endl;
		cout << "0. Sair" << endl;
		cout << "\nEntre com a opcao desejada: ";
		cin >> opcao;
		switch(opcao)
		{
		case 1:
			system("cls");
			// 1. Inserir novo elemento na arvore
			cout << "Insira o novo elemento: ";
			cin >> valor;
			arv = inserir(arv, valor);
			break;
		case 2:
			system("cls");
			// 2. Remover elemento da arvore
			cout << "Insira o elemento a ser removido: ";
			cin >> valor;
			arv = remover(arv, valor);
			break;
		case 3:
			system("cls");
			// 3. Verificar se um elemento está na arvore
			cout << "Pesquisar elemento: ";
			cin >> valor;
			if(buscar(arv, valor))
			{
				cout << "--------------" << endl;
				cout << "O elemento esta na arvore, meu querido!" << endl;
				cout << "--------------" << endl;
			}
			else
			{
				cout << "--------------" << endl;
				cout << "O elemento NAO esta na arvore, vacilao!" << endl;
				cout << "--------------" << endl;
			};
			break;
		case 4:
			system("cls");
			// 4. Verificar se a arvore está vazia
			if(estaVazia(arv))
			{
				cout << "--------------" << endl;
				cout << "A arvore esta vazia :(" << endl;
				cout << "--------------" << endl;
			}
			else
			{
				cout << "--------------" << endl;
				cout << "A arvore NAO esta vazia :)" << endl;
				cout << "--------------" << endl;
			};
			break;
		case 5:
			system("cls");
			// 5. visita e imprime os elementos da árvore em PRÉ-ORDEM (“RED”).
			cout << "--------------" << endl;
			cout << "Imprimindo em PRE-Ordem" << endl;
			cout << "--------------" << endl;
			preOrdem(arv);
			break;
		case 6:
			system("cls");
			// 6.  visita e imprime os elementos da árvore EM-ORDEM (“ERD”).
			cout << "--------------" << endl;
			cout << "Imprimindo em EM-Ordem" << endl;
			cout << "--------------" << endl;
			emOrdem(arv);
			break;
		case 7:
			system("cls");
			// 7.  visita e imprime os elementos da árvore PÓS-ORDEM (“EDR”).
			cout << "--------------" << endl;
			cout << "Imprimindo em POS-Ordem" << endl;
			cout << "--------------" << endl;
			posOrdem(arv);
			break;
		case 8:
			system("cls");
			// 8. Verificar se a arvore é estritamente binária
			if(ehEstritamenteBinaria(arv))
			{
				cout << "--------------" << endl;
				cout << "A arvore eh estritamente binaria :)" << endl;
				cout << "--------------" << endl;
			}
			else
			{
				cout << "--------------" << endl;
				cout << "A arvore NAO eh estritamente binaria :(" << endl;
				cout << "--------------" << endl;
			};
			break;
		case 9:
			system("cls");
			// 9. Verificar se a arvore é quase completa
			if(ehQuaseCompleta(arv))
			{
				cout << "--------------" << endl;
				cout << "A arvore eh quase completa :)" << endl;
				cout << "--------------" << endl;
			}
			else
			{
				cout << "--------------" << endl;
				cout << "A arvore NAO eh quase completa :(" << endl;
				cout << "--------------" << endl;
			};
			break;
		case 10:
			system("cls");
			// 10. Verificar se a arvore é completa
			if(ehCompletaCheia(arv))
			{
				cout << "--------------" << endl;
				cout << "A arvore eh completa :)" << endl;
				cout << "--------------" << endl;
			}
			else
			{
				cout << "--------------" << endl;
				cout << "A arvore NAO eh completa :(" << endl;
				cout << "--------------" << endl;
			};
			break;
		case 0:
			system("cls");
			cout << "Depois de me usar vai abandonar? Ja que eh assim, ok entao. A fila anda, meu bem.\n";
			cout << "TCHAU BRIGADU!" << endl;
			sair = true;
			// 0. Sair
			break;

		default:
			system("cls");
			// Opcao invalida
			cout << "--------------" << endl;
			cout << "Digita o bagulho certo, seu tchola!" << endl;
			cout << "--------------" << endl;

			break;
		}
	}
}


int main()
{
	menu();

	return 0;
}
