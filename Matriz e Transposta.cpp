#include <iostream>

using namespace std;

int main()
{
	int n,m;
	cout << "No. Linhas da matriz: ";
	cin >> n;
	cout << "No. Colunas da matriz: ";
	cin >> m;
	
	
	int mat1[100][100], mat2[100][100];
	
	for(int i = 1; i<=n; i++)
	{
		for(int j=1; j<=m; j++)
		{
			cout << "Entre c/ o valor da matriz para coordenada " << i << " , " << j << ": ";
			cin >> mat1[i][j];
		}
	}
	
	
	// Matriz Gerada
	cout << endl << endl << "C = " << endl;
	
	 for (int i =1; i<=n; i++)
	{
		for (int j=1; j <=m; j++)
		{
			cout << mat1[i][j] << " ";
		}
		
		cout << endl;
	}
	
	
	
	// Matriz Transposta
	cout << endl << endl <<
	 "CT = " << endl;
	
	for (int j=1; j <=m; j++)
	{
		for (int i =1; i<=n; i++)
		{
			cout << mat1[i][j] << " ";
		}
		
		cout << endl;
	}
	
}