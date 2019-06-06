#include "board.h"
#include<random>
#include<iostream>
#include<exception>

board::board(int n, int m, int mines)
{
	if (n < 0 || m < 0 || mines > n * m)
		throw "Not valid parameters.";

	this->n = n;
	this->m = m;
	this->mines = mines;

	this->realBoard = new int**[n];
	
	for (int i = 0; i < n; i++)
	{
		this->realBoard[i] = new int*[m];
	}

	for ( int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			this->realBoard[i][j] = new int[2];
			this->realBoard[i][j][0] = 0; //start status
			this->realBoard[i][j][1] = hidden; //hiden
		}

	this->setMines();

	this->generateBoard();
}

void board::setMines()
{
	for (int i = 0; i < mines; i++)
	{
		int x = rand() % n;
		int y = rand() % m;

		if (realBoard[x][y][0] == -1)
		{
			i--;
		}
		else
		{
			realBoard[x][y][0] = -1;
		}
	}
}

void board::generateBoard()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (realBoard[i][j][0] != -1)
			{
				realBoard[i][j][0] = countMines(i, j);
			}
		}
	}
}

int board::countMines(int x, int y)
{
	int count = 0;

	int a[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int b[8] = {-1, 0, 1, -1 , 1, -1, 0, 1};

	for (int i = 0; i < 8; i++)
	{
		int new_x = x + a[i];
		int new_y = y + b[i];

		if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < m)
		{
			if (realBoard[new_x][new_y][0] == -1)
				count++;
		}
	}

	return count;
}

bool board::clickTile(int x, int y)
{
	if (realBoard[x][y][1] == visible)
		return true;

	if (realBoard[x][y][0] == -1)
		return false;

	this->openTile(x, y);

	return true;
}

void board::markAsMine(int x, int y)
{
	if (realBoard[x][y][1] == hidden)
		realBoard[x][y][1] = marked; 
	else if (realBoard[x][y][1] == marked)
		realBoard[x][y][1] = hidden;
}

void board::openTile(int x, int y)
{
	realBoard[x][y][1] = visible;

	if (realBoard[x][y][0] == 0)
	{
		int a[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
		int b[8] = { -1, 0, 1, -1 , 1, -1, 0, 1 };

		for (int i = 0; i < 8; i++)
		{
			int new_x = x + a[i];
			int new_y = y + b[i];

			if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < m)
			{
				this->openTile(new_x, new_y);
			}
		}
	}
}

void board::printBoard() const
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			std::cout << realBoard[i][j][0] << " ";
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			std::cout << realBoard[i][j][1] << " ";
		}
		std::cout << std::endl;
	}
}

board::~board()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			delete[] realBoard[i][j];
		delete[] realBoard[i];
	}

	delete[] realBoard;
}
