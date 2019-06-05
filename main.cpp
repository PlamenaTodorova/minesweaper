#include "board.h"
#include<iostream>

using namespace std;

int main()
{
	board b(5, 5, 6);

	b.printBoard();

	system("pause");
	return 0;
}