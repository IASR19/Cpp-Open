#include <iostream>
#include <windows.h>

using namespace std;

struct deque // struct de dados
{
	int frente, fim, cap; // armazena a frente, final e capacidade do deque
	double *info;		  // info completa do deque
};

//funcao de inicializacao do deque
void init(deque *d, int c)
{
	d->frente = NULL;		 // indica que o deque est� vazio
	d->fim = -1;			 // indica que o deque est� vazio
	d->cap = c;				 // define a capacidade do deque
	d->info = new double[c]; // aloca mem�ria para a capacidade fornecida
}

bool isEmpty(deque *d) // função se deque estiver vazio
{
	int vazio = d->fim == -1;
	return vazio;
}

bool isFull(deque *d) // função se deque estiver cheio
{
	int cheio = d->fim == d->cap - 1;
	return cheio;
}

void insertFront(deque *d, double v) // função para inserir valor na frente
{
	if (d->fim == -1)
	{
		d->fim++;
		d->info[d->fim] = v;
	}

	else
	{
		for (int i = d->fim; i >= d->frente; i--)
		{
			double aux = d->info[i];
			d->info[i + 1] = aux;
		}
		d->info[d->frente] = v;
		d->fim++;
	}
}

void insertRear(deque *d, double v) // função para inserir no fim do deque
{
	d->fim++;
	d->info[d->fim] = v;
}

double deleteFront(deque *d) // função para deletar o primeiro valor
{
	double del /* variável auxiliar */ = d->info[d->frente];

	if (d->fim == 0)
		d->fim--;

	else
	{
		for (int i = d->frente + 1; i <= d->fim; i++)
		{
			double aux = d->info[i];
			d->info[i - 1] = aux;
		}
		d->fim--;
	}

	return del;
}

double deleteRear(deque *d) // função para deletar o último valor
{
	double aux = d->info[d->fim];

	d->fim--;

	return aux;
}

double getFront(deque *d) // função para exibir o inicio
{
	return d->info[d->frente];
}

double getRear(deque *d) // função para exibir o final
{
	return d->info[d->fim];
}

int main()
{
	deque d; // dados deque
	int cap; // capacidade

	cout << "Qual o tamanho do deque? ";
	cin >> cap;

	init(&d, cap); //definindo tamanho

	int op; // selecionar opção

	do
	{
		cout << "\n";
		cout << "Deque do tamanho ->" << cap << "<-\n" << "\n";
		cout << "ESCOLHA SUA OPCAO MEU CONSAGRADO! \n" << "\n";
		cout << "1 - Inserir valor na frente \n";
		cout << "2 - Inserir valor no final \n";
		cout << "3 - Deletar valor da frente \n";
		cout << "4 - Deletar valor do final \n";
		cout << "5 - Ver valor da frente \n";
		cout << "6 - Ver valor do final \n";
		cout << "0 - Sair da interatividade \n";
		cin >> op;

		//cases possiveis
		switch (op)
		{

		case 1: // incluir valor no inicio
			system("cls");
			if (isFull(&d) == true)
				cout << "Deque cheio! \n";
			else
			{
				double v;
				cout << "Valor a incluir: ";
				cin >> v;
				insertFront(&d, v); // Mandando valor para o endereço
				cout << "Valor " << v << " incluido no inicio \n";
			}
			break;

		//incluindo valor no final do deque
		case 2: // incluir valor no final
			system("cls");
			if (isFull(&d) == true)
				cout << "Deque cheio! \n";
			else
			{
				double v;
				cout << "Valor a incluir: ";
				cin >> v;
				insertRear(&d, v); // Mandando valor para o endereço
				cout << "Valor " << v << " incluido no fim \n";
			}
			break;

		case 3: // remover valor do inicio
			system("cls");
			if (isEmpty(&d) == true)
				cout << "Deque vazio! \n";
			else
			{
				double v = deleteFront(&d);
				cout << "Valor " << v << " removido do inicio \n";
			}
			break;

		//removendoo valor do final do deque
		case 4:
			system("cls");
			if (isEmpty(&d) == true)
				cout << "Deque vazio! \n";
			else
			{
				double v = deleteRear(&d);
				cout << "Valor " << v << " removido do fim \n";
			}
			break;

		case 5: // mostrando valor inicio
			system("cls");
			if (isEmpty(&d) == true)
				cout << "Deque vazio! \n";
			else
			{
				double v = getFront(&d);
				cout << "Valor inicial = " << v << endl;
			}
			break;

		case 6: // mostrando valor final
			system("cls");
			if (isEmpty(&d) == true)
				cout << "Deque vazio! \n";
			else
			{
				double v = getRear(&d);
				cout << "Valor final = " << v << endl;
			}
			break;

		case 0: // saindo
			system("cls");
			cout << "TCHAU BRIGADO";
			break;

		default:
			system("cls");
			cout << "Operação Inválida, digite novamente \n";
			break;
		}
	} while (op != 0);
}
