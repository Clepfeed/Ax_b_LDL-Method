#include <iostream>
#include <vector>
#include <random>
#include <math.h>
#include <iomanip>
#include <chrono>
#include <fstream>

using namespace std;

ofstream fout("res.txt");

void printVec(vector<vector<double>>& mat)
{
	for (int i = 0; i < mat.size(); i++)
	{
		for (int q = 0; q < mat[i].size(); q++)
		{
			fout << mat[i][q] << " ";
		}
		for (int q = mat[i].size(); q < mat.size(); q++)
		{
			fout << mat[q][i] << " ";
		}
	}
}
void printVec(vector<double>& mat)
{
	for (int q = 0; q < mat.size() && q < 5; q++)
	{
		fout << mat[q] << " ";
	}
	for (int q = mat.size() - 5 > 5 ? mat.size() - 5 : 5; q < mat.size(); q++)
	{
		fout << mat[q] << " ";
	}
	fout << "\n";
}
void mulMat(vector<vector<double>>& matA, vector<double>& x, vector<double>& matB)
{
	for (int i = 0; i < matA.size(); i++) // �������� �������� b
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
	for (int i = 0; i < mat.size(); i++) // ���� �� �������� ����
	{
		double sum = 0;
		for (int k = 0; k < i; k++)
		{
			sum += mat[i][k] * mat[i][k] * mat[k][k];
		}
		mat[i][i] -= sum;
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
	/*fout << std::fixed << std::setprecision(22);*/ //���� ���� ���������� ������ ������ ����� �������
	int n = 1000;
	vector<vector<double>> matA; // ����� ������� ������ ������ ����������� ���, �� ��� ����������� 
	vector<double> solution(n, 0);
	vector<double> impreciseSolution(n, 0);
	vector<double> matB(n, 0);
	
	for (int i = 0; i < n; i++) // ��������� ������� �
	{
		vector <double> temp;
		for (int q = 0; q < i; q++)
		{
			temp.push_back(rand() % 201 - 100.0);
		}
		temp.push_back(0);
		matA.push_back(temp);
	}
	for (int i = 0; i < n; i++) // ��������� ���������
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
	for (int i = 0; i < n; i++) // ������ �������
	{
		solution[i] = 12.0 + i;
	}
	mulMat(matA, solution, matB); // ����������� �������
	// �������� ������� b

	fout << "Solution:\n";
	printVec(solution);
	fout << "\n\n";

	auto start = chrono::high_resolution_clock::now();

	LD(matA); // ����������� A � LD
	find_z(matA, impreciseSolution, matB); // ������� ������ z
	find_x(matA, impreciseSolution); // ������� x

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;

	fout << std::fixed << std::setprecision(22);
	fout << "Imprecise solution:\n";
	printVec(impreciseSolution);
	
	fout << "\nTime: " << duration.count() << " seconds\n\n";


	double normSol = 0;
	for (int i = 0; i < solution.size(); i++)
	{
		normSol += abs(solution[i]);
	}
	double normSolImprecise = 0;
	for (int i = 0; i < solution.size(); i++)
	{
		normSolImprecise += abs(solution[i] - impreciseSolution[i]);
	}
	fout << "Relative error: " << normSolImprecise / normSol << "\n";
	

	return 0;
}