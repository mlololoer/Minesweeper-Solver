#include "minefield.h"

void consoleMove(const int& x, const int& y) {
	COORD a = {static_cast<short>(x),static_cast<short>(y)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),a);
}

void setColor(Color fg = LIGHTGRAY, Color bg = BLACK) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg + (bg<<4));
}

Minefield::Minefield(int num_mines, int height, int width) : num_mines(num_mines), height(height), width(width) {
	field = new short*[height];
	hidden = new bool*[height];
	mines = new bool*[height];
	for (int i = 0; i < height; i++) {
		field[i] = new short[width];
		hidden[i] = new bool[width];
		mines[i] = new bool[width];
	}
}

void Minefield::initialize() { //given number of mines, place them onto the field.
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			field[i][j] = 0;
			hidden[i][j] = true;
			mines[i][j] = false;
		}
	}
	for (int i = 0; i < num_mines; i++) {
		bool minePlaced = false;
		while (!minePlaced) {
			int randomHeight = rand()%height;
			int randomWidth = rand()%width;
			if (field[randomHeight][randomWidth] != 9) {
				field[randomHeight][randomWidth] = 9;
				for (int j = -1; j <= 1; j++) {
					for (int k = -1; k <= 1; k++) {
						if (
							randomHeight + j >= 0 && randomHeight + j < height
							&&
							randomWidth + k >= 0 && randomWidth + k < width
							&&
							field[randomHeight+j][randomWidth+k] != 9
						) {
							field[randomHeight+j][randomWidth+k]++;
						}
					}
				}
				minePlaced = true;
			}
		}
	}
}

bool Minefield::win() const {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (hidden[i][j] && field[i][j] != 9) return false;
		}
	}
	return true;
}

void Minefield::printField() const{
    consoleMove(0,2);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (hidden[i][j]) {
				cout << '?';
			} else if (field[i][j] == 0) {
			    cout << ' ';
			} else {
				switch (field[i][j]) {
					case 1:
						setColor(CYAN, BLACK);
						break;
					case 2:
						setColor(LIGHTGREEN,BLACK);
						break;
					case 3:
						setColor(LIGHTRED, BLACK);
						break;
					case 4:
						setColor(BLUE, BLACK);
						break;
					case 5:
						setColor(RED, BLACK);
						break;
					case 6:
						setColor(LIGHTGRAY, BLACK);
						break;
					case 7:
						setColor(GREEN, BLACK);
						break;
					case 8:
						setColor(DARKGRAY, BLACK);
				}
				cout << field[i][j];
				setColor(LIGHTGRAY,BLACK);
			}
		}
		cout << endl;
	}
	cout << endl;
}

void Minefield::printField(const int& selectRow, const int& selectCol) const{
    consoleMove(0,2);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
		    cout << ((i == selectRow && (selectCol == j || selectCol+1 == j)) ? '|' : ' ');
			if (hidden[i][j]) {
				cout << '?';
			} else if (field[i][j] == 0) {
			    cout << ' ';
			} else {
				switch (field[i][j]) {
					case 1:
						setColor(CYAN, BLACK);
						break;
					case 2:
						setColor(LIGHTGREEN,BLACK);
						break;
					case 3:
						setColor(LIGHTRED, BLACK);
						break;
					case 4:
						setColor(BLUE, BLACK);
						break;
					case 5:
						setColor(RED, BLACK);
						break;
					case 6:
						setColor(LIGHTGRAY, BLACK);
						break;
					case 7:
						setColor(GREEN, BLACK);
						break;
					case 8:
						setColor(DARKGRAY, BLACK);
				}
				cout << field[i][j];
				setColor(LIGHTGRAY,BLACK);
			}
		}
		cout << endl << endl;
	}
	cout << endl;
}

void Minefield::debugPrintField() const{
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) cout << field[i][j] << ' ';
		cout << endl << endl;
	}
	cout << endl;
}

int Minefield::getHeight() const {return height;}
int Minefield::getWidth() const {return width;}
bool Minefield::inBounds(const int& row, const int& col) const{return (row >= 0 && row < height && col >= 0 && col < width);}

short Minefield::uncover(const int& row, const int& col) {
    if (field[row][col] == 9) return 1; // mine clicked!
    else if (hidden[row][col]) {
        hidden[row][col] = false;
        if (field[row][col] == 0) {
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    if (!(i == 0 && j == 0) && inBounds(row+i,col+j))uncover(row+i,col+j);
                }
            }
        }
        return 0; // no error
    }
    else return 2; // already clicked!
}

void Minefield::eliminate(const int& row, const int& col) {
	short numMines = 0;
	for (int i = row-1; i <= row+1; ++i) {
		for (int j = col-1; j <= col+1; ++j) {
			if ((i != 0 || j != 0)&&inBounds(i,j)) {

			}
		}
	}
	if (numMines == field[row][col]) {
		for (int i = row-1; i <= row+1; ++i) {
			for (int j = col-1; j <= col+1; ++j) {
				if ((i != 0 || j != 0)&&inBounds(i,j)&& hidden[i][j] && !mines[i][j]) {
					uncover(i,j);
				}
			}
		}
	}
}
void Minefield::mark(const int& row, const int& col) {
	if (field[row][col] == 0 || field[row][col] == 9) return;
	short numHidden = 0;
	short numMines = 0;
	for (int i = row-1; i <= row+1; ++i) {
		for (int j = col-1; j <= col+1; ++j) {
			if ((i != 0 || j != 0)&&inBounds(i,j)) {
				numHidden += hidden[i][j];
				numMines += mines[i][j];
			}
		}
	}
	if (numHidden == field[row][col]) {
		for (int i = row-1; i <= row+1; ++i) {
			for (int j = col-1; j <= col+1; ++j) {
				if ((i != 0 || j != 0)&&inBounds(i,j)&& hidden[i][j]) {
					mines[i][j] = true;
				}
			}
		}
	}
	if (numMines == field[row][col]) {
		for (int i = row-1; i <= row+1; ++i) {
			for (int j = col-1; j <= col+1; ++j) {
				if ((i != 0 || j != 0)&&inBounds(i,j)&& hidden[i][j] && !mines[i][j]) {
					uncover(i,j);
				}
			}
		}
	}
}


bool Minefield::solve() {
	int selectedHeight;
	int selectedWidth;
	do {
		selectedHeight = rand()%height; selectedWidth = rand()%width;
	} while (field[selectedHeight][selectedWidth] != 0);
	uncover(selectedHeight,selectedWidth);
	printField();
	while (!win()) {
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				if (hidden[i][j] || field[i][j] == 0) continue;
				mark(i,j);
				//eliminate(i,j);
			}
		}
		printField();
	}
	return true;
}

Minefield::~Minefield() {
	for (int i = 0; i < height; i++) {
		delete [] field[i];
		delete [] hidden[i];
		delete [] mines[i];
	}
	delete [] field;
	delete [] hidden;
	delete [] mines;
}
