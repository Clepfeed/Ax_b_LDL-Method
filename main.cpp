#include <iostream>
#include <vector>
#include <random>
#include <math.h>
#include <iomanip>
#include <chrono>


using namespace std;


void printVec(vector<vector<double>>& mat)
{
	for (int i = 0; i < mat.size(); i++)
	{
		for (int q = 0; q < mat[i].size(); q++)
		{
			cout << mat[i][q] << " ";
		}
		for (int q = mat[i].size(); q < mat.size(); q++)
		{
			cout << mat[q][i] << " ";
		}
		cout << "\n";
	}
}
void printVec(vector<double>& mat)
{
	
	for (int q = 0; q < mat.size() && q < 5; q++)
	{
		cout << mat[q] << " ";
	}
	cout << "\n";
	for (int q = mat.size() - 1; q > mat.size() - 6; q--)
	{
		cout << mat[q] << " ";
	}
	cout << "\n";
	
}
void mulMat(vector<vector<double>>& matA, vector<double>& x, vector<double>& matB)
{
	for (int i = 0; i < matA.size(); i++) // получаем значения b
	{
		for (int q = 0; q < matA[i].size(); q++)
		{
			matB[i] += matA[i][q] * x[q];
		}
		for (int q = matA[i].size(); q < matA.size(); q++)
		{
			matB[i] += matA[q][i] * x[q];
		}
	}
}

void LDL(vector<vector<double>>& matA)
{
	for (int i = 0; i < matA.size(); i++)
	{
		
	}
}

int main()
{
	srand(time(0));
	//std::cout << std::fixed << std::setprecision(12); //Если надо установить больше знаков после запятой
	int n = 3;
	vector<vector<double>> matA; // можем хранить только верхний треугольный вид, тк она симметрична 
	vector<double> solution(n, 0);
	vector<double> impreciseSolution(n, 0);
	vector<double> matB(n, 0);
	
	for (int i = 0; i < n; i++) // заполняем матрицу А
	{
		vector <double> temp;
		for (int q = 0; q < i; q++)
		{
			//temp.push_back(rand() % 200 - 100.0);
			temp.push_back(rand() % 8 + 1.0);
		}
		temp.push_back(0);
		matA.push_back(temp);
	}
	for (int i = 0; i < n; i++) // заполняем диагонали
	{
		double sum = 0;
		for (int q = 0; q < matA[i].size(); q++)
		{
			sum += matA[i][q];
		}
		for (int q = matA[i].size(); q < matA.size(); q++)
		{
			sum += matA[q][i];
		}
		matA[i][i] = rand() % 120 + 12.0 + sum;
	}
	for (int i = 0; i < n; i++) // точные решения
	{
		solution[i] = 12.0 + i;
	}
	mulMat(matA, solution, matB); // перемножаем матрицы
	// получили матрицу b
	
	/*printVec(matA);
	cout << "Solution:\n";
	printVec(solution);
	cout << "\nMat B:\n";
	printVec(matB);*/

	auto start = chrono::high_resolution_clock::now();

	LDL(matA); // преобразуем A в LDL^T

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;
	cout << "\nTime: " << duration.count() << "\n\n";

	


	return 0;
}