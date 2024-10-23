#include <iostream>
#include <vector>
#include <random>
#include <math.h>
#include <iomanip>
#include <chrono>
#include <limits>

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
	for (int i = 0; i < matA.size(); i++) // получаем значени€ b
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

void LD(vector<vector<double>>& mat)
{
	for (int i = 0; i < mat.size(); i++) // идем по столбцам вниз
	{
		double sum = 0;
		for (int k = 0; k < i; k++)
		{
			sum += mat[i][k] * mat[i][k] * mat[k][k];
		}
		mat[i][i] -= sum;
		
		//cout << mat[i][i] << "\n\n";
		for (int q = i + 1; q < mat.size(); q++)
		{
			sum = 0;
			for (int k = 0; k < i; k++)
			{
				sum += mat[q][k] * mat[i][k] * mat[k][k];
			}
			mat[q][i] -= sum;
			mat[q][i] /= mat[i][i];
		}
	}
}
void find_z(vector<vector<double>>& A, vector<double>& z, vector<double>& b)
{
	for (int i = 0; i < A.size(); i++)
	{
		for (int q = 0; q < i; q++)
		{
			b[i] -= A[i][q] * z[q];
		}
		z[i] = b[i];
	}
	for (int i = 0; i < A.size(); i++)
	{
		z[i] /= A[i][i];
	}
}
void find_x(vector<vector<double>>& A, vector<double>& z)
{
	for (int i = A.size() - 1; i >= 0; i--)
	{
		for (int q = i + 1; q < A.size(); q++)
		{
			z[i] -= A[q][i] * z[q];
		}
	}
}

int main()
{
	srand(time(0));
	std::cout << std::fixed << std::setprecision(12); //≈сли надо установить больше знаков после зап€той
	int n = 1000;
	vector<vector<double>> matA; // можем хранить только нижний треугольный вид, тк она симметрична 
	vector<double> solution(n, 0);
	vector<double> impreciseSolution(n, 0);
	vector<double> matB(n, 0);
	
	for (int i = 0; i < n; i++) // заполн€ем матрицу ј
	{
		vector <double> temp;
		for (int q = 0; q < i; q++)
		{
			temp.push_back(rand() % 201 - 100.0);
		}
		temp.push_back(0);
		matA.push_back(temp);
	}
	for (int i = 0; i < n; i++) // заполн€ем диагонали
	{
		double sum = 0;
		for (int q = 0; q < matA[i].size(); q++)
		{
			sum += abs(matA[i][q]);
		}
		for (int q = matA[i].size(); q < matA.size(); q++)
		{
			sum += abs(matA[q][i]);
		}
		matA[i][i] = rand() % 120 + 12.0 + sum;
	}
	for (int i = 0; i < n; i++) // точные решени€
	{
		solution[i] = 12.0 + i;
	}
	mulMat(matA, solution, matB); // перемножаем матрицы
	// получили матрицу b

	cout << "Solution:\n";
	printVec(solution);

	cout << "\n\n";
	//printVec(matA);

	auto start = chrono::high_resolution_clock::now();

	LD(matA); // преобразуем A в LD
	find_z(matA, impreciseSolution, matB); // находим сразу вектор z
	find_x(matA, impreciseSolution); // находим x

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;
	

	cout << "Imprecise solution:\n";
	printVec(impreciseSolution);
	
	cout << "\nTime: " << duration.count() << "\n\n";

	return 0;
}