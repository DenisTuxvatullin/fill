// fill.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
const int MAX_SIZE = 102;
using namespace std;
typedef char Bitmap[MAX_SIZE][MAX_SIZE];

struct SymbolPosition
{
	int y;
	int x;
};

void Fill(Bitmap &a, int x, int y)
{
	if (a[x - 1][y] == ' ')
	{
		a[x - 1][y] = '.';
		Fill(a, x - 1, y);
	}
	if (a[x + 1][y] == ' ')
	{
		a[x + 1][y] = '.';
		Fill(a, x + 1, y);
	}
	if (a[x][y - 1] == ' ')
	{
		a[x][y - 1] = '.';
		Fill(a, x, y - 1);
	}
	if (a[x][y + 1] == ' ')
	{
		a[x][y + 1] = '.';
		Fill(a, x, y + 1);
	}
}

void FillWithZeros(Bitmap &a)
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			a[i][j] = 0;
		}
	}
}

vector<SymbolPosition> ReadData(ifstream &fin, int &rows, Bitmap &a, int(&rowSizes)[MAX_SIZE])
{
	char c; 
	int n = 1;
	int m = 1;
	vector<SymbolPosition> posList;
	while ((c = fin.get()) != EOF)
	{
		if (c == '\n')
		{
			rowSizes[n] = m;
			n++;
			m = 1;
			continue;
		}
		if (c == 'O')
		{
			posList.push_back({ n, m });
		}
		a[n][m] = c;
		m++;
	}
	if (m > 1)
	{
		rowSizes[n] = m;
		n++;
	}

	rows = n;
	return posList;
}

void PrintBitmap(ofstream &fout, int &rows, const Bitmap &a, const int (&rowSizes)[MAX_SIZE])
{
	for (int i = 1; i < rows; i++)
	{
		for (int j = 1; j < rowSizes[i]; j++)
		{
			fout << a[i][j];
		}
		fout << '\n';
	}
}

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		cout << "Not enough arguments \n";
		return 0;
	}
	ifstream fin(argv[1]);
	if (!fin.is_open())
	{
		cout << "Error with opening input file \n";
		return 1;
	}
	ofstream fout(argv[2]);
	if (!fout.is_open())
	{
		cout << "Error with opening output file \n";
		return 1;
	}
	Bitmap a;
	int rowsSizes[MAX_SIZE];
	FillWithZeros(a);
	int rows;
	auto posList = ReadData(fin, rows, a, rowsSizes);
	for (size_t i = 0; i < posList.size(); i++)
	{
		Fill(a, posList[i].x, posList[i].y);
	}
	PrintBitmap(fout, rows, a, rowsSizes);
	return 0;
}
