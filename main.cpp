#include "minefield.h"

int main()
{
	srand(time(NULL));
	cout << "Welcome to Minesweeper!" << endl;
	Minefield minefield = Minefield(99,16,30);
	minefield.initialize();
	if (minefield.solve()) {
		minefield.printField();
		cout << "Solved!";
	}
	cout << "bla";
//	bool loopFlag = true;
//	int selectRow = 0;
//	int selectCol = 0;
//	while (loopFlag) {
//		minefield.printField(selectRow,selectCol);
//        switch(getch()) {
//            case 'w': {
//				selectRow -= ((selectRow-1) >= 0);
//                break;
//            }
//            case 's': {
//                selectRow += ((selectRow+1) < minefield.getHeight());
//                break;
//            }
//            case 'd': {
//                selectCol += ((selectCol+1) < minefield.getWidth());
//                break;
//            }
//            case 'a': {
//                selectCol -= ((selectCol-1) >= 0);
//                break;
//            }
//            case 'e': {
//                switch (minefield.uncover(selectRow,selectCol)) {
//                    case 1: {
//                        loopFlag = false;
//                        cout << "You lost!" << endl;
//                        break;
//                    }
//                    case 2: {
//                        cout << "That tile has already been clicked!" << endl;
//                        break;
//                    }
//                }
//                if (minefield.win()) {
//					cout << "You won!" << endl;
//					cout << "Play again? (Y/N): ";
//					char playAgain;
//					do {
//					cin >> playAgain;
//					} while (playAgain != 'Y' && playAgain != 'N');
//					loopFlag = (playAgain == 'Y') ? true : false;
//					minefield.initialize();
//                }
//                break;
//            }
//        }
//	}
}
