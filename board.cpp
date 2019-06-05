#include "board.h"
#include<random>
#include<iostream>

board::board(int n, int m, int mines)
{
	//validations of the input
	this->n = n;
	this->m = m;
	this->mines = mines;

	this->realBoard = new int*[n];
	this->visibleBoard = new int*[n];

	for (int i = 0; i < n; i++)
	{
		this->realBoard[i] = new int[m];
		this->visibleBoard[i] = new int[m];
	}

	for ( int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			this->realBoard[i][j] = 0;
			this->visibleBoard[i][j] = 0; // hidden
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

		if (realBoard[x][y] == -1)
		{
			i--;
		}
		else
		{
			realBoard[x][y] = -1;
		}
	}
}

void board::generateBoard()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (realBoard[i][j] != -1)
			{
				realBoard[i][j] = countMines(i, j);
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
		if (x + a[i] >= 0 && x + a[i] < n && y + b[i] >= 0 && y + b[i] < m)
		{
			if (realBoard[x + a[i]][y + b[i]] == -1)
				count++;
		}
	}

	return count;
}

bool board::clickTile(int x, int y)
{
	if (visibleBoard[x][y] == 1)
		return true;

	if (realBoard[x][y] == -1)
		return false;

	this->openTile(x, y);

	return true;
}

void board::markAsMine(int x, int y)
{
	if (visibleBoard[x][y] == 0)
		visibleBoard[x][y] = 2; //marked mine
}

void board::openTile(int x, int y)
{
	visibleBoard[x][y] = 1;

	if (realBoard[x][y] == 0)
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
			std::cout << realBoard[i][j] << " ";
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			std::cout << visibleBoard[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

board::~board()
{
	for (int i = 0; i < n; i++)
	{
		delete[] realBoard[i];
		delete[] visibleBoard[i];
	}

	delete[] realBoard;
	delete[] visibleBoard;
}
