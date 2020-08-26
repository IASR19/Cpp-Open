#include <iostream>

using namespace std;

void display(int *array, int size)
{
	for(int i = 0; i < size; i++)
		cout << array[i] << " ";
	cout << endl;
}


void insertionSort(int *array, int size)
{
	int key, j;
	for(int i = 1; i < size; i++)
	{
		key = array[i]; //indique os valores
		j = i;
		while(j > 0 && array[j - 1] > key)
		{
			array[j] = array[j - 1];
			j--;
		}
		array[j] = key;   //inserindo no lugar correto
	}
}


int main()
{
	int n;
	cout << "Entre com o numero de elementos: ";
	cin >> n;
	int arr[n];    //crie um vetor com determinado número de elementos
	cout << "Entre com os elementos:" << endl;
	for(int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	cout << "\nVetor original: ";
	display(arr, n);
	insertionSort(arr, n);
	cout << "\nVetor ordenado: ";
	display(arr, n);
}
