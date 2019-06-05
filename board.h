#pragma once
class board
{
public:
	board(int n, int m, int mines);
	//The great 4
	~board();

	bool clickTile(int x, int y);
	void markAsMine(int x, int y);
	void printBoard() const;

private:
	int** realBoard;
	int** visibleBoard;
	int n, m;
	int mines;
	int minesLeft;

	void generateBoard();
	void setMines();
	int countMines(int x, int y);
	void openTile(int x, int y);
};

