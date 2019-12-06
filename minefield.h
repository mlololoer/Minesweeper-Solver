#ifndef MINEFIELD_H_INCLUDED
#define MINEFIELD_H_INCLUDED
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
using std::cout;
using std::cin;
using std::endl;

enum Location{NOLOC,ACC,INP,OUT,STK};
enum Color
{BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
LIGHTGRAY, DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN,
LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE};


void consoleMove(const int& x, const int& y);
void setColor(Color fg, Color bg);

class Minefield{
	short** field;
	bool** hidden;
	bool** mines; //for solver to keep track of mines
	const int num_mines;
	const int height;
	const int width;
public:
	Minefield(int num_mines = 10, int height = 10, int width = 10);
	void initialize();
	void printField() const;
	void printField(const int& selectRow, const int& selectCol) const;
	int getHeight() const;
	int getWidth() const;
	bool win() const;
	void debugPrintField() const;
	short uncover(const int& row, const int& col);
	bool inBounds(const int& row, const int& col) const;
	void mark(const int& row, const int& col);
	void eliminate(const int& row, const int& col);
	bool solve();
	~Minefield();
};



#endif // MINEFIELD_H_INCLUDED
