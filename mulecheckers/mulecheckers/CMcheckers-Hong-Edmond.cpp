#include <iostream>
#include <iomanip>

using namespace std;



const int MAX_ARRAY_SIZE = 18;

const int MIN_ARRAY_SIZE = 8;

const int MAX_PIECES = 72;

const int NOPLAYER = 0;

const int WHITEWINS = 1;

const int REDWINS = 2;

const int NOONEWINS = 0;

const int WHITESOLDIER = 1;

const int WHITEMULE = 2;

const int WHITEKING = 3;

const int REDSOLDIER = 4;

const int REDMULE = 5;

const int REDKING = 6;

const int WHITEPLAYER = 1;

const int REDPLAYER = 2;


void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);

void DisplayBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);

int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);

bool CheckList(int inArray1[], int inArray2[], int xIndex, int yIndex);

int CountMove1Squares(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);

bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc);

bool IsJump(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc);

bool MakeMove(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool &jumped);

bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);

int main()
{
	int myCMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE] = { 0 };
	int xIndicesMove[MAX_PIECES] = { 0 };
	int yIndicesMove[MAX_PIECES] = { 0 };
	int xIndicesJump[MAX_PIECES] = { 0 };
	int yIndicesJump[MAX_PIECES] = { 0 };
	int numRowsInBoard = 0;
	int player = 1;
	int fromSquareNum = 0;
	int toSquareNum = 0;
	bool propervalue = false;
	// number conversion to x and y maxtrix coordinates - > myCMCheckersBoard[fromSquareNumy][fromSquareNumx]
	int fromSquareNumx = 0;
	int fromSquareNumy = 0;
	int toSquareNumx = 0;
	int toSquareNumy = 0;
	int whiteturncount = 0;
	int redturncount = 0;
	int ydistance = 0;
	bool jumped = false;
	char c;


	cout << "Enter the number of squares along each edge of the board " << endl;
	cin >> numRowsInBoard;
	for (int count = 0; count <= 2; count++)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			if (count == 2)
			{
				cerr << "ERROR: Too many errors entering the size of the board.";
				return 1;
			}
			else
			{
				cerr << "ERROR: Board size is not an integer." << endl << "8 <= number of squares <= 18" << endl;
				cout << "Enter the number of squares along each edge of the board " << endl;
				cin >> numRowsInBoard;
			}
		}
		else if (numRowsInBoard % 2 != 0)
		{
			if (count == 2)
			{
				cerr << "ERROR: Too many errors entering the size of the board.";
				return 2;
			}
			else
			{
				cerr << "ERROR: Board size odd." << endl << "8 <= number of squares <= 18" << endl;
				cout << "Enter the number of squares along each edge of the board " << endl;
				cin >> numRowsInBoard;
			}
		}
		else if (numRowsInBoard > 18)
		{
			if (count == 2)
			{
				cerr << "ERROR: Too many errors entering the size of the board.";
				return 3;
			}
			else
			{
				cerr << "ERROR: Board size too large." << endl << "8 <= number of squares <= 18" << endl;
				cout << "Enter the number of squares along each edge of the board " << endl;
				cin >> numRowsInBoard;
			}
		}
		else if (numRowsInBoard < 8)
		{
			if (count == 2)
			{
				cerr << "ERROR: Too many errors entering the size of the board.";
				return 4;
			}
			else
			{
				cerr << "ERROR: Board size too small." << endl << "8 <= number of squares <= 18" << endl;
				cout << "Enter the number of squares along each edge of the board " << endl;
				cin >> numRowsInBoard;
			}
		}
	}
	InitializeBoard(myCMCheckersBoard, numRowsInBoard);
	DisplayBoard(myCMCheckersBoard, numRowsInBoard);
	do
	{
		if (player == WHITEPLAYER)
		{
			if (CountMove1Squares(myCMCheckersBoard, numRowsInBoard, player, xIndicesMove, yIndicesMove) == 0 && CountJumps(myCMCheckersBoard, numRowsInBoard, player, xIndicesJump, yIndicesJump) == 0)
			{
				cout << "White is unable to move." << endl;
				cout << "GAME OVER, Red has won." << endl;
				cout << "enter any character to close the game." << endl;
				cin >> c;
				return 1;
			}
			else
			{
				if (whiteturncount == 0)
				{
					cout << "White takes a turn " << endl;
				}
				do
				{
					propervalue = false;
					cout << "Enter square number of the checker you want to move " << endl;

					cin >> fromSquareNum;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore();
						cout << "you did not enter an integer" << endl;
						cout << "Try again" << endl;
					}
					else
					{
						fromSquareNumx = (fromSquareNum % numRowsInBoard);
						fromSquareNumy = (fromSquareNum / numRowsInBoard);
						if (CountJumps(myCMCheckersBoard, numRowsInBoard, player, xIndicesJump, yIndicesJump) > 0)
						{
							if (fromSquareNum > (numRowsInBoard*numRowsInBoard))
							{
								cerr << "ERROR: That square is not on the board. " << endl;
								cout << "Try again " << endl;
							}
							else if (fromSquareNum < 0)
							{
								cerr << "ERROR: It is not possible to move to a square that is not on the board. " << endl;
								cout << "Try again " << endl;
							}
							else if (myCMCheckersBoard[fromSquareNumy][fromSquareNumx] >= 4 && myCMCheckersBoard[fromSquareNumy][fromSquareNumx] <= 6)
							{
								cerr << "ERROR: That square contains an opponent's checker. " << endl;
								cout << "Try again " << endl;
							}
							else if (myCMCheckersBoard[fromSquareNumy][fromSquareNumx] == 0)
							{
								cerr << "ERROR: That square is empty " << endl;
								cout << "Try again " << endl;
							}
							else if (!IsMove1Square(myCMCheckersBoard, numRowsInBoard, player, fromSquareNumx, fromSquareNumy) && !IsJump(myCMCheckersBoard, numRowsInBoard, player, fromSquareNumx, fromSquareNumy))
							{
								cerr << "ERROR: There is no legal move for this checker." << endl;
								cout << "Try again " << endl;
							}
							else
							{
								for (int a = 0; a < CountJumps(myCMCheckersBoard, numRowsInBoard, player, xIndicesJump, yIndicesJump); a++)
								{
									if (yIndicesJump[a] == fromSquareNumy && xIndicesJump[a] == fromSquareNumx)
									{
										propervalue = true;
									}
								}
								if (propervalue != true)
								{
									cerr << "ERROR: You can jump with another checker, you may not move your chosen checker." << endl;
									cout << "You can jump using checkers on the following squares: ";
									for (int a = 0; a < CountJumps(myCMCheckersBoard, numRowsInBoard, player, xIndicesJump, yIndicesJump); a++)
									{
										cout << yIndicesJump[a] * numRowsInBoard + xIndicesJump[a] << " ";
									}
									cout << endl;
								}
							}
						}
						else
						{
							if (fromSquareNum > (numRowsInBoard*numRowsInBoard))
							{
								cerr << "ERROR: That square is not on the board. " << endl;
								cout << "Try again " << endl;
							}
							else if (fromSquareNum < 0)
							{
								cerr << "ERROR: It is not possible to move to a square that is not on the board. " << endl;
								cout << "Try again " << endl;
							}
							else if (myCMCheckersBoard[fromSquareNumy][fromSquareNumx] >= 4 && myCMCheckersBoard[fromSquareNumy][fromSquareNumx] <= 6)
							{
								cerr << "ERROR: That square contains an opponent's checker. " << endl;
								cout << "Try again " << endl;
							}
							else if (myCMCheckersBoard[fromSquareNumy][fromSquareNumx] == 0)
							{
								cerr << "ERROR: That square is empty " << endl;
								cout << "Try again " << endl;
							}
							else if (!IsMove1Square(myCMCheckersBoard, numRowsInBoard, player, fromSquareNumx, fromSquareNumy) && !IsJump(myCMCheckersBoard, numRowsInBoard, player, fromSquareNumx, fromSquareNumy))
							{
								cerr << "ERROR: There is no legal move for this checker." << endl;
								cout << "Try again " << endl;
							}
							else
							{
								propervalue = true;
							}
						}
					}
				} while (!propervalue);
				do
				{
					propervalue = false;
					cout << "Enter square number of the square you want to move your checker to " << endl;
					cin >> toSquareNum;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore();
						cout << "you did not enter an integer" << endl;
						cout << "Try again" << endl;
					}
					else
					{
						toSquareNumx = (toSquareNum % numRowsInBoard);
						toSquareNumy = (toSquareNum / numRowsInBoard);
						ydistance = toSquareNumy - fromSquareNumy;

						if (CountJumps(myCMCheckersBoard, numRowsInBoard, player, xIndicesJump, yIndicesJump) > 0)
						{
							if (toSquareNum > (numRowsInBoard*numRowsInBoard) || toSquareNum < 0)
							{
								cerr << "ERROR: That square is not on the board. " << endl;
								cout << "Try again " << endl;
							}
							else if (myCMCheckersBoard[toSquareNumy][toSquareNumx] != 0)
							{
								cerr << "ERROR: It is not possible to move to a square that is already occupied. " << endl;
								cout << "Try again " << endl;
							}
							else if (fromSquareNum != (int)fromSquareNum)
							{
								cout << "you did not enter an integer" << endl;
								cout << "Try again" << endl;
							}
							else if (ydistance != 2 && ydistance != -2)
							{
								cerr << "ERROR: You can jump with this checker, you must jump not move 1 space." << endl;
								cout << "Try again" << endl;
							}
							else
							{
								propervalue = true;
							}
						}
						else
						{
							if (toSquareNum > (numRowsInBoard*numRowsInBoard) || toSquareNum < 0)
							{
								cerr << "ERROR: That square is not on the board. " << endl;
								cout << "Try again " << endl;
							}
							else if (myCMCheckersBoard[toSquareNumy][toSquareNumx] != 0)
							{
								cerr << "ERROR: It is not possible to move to a square that is already occupied. " << endl;
								cout << "Try again " << endl;
							}
							else if (fromSquareNum != (int)fromSquareNum)
							{
								cout << "you did not enter an integer" << endl;
								cout << "Try again" << endl;
							}
							else
							{
								propervalue = true;
							}
						}
					}
				} while (!propervalue);
			}
			if (MakeMove(myCMCheckersBoard, numRowsInBoard, player, fromSquareNum, toSquareNum, jumped))
			{
				DisplayBoard(myCMCheckersBoard, numRowsInBoard);
				while (jumped)
				{
					jumped = false;
					if (IsJump(myCMCheckersBoard, numRowsInBoard, player, toSquareNumx, toSquareNumy))
					{
						cout << "You can jump again, Please enter the next square you wish to move your checker to" << endl;
						fromSquareNum = toSquareNum;
						cin >> toSquareNum;
						MakeMove(myCMCheckersBoard, numRowsInBoard, player, fromSquareNum, toSquareNum, jumped);
						DisplayBoard(myCMCheckersBoard, numRowsInBoard);

					}
				}
				player = REDPLAYER;
			}
			else
			{
				cerr << "Error: illegal move " << endl;
				whiteturncount++;
			}
			redturncount = 0;
			if ((CheckWin(myCMCheckersBoard, numRowsInBoard)))
			{
				cout << "Enter any character to terminate the game then press the enter key" << endl;
				cin >> c;
				return 0;
			}
		}

		if (player == REDPLAYER)
		{
			if (CountMove1Squares(myCMCheckersBoard, numRowsInBoard, player, xIndicesMove, yIndicesMove) == 0 && CountJumps(myCMCheckersBoard, numRowsInBoard, player, xIndicesJump, yIndicesJump) == 0)
			{
				cout << "Red is unable to move." << endl;
				cout << "GAME OVER, White has won." << endl;
				cout << "enter any character to close the game." << endl;
				cin >> c;
				return 2;

			}
			else
			{
				if (redturncount == 0)
				{
					cout << "Red takes a turn " << endl;
				}
				do {
					propervalue = false;
					cout << "Enter square number of the checker you want to move " << endl;
					cin >> fromSquareNum;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore();
						cout << "you did not enter an integer" << endl;
						cout << "Try again" << endl;
					}
					else
					{
						fromSquareNumx = (fromSquareNum % numRowsInBoard);
						fromSquareNumy = (fromSquareNum / numRowsInBoard);
						if (CountJumps(myCMCheckersBoard, numRowsInBoard, player, xIndicesJump, yIndicesJump) > 0)
						{
							if (fromSquareNum > (numRowsInBoard*numRowsInBoard))
							{
								cerr << "ERROR: That square is not on the board. " << endl;
								cout << "Try again " << endl;
							}
							else if (fromSquareNum < 0)
							{
								cerr << "ERROR: It is not possible to move to a square that is not on the board. " << endl;
								cout << "Try again " << endl;
							}
							else if (myCMCheckersBoard[fromSquareNumy][fromSquareNumx] >= 1 && myCMCheckersBoard[fromSquareNumy][fromSquareNumx] <= 3)
							{
								cerr << "ERROR: That square contains an opponent's checker. " << endl;
								cout << "Try again " << endl;
							}
							else if (myCMCheckersBoard[fromSquareNumy][fromSquareNumx] == 0)
							{
								cerr << "ERROR: That square is empty " << endl;
								cout << "Try again " << endl;
							}
							else if (!IsMove1Square(myCMCheckersBoard, numRowsInBoard, player, fromSquareNumx, fromSquareNumy) && !IsJump(myCMCheckersBoard, numRowsInBoard, player, fromSquareNumx, fromSquareNumy))
							{
								cerr << "ERROR: There is no legal move for this checker." << endl;
								cout << "Try again " << endl;
							}
							else
							{
								for (int a = 0; a < CountJumps(myCMCheckersBoard, numRowsInBoard, player, xIndicesJump, yIndicesJump); a++)
								{
									if (yIndicesJump[a] == fromSquareNumy && xIndicesJump[a] == fromSquareNumx)
									{
										propervalue = true;
									}
								}
								if (propervalue != true)
								{
									cerr << "ERROR: You can jump with another checker, you may not move your chosen checker." << endl;
									cout << "You can jump using checkers on the following squares: ";
									for (int a = 0; a < CountJumps(myCMCheckersBoard, numRowsInBoard, player, xIndicesJump, yIndicesJump); a++)
									{
										cout << yIndicesJump[a] * numRowsInBoard + xIndicesJump[a] << " ";
									}
									cout << endl;
								}
							}
						}
						else
						{
							if (fromSquareNum > (numRowsInBoard*numRowsInBoard))
							{
								cerr << "ERROR: That square is not on the board. " << endl;
								cout << "Try again " << endl;
							}
							else if (fromSquareNum < 0)
							{
								cerr << "ERROR: It is not possible to move to a square that is not on the board. " << endl;
								cout << "Try again " << endl;
							}
							else if (myCMCheckersBoard[fromSquareNumy][fromSquareNumx] >= 1 && myCMCheckersBoard[fromSquareNumy][fromSquareNumx] <= 3)
							{
								cerr << "ERROR: That square contains an opponent's checker. " << endl;
								cout << "Try again " << endl;
							}
							else if (myCMCheckersBoard[fromSquareNumy][fromSquareNumx] == 0)
							{
								cerr << "ERROR: That square is empty " << endl;
								cout << "Try again " << endl;
							}
							else if (!IsMove1Square(myCMCheckersBoard, numRowsInBoard, player, fromSquareNumx, fromSquareNumy) && !IsJump(myCMCheckersBoard, numRowsInBoard, player, fromSquareNumx, fromSquareNumy))
							{
								cerr << "ERROR: There is no legal move for this checker." << endl;
								cout << "Try again " << endl;
							}
							else
							{
								propervalue = true;
							}
						}
					}

				} while (!propervalue);

				do
				{
					propervalue = false;
					cout << "Enter square number of the square you want to move your checker to " << endl;
					cin >> toSquareNum;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore();
						cout << "you did not enter an integer" << endl;
						cout << "Try again" << endl;
					}
					else
					{
						toSquareNumx = (toSquareNum % numRowsInBoard);
						toSquareNumy = (toSquareNum / numRowsInBoard);
						ydistance = toSquareNumy - fromSquareNumy;

						if (CountJumps(myCMCheckersBoard, numRowsInBoard, player, xIndicesJump, yIndicesJump) > 0)
						{
							if (toSquareNum > (numRowsInBoard*numRowsInBoard) || toSquareNum < 0)
							{
								cerr << "ERROR: That square is not on the board. " << endl;
								cout << "Try again " << endl;
							}
							else if (myCMCheckersBoard[toSquareNumy][toSquareNumx] != 0)
							{
								cerr << "ERROR: It is not possible to move to a square that is already occupied. " << endl;
								cout << "Try again " << endl;
							}
							else if (ydistance != 2 && ydistance != -2)
							{
								cerr << "ERROR: You can jump with this checker, you must jump not move 1 space." << endl;
								cout << "Try again" << endl;
							}
							else
							{
								propervalue = true;
							}
						}
						else
						{
							if (toSquareNum > (numRowsInBoard*numRowsInBoard) || toSquareNum < 0)
							{
								cerr << "ERROR: That square is not on the board. " << endl;
								cout << "Try again " << endl;
							}
							else if (myCMCheckersBoard[toSquareNumy][toSquareNumx] != 0)
							{
								cerr << "ERROR: It is not possible to move to a square that is already occupied. " << endl;
								cout << "Try again " << endl;
							}
							else
							{
								propervalue = true;
							}
						}
					}
				} while (!propervalue);

			}
			if (MakeMove(myCMCheckersBoard, numRowsInBoard, player, fromSquareNum, toSquareNum, jumped))
			{
				DisplayBoard(myCMCheckersBoard, numRowsInBoard);
				while (jumped)
				{
					jumped = false;
					if (IsJump(myCMCheckersBoard, numRowsInBoard, player, toSquareNumx, toSquareNumy))
					{
						cout << "You can jump again, Please enter the next square you wish to move your checker to" << endl;
						fromSquareNum = toSquareNum;
						cin >> toSquareNum;
						MakeMove(myCMCheckersBoard, numRowsInBoard, player, fromSquareNum, toSquareNum, jumped);
						DisplayBoard(myCMCheckersBoard, numRowsInBoard);

					}
				}
				player = WHITEPLAYER;
			}
			else
			{
				cerr << "Error: illegal move " << endl;
				redturncount++;
			}
			whiteturncount = 0;
		}
	} while (!(CheckWin(myCMCheckersBoard, numRowsInBoard)));
	cout << "Enter any character to terminate the game then press the enter key" << endl;
	cin >> c;
	return 0;
}
void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	int i = 0;
	int j = 0;


	while (i < (numRowsInBoard - 2) / 2)
	{
		while (j < numRowsInBoard)
		{
			if (i == 0)
			{
				if (j % 2 == 0)
				{
					CMCheckersBoard[i][j] = 0;
				}
				else
				{
					CMCheckersBoard[i][j] = 2;
				}
			}
			else
			{
				if (i % 2 == 0)
				{
					if (j % 2 == 0)
					{
						CMCheckersBoard[i][j] = 0;
					}
					else
					{
						CMCheckersBoard[i][j] = 1;
					}
				}
				else
				{
					if (j % 2 == 0)
					{
						CMCheckersBoard[i][j] = 1;
					}
					else
					{
						CMCheckersBoard[i][j] = 0;
					}
				}
			}
			j++;
		}
		j = 0;
		i++;
	}
	for (int count = 0; count < 2; count++)
	{
		while (j < numRowsInBoard)
		{
			CMCheckersBoard[i][j] = 0;
			j++;
		}
		i++;
		j = 0;
	}
	while (i < numRowsInBoard)
	{
		while (j < numRowsInBoard)
		{
			if (i == (numRowsInBoard - 1))
			{
				if (j % 2 == 0)
				{
					CMCheckersBoard[i][j] = 5;
				}
				else
				{
					CMCheckersBoard[i][j] = 0;
				}
			}
			else
			{
				if (i % 2 == 0)
				{
					if (j % 2 == 0)
					{
						CMCheckersBoard[i][j] = 0;
					}
					else
					{
						CMCheckersBoard[i][j] = 4;
					}
				}
				else
				{
					if (j % 2 == 0)
					{
						CMCheckersBoard[i][j] = 4;
					}
					else
					{
						CMCheckersBoard[i][j] = 0;
					}
				}
			}
			j++;
		}
		j = 0;
		i++;
	}
	return;
}
void DisplayBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	int i = 0;
	int j = 0;
	int position = 0;
	for (int count = 0; count < numRowsInBoard; count++)
	{
		while (j < numRowsInBoard)
		{
			if (CMCheckersBoard[i][j] == 0)
			{
				cout << setw(4) << position;
				position++;
			}
			else if (CMCheckersBoard[i][j] == 1)
			{
				cout << setw(4) << "WS";
				position++;
			}
			else if (CMCheckersBoard[i][j] == 2)
			{
				cout << setw(4) << "WM";
				position++;
			}
			else if (CMCheckersBoard[i][j] == 3)
			{
				cout << setw(4) << "WK";
				position++;
			}
			else if (CMCheckersBoard[i][j] == 4)
			{
				cout << setw(4) << "RS";
				position++;
			}
			else if (CMCheckersBoard[i][j] == 5)
			{
				cout << setw(4) << "RM";
				position++;
			}
			else if (CMCheckersBoard[i][j] == 6)
			{
				cout << setw(4) << "RK";
				position++;
			}
			j++;
		}
		cout << endl;
		j = 0;
		i++;
	}

	return;
}
bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
	if (player == WHITEPLAYER)
	{
		if ((CMCheckersBoard[yLoc][xLoc] == WHITEMULE || CMCheckersBoard[yLoc][xLoc] == WHITESOLDIER))
		{
			if (xLoc == 0)
			{
				if (CMCheckersBoard[(yLoc + 1)][(xLoc + 1)] == 0)
				{
					return true;
				}
				else if (CMCheckersBoard[(yLoc + 1)][(numRowsInBoard - 1)] == 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else if (xLoc == (numRowsInBoard - 1))
			{
				if (CMCheckersBoard[(yLoc + 1)][0] == 0)
				{
					return true;
				}
				else if (CMCheckersBoard[(yLoc + 1)][(xLoc - 1)] == 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				if (CMCheckersBoard[(yLoc + 1)][(xLoc + 1)] == 0)
				{
					return true;
				}
				else if (CMCheckersBoard[(yLoc + 1)][(xLoc - 1)] == 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		else if (CMCheckersBoard[yLoc][xLoc] == WHITEKING)
		{
			if (xLoc == 0)
			{
				if (yLoc == 0)
				{
					if (CMCheckersBoard[(yLoc + 1)][(xLoc + 1)] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[(yLoc + 1)][(numRowsInBoard - 1)] == 0)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (yLoc == numRowsInBoard - 1)
				{
					if (CMCheckersBoard[(yLoc - 1)][(xLoc + 1)] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[(yLoc - 1)][(numRowsInBoard - 1)] == 0)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					if (CMCheckersBoard[(yLoc + 1)][(xLoc + 1)] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[(yLoc + 1)][(numRowsInBoard - 1)] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[(yLoc - 1)][(xLoc + 1)] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[(yLoc - 1)][(numRowsInBoard - 1)] == 0)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			else if (xLoc == (numRowsInBoard - 1))
			{
				if (yLoc == 0)
				{
					if (CMCheckersBoard[(yLoc + 1)][0] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[(yLoc + 1)][(xLoc - 1)] == 0)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (yLoc == numRowsInBoard - 1)
				{
					if (CMCheckersBoard[(yLoc - 1)][(xLoc + 1)] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[(yLoc - 1)][(numRowsInBoard - 1)] == 0)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					if (CMCheckersBoard[(yLoc + 1)][0] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[(yLoc + 1)][(xLoc - 1)] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[(yLoc - 1)][(xLoc - 1)] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[(yLoc - 1)][0] == 0)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			else
			{
				if (yLoc == 0)
				{
					if (CMCheckersBoard[yLoc + 1][xLoc + 1] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[yLoc + 1][xLoc - 1] == 0)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (yLoc == numRowsInBoard - 1)
				{
					if (CMCheckersBoard[yLoc - 1][xLoc + 1] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[yLoc - 1][xLoc - 1] == 0)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					if (CMCheckersBoard[yLoc + 1][xLoc + 1] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[yLoc + 1][xLoc - 1] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[yLoc - 1][xLoc + 1] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[yLoc - 1][xLoc - 1] == 0)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}
		else
		{
			return false;
		}

	}
	else if (player == REDPLAYER)
	{
		if ((CMCheckersBoard[yLoc][xLoc] == REDMULE || CMCheckersBoard[yLoc][xLoc] == REDSOLDIER))
		{
			if (xLoc == 0)
			{
				if (CMCheckersBoard[(yLoc - 1)][(xLoc + 1)] == 0)
				{
					return true;
				}
				else if (CMCheckersBoard[(yLoc - 1)][(numRowsInBoard - 1)] == 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else if (xLoc == (numRowsInBoard - 1))
			{
				if (CMCheckersBoard[(yLoc - 1)][0] == 0)
				{
					return true;
				}
				else if (CMCheckersBoard[(yLoc - 1)][(xLoc - 1)] == 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				if (CMCheckersBoard[(yLoc - 1)][(xLoc + 1)] == 0)
				{
					return true;
				}
				else if (CMCheckersBoard[(yLoc - 1)][(xLoc - 1)] == 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		else if (CMCheckersBoard[yLoc][xLoc] == REDKING)
		{
			if (xLoc == 0)
			{
				if (yLoc == 0)
				{
					if (CMCheckersBoard[(yLoc + 1)][(xLoc + 1)] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[(yLoc + 1)][(numRowsInBoard - 1)] == 0)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (yLoc == numRowsInBoard - 1)
				{
					if (CMCheckersBoard[(yLoc - 1)][(xLoc + 1)] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[(yLoc - 1)][(numRowsInBoard - 1)] == 0)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					if (CMCheckersBoard[(yLoc + 1)][(xLoc + 1)] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[(yLoc + 1)][(numRowsInBoard - 1)] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[(yLoc - 1)][(xLoc + 1)] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[(yLoc - 1)][(numRowsInBoard - 1)] == 0)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			else if (xLoc == (numRowsInBoard - 1))
			{
				if (yLoc == 0)
				{
					if (CMCheckersBoard[(yLoc + 1)][0] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[(yLoc + 1)][(xLoc - 1)] == 0)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (yLoc == numRowsInBoard - 1)
				{
					if (CMCheckersBoard[(yLoc - 1)][(xLoc + 1)] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[(yLoc - 1)][(numRowsInBoard - 1)] == 0)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					if (CMCheckersBoard[(yLoc + 1)][0] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[(yLoc + 1)][(xLoc - 1)] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[(yLoc - 1)][(xLoc - 1)] == 0)
					{
						return true;
					}
					else if (CMCheckersBoard[(yLoc - 1)][0] == 0)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			else
			{
				return false;
			}

		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
int CountMove1Squares(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
{
	int i = 0;
	int j = 0;
	int loopcount = 0;
	int checkcount = 0;
	if (player == WHITEPLAYER)
	{
		for (; loopcount < numRowsInBoard; loopcount++)
		{
			while (j < numRowsInBoard)
			{
				if (CMCheckersBoard[i][j] == 1 || CMCheckersBoard[i][j] == 2 || CMCheckersBoard[i][j] == 3)
				{
					if (IsMove1Square(CMCheckersBoard, numRowsInBoard, player, j, i))
					{
						checkcount++;
					}
				}
				j++;
			}
			j = 0;
			i++;
		}
	}
	if (player == REDPLAYER)
	{
		for (; loopcount < numRowsInBoard; loopcount++)
		{
			while (j < numRowsInBoard)
			{
				if (CMCheckersBoard[i][j] == 4 || CMCheckersBoard[i][j] == 5 || CMCheckersBoard[i][j] == 6)
				{
					if (IsMove1Square(CMCheckersBoard, numRowsInBoard, player, j, i))
					{
						checkcount++;
					}
				}
				j++;
			}
			j = 0;
			i++;
		}
	}
	return checkcount;
}
int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
{
	int i = 0;
	int j = 0;
	int loopcount = 0;
	int checkcount = 0;
	int arraycounter = 0;
	if (player == WHITEPLAYER)
	{
		for (; loopcount < numRowsInBoard; loopcount++)
		{
			while (j < numRowsInBoard)
			{
				if (CMCheckersBoard[i][j] == 1 || CMCheckersBoard[i][j] == 2 || CMCheckersBoard[i][j] == 3)
				{
					if (IsJump(CMCheckersBoard, numRowsInBoard, player, j, i))
					{
						checkcount++;
						yLocArray[arraycounter] = i;
						xLocArray[arraycounter] = j;
						arraycounter++;
					}
				}
				j++;
			}
			j = 0;
			i++;
		}
	}
	if (player == REDPLAYER)
	{
		for (; loopcount < numRowsInBoard; loopcount++)
		{
			while (j < numRowsInBoard)
			{
				if (CMCheckersBoard[i][j] == 4 || CMCheckersBoard[i][j] == 5 || CMCheckersBoard[i][j] == 6)
				{
					if (IsJump(CMCheckersBoard, numRowsInBoard, player, j, i))
					{
						checkcount++;
						yLocArray[arraycounter] = i;
						xLocArray[arraycounter] = j;
						arraycounter++;
					}
				}
				j++;
			}
			j = 0;
			i++;
		}
	}
	return checkcount;
}
bool IsJump(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
	if (player == WHITEPLAYER)
	{
		if ((CMCheckersBoard[yLoc][xLoc] == WHITEMULE || CMCheckersBoard[yLoc][xLoc] == WHITESOLDIER))
		{
			if (xLoc == 0)
			{
				if (CMCheckersBoard[yLoc + 1][xLoc + 1] >= 4 && CMCheckersBoard[yLoc + 1][xLoc + 1] <= 6)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc + 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] >= 4 && CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] <= 6)
				{
					if (CMCheckersBoard[yLoc + 2][numRowsInBoard - 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return 0;
				}
			}
			else if (xLoc == 1)
			{
				if (CMCheckersBoard[yLoc + 1][xLoc + 1] >= 4 && CMCheckersBoard[yLoc + 1][xLoc + 1] <= 6)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc + 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc + 1][0] >= 4 && CMCheckersBoard[yLoc + 1][0] <= 6)
				{
					if (CMCheckersBoard[yLoc + 2][numRowsInBoard - 1] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return 0;
				}
			}
			else if (xLoc == (numRowsInBoard - 1))
			{
				if (CMCheckersBoard[yLoc + 1][xLoc - 1] >= 4 && CMCheckersBoard[yLoc + 1][xLoc - 1] <= 6)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc - 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc + 1][0] >= 4 && CMCheckersBoard[yLoc + 1][0] <= 6)
				{
					if (CMCheckersBoard[yLoc + 2][1] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return 0;
				}
			}
			else if (xLoc == (numRowsInBoard - 2))
			{
				if (CMCheckersBoard[yLoc + 1][xLoc - 1] >= 4 && CMCheckersBoard[yLoc + 1][xLoc - 1] <= 6)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc - 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] >= 4 && CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] <= 6)
				{
					if (CMCheckersBoard[yLoc + 2][0] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return 0;
				}
			}
			else
			{
				if (CMCheckersBoard[yLoc + 1][xLoc + 1] >= 4 && CMCheckersBoard[yLoc + 1][xLoc + 1] <= 6)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc + 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc + 1][xLoc - 1] >= 4 && CMCheckersBoard[yLoc + 1][xLoc - 1] <= 6)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc - 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return 0;
				}
			}
		}
		else if (CMCheckersBoard[yLoc][xLoc] == WHITEKING)
		{
			if (xLoc == 0)
			{
				if (CMCheckersBoard[yLoc + 1][xLoc + 1] >= 4 && CMCheckersBoard[yLoc + 1][xLoc + 1] <= 6)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc + 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc + 1] >= 4 && CMCheckersBoard[yLoc - 1][xLoc + 1] <= 6)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc + 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] >= 4 && CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] <= 6)
				{
					if (CMCheckersBoard[yLoc + 2][numRowsInBoard - 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] >= 4 && CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] <= 6)
				{
					if (CMCheckersBoard[yLoc - 2][numRowsInBoard - 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return 0;
				}
			}
			else if (xLoc == 1)
			{
				if (CMCheckersBoard[yLoc + 1][xLoc + 1] >= 4 && CMCheckersBoard[yLoc + 1][xLoc + 1] <= 6)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc + 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc + 1] >= 4 && CMCheckersBoard[yLoc - 1][xLoc + 1] <= 6)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc + 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc + 1][xLoc - 1] >= 4 && CMCheckersBoard[yLoc + 1][xLoc - 1] <= 6)
				{
					if (CMCheckersBoard[yLoc + 2][numRowsInBoard - 1] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc - 1] >= 4 && CMCheckersBoard[yLoc + 1][xLoc - 1] <= 6)
				{
					if (CMCheckersBoard[yLoc - 2][numRowsInBoard - 1] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return 0;
				}
			}
			else if (xLoc == (numRowsInBoard - 1))
			{
				if (CMCheckersBoard[yLoc + 1][xLoc - 1] >= 4 && CMCheckersBoard[yLoc + 1][xLoc - 1] <= 6)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc - 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc - 1] >= 4 && CMCheckersBoard[yLoc - 1][xLoc - 1] <= 6)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc - 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc + 1][0] >= 4 && CMCheckersBoard[yLoc + 1][0] <= 6)
				{
					if (CMCheckersBoard[yLoc + 2][1] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][0] >= 4 && CMCheckersBoard[yLoc - 1][0] <= 6)
				{
					if (CMCheckersBoard[yLoc - 2][1] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return 0;
				}
			}
			else if (xLoc == (numRowsInBoard - 2))
			{
				if (CMCheckersBoard[yLoc + 1][xLoc - 1] >= 4 && CMCheckersBoard[yLoc + 1][xLoc - 1] <= 6)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc - 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc - 1] >= 4 && CMCheckersBoard[yLoc - 1][xLoc - 1] <= 6)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc - 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc + 1][xLoc + 1] >= 4 && CMCheckersBoard[yLoc + 1][xLoc + 1] <= 6)
				{
					if (CMCheckersBoard[yLoc + 2][0] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc + 1] >= 4 && CMCheckersBoard[yLoc - 1][xLoc + 1] <= 6)
				{
					if (CMCheckersBoard[yLoc - 2][0] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return 0;
				}
			}
			else
			{
				if (CMCheckersBoard[yLoc + 1][xLoc + 1] >= 4 && CMCheckersBoard[yLoc + 1][xLoc + 1] <= 6)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc + 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc + 1][xLoc - 1] >= 4 && CMCheckersBoard[yLoc + 1][xLoc - 1] <= 6)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc - 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc + 1] >= 4 && CMCheckersBoard[yLoc - 1][xLoc + 1] <= 6)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc + 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc - 1] >= 4 && CMCheckersBoard[yLoc - 1][xLoc - 1] <= 6)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc - 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return 0;
				}
			}
		}
		else
		{
			return 0;
		}

	}
	else if (player == REDPLAYER)
	{
		if ((CMCheckersBoard[yLoc][xLoc] == REDMULE || CMCheckersBoard[yLoc][xLoc] == REDSOLDIER))
		{
			if (xLoc == 0)
			{
				if (CMCheckersBoard[yLoc - 1][xLoc + 1] >= 1 && CMCheckersBoard[yLoc - 1][xLoc + 1] <= 3)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc + 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] >= 1 && CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] <= 3)
				{
					if (CMCheckersBoard[yLoc - 2][numRowsInBoard - 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return 0;
				}
			}
			else if (xLoc == 1)
			{
				if (CMCheckersBoard[yLoc - 1][xLoc + 1] >= 1 && CMCheckersBoard[yLoc - 1][xLoc + 1] <= 3)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc + 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][0] >= 1 && CMCheckersBoard[yLoc - 1][0] <= 3)
				{
					if (CMCheckersBoard[yLoc - 2][numRowsInBoard - 1] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return 0;
				}
			}
			else if (xLoc == (numRowsInBoard - 1))
			{
				if (CMCheckersBoard[yLoc - 1][xLoc - 1] >= 1 && CMCheckersBoard[yLoc - 1][xLoc - 1] <= 3)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc - 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][0] >= 1 && CMCheckersBoard[yLoc - 1][0] <= 3)
				{
					if (CMCheckersBoard[yLoc - 2][1] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return 0;
				}
			}
			else if (xLoc == (numRowsInBoard - 2))
			{
				if (CMCheckersBoard[yLoc - 1][xLoc - 1] >= 1 && CMCheckersBoard[yLoc - 1][xLoc - 1] <= 3)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc - 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] >= 1 && CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] <= 3)
				{
					if (CMCheckersBoard[yLoc - 2][0] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return 0;
				}
			}
			else
			{
				if (CMCheckersBoard[yLoc - 1][xLoc + 1] >= 1 && CMCheckersBoard[yLoc - 1][xLoc + 1] <= 3)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc + 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc - 1] >= 1 && CMCheckersBoard[yLoc - 1][xLoc - 1] <= 3)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc - 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return 0;
				}
			}
		}
		else if (CMCheckersBoard[yLoc][xLoc] == REDKING)
		{
			if (xLoc == 0)
			{
				if (CMCheckersBoard[yLoc + 1][xLoc + 1] >= 1 && CMCheckersBoard[yLoc + 1][xLoc + 1] <= 3)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc + 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc + 1] >= 1 && CMCheckersBoard[yLoc - 1][xLoc + 1] <= 3)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc + 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] >= 1 && CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] <= 3)
				{
					if (CMCheckersBoard[yLoc + 2][numRowsInBoard - 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] >= 1 && CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] <= 3)
				{
					if (CMCheckersBoard[yLoc - 2][numRowsInBoard - 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return 0;
				}
			}
			else if (xLoc == 1)
			{
				if (CMCheckersBoard[yLoc + 1][xLoc + 1] >= 1 && CMCheckersBoard[yLoc + 1][xLoc + 1] <= 3)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc + 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc + 1] >= 1 && CMCheckersBoard[yLoc - 1][xLoc + 1] <= 3)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc + 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc + 1][xLoc - 1] >= 1 && CMCheckersBoard[yLoc + 1][xLoc - 1] <= 3)
				{
					if (CMCheckersBoard[yLoc + 2][numRowsInBoard - 1] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc - 1] >= 1 && CMCheckersBoard[yLoc + 1][xLoc - 1] <= 3)
				{
					if (CMCheckersBoard[yLoc - 2][numRowsInBoard - 1] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return 0;
				}
			}
			else if (xLoc == (numRowsInBoard - 1))
			{
				if (CMCheckersBoard[yLoc + 1][xLoc - 1] >= 1 && CMCheckersBoard[yLoc + 1][xLoc - 1] <= 3)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc - 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc - 1] >= 1 && CMCheckersBoard[yLoc - 1][xLoc - 1] <= 3)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc - 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc + 1][0] >= 1 && CMCheckersBoard[yLoc + 1][0] <= 3)
				{
					if (CMCheckersBoard[yLoc + 2][1] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][0] >= 1 && CMCheckersBoard[yLoc - 1][0] <= 3)
				{
					if (CMCheckersBoard[yLoc - 2][1] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return 0;
				}
			}
			else if (xLoc == (numRowsInBoard - 2))
			{
				if (CMCheckersBoard[yLoc + 1][xLoc - 1] >= 1 && CMCheckersBoard[yLoc + 1][xLoc - 1] <= 3)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc - 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc - 1] >= 1 && CMCheckersBoard[yLoc - 1][xLoc - 1] <= 3)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc - 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc + 1][xLoc + 1] >= 1 && CMCheckersBoard[yLoc + 1][xLoc + 1] <= 3)
				{
					if (CMCheckersBoard[yLoc + 2][0] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc + 1] >= 1 && CMCheckersBoard[yLoc - 1][xLoc + 1] <= 3)
				{
					if (CMCheckersBoard[yLoc - 2][0] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return 0;
				}
			}
			else
			{
				if (CMCheckersBoard[yLoc + 1][xLoc + 1] >= 1 && CMCheckersBoard[yLoc + 1][xLoc + 1] <= 3)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc + 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc + 1][xLoc - 1] >= 1 && CMCheckersBoard[yLoc + 1][xLoc - 1] <= 3)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc - 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc + 1] >= 1 && CMCheckersBoard[yLoc - 1][xLoc + 1] <= 3)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc + 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else if (CMCheckersBoard[yLoc - 1][xLoc - 1] >= 1 && CMCheckersBoard[yLoc - 1][xLoc - 1] <= 3)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc - 2] == 0)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return 0;
				}
			}
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	int RMule = 0;
	int RSoldier = 0;
	int RKing = 0;
	int WMule = 0;
	int WSoldier = 0;
	int WKing = 0;

	for (int i = 0; i < numRowsInBoard; i++)
	{
		for (int j = 0; j < numRowsInBoard; j++)
		{
			if (CMCheckersBoard[i][j] == 0)
			{

			}
			else if (CMCheckersBoard[i][j] == WHITESOLDIER)
			{
				WSoldier++;
			}
			else if (CMCheckersBoard[i][j] == WHITEMULE)
			{
				WMule++;
			}
			else if (CMCheckersBoard[i][j] == WHITEKING)
			{
				WKing++;
			}
			else if (CMCheckersBoard[i][j] == REDSOLDIER)
			{
				RSoldier++;
			}
			else if (CMCheckersBoard[i][j] == REDMULE)
			{
				RMule++;
			}
			else //REDKING
			{
				RKing++;
			}
		}
	}
	if (RMule == 0)
	{
		cout << " The Red Player has won the game by losing all of the Red Mules" << endl;
		return true;
	}
	else if (WMule == 0)
	{
		cout << " The White Player has won the game by losing all of the White Mules" << endl;
		return true;
	}
	else if (RSoldier == 0 && WKing == 0)
	{
		cout << "The White Player has won by capturing all of the red players soldiers and kings" << endl;
		return true;
	}
	else if (WSoldier == 0 && WKing == 0)
	{
		cout << "The Red Player has won by capturing all of the white players soldiers and kings" << endl;
		return true;
	}
	else
	{
		return false;
	}
}
bool MakeMove(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool & jumped)
{
	int xdistance = 0;
	int ydistance = 0;
	int fromSquareNumx = fromSquareNum % numRowsInBoard;
	int fromSquareNumy = fromSquareNum / numRowsInBoard;
	int toSquareNumx = toSquareNum % numRowsInBoard;
	int toSquareNumy = toSquareNum / numRowsInBoard;


	if (player == WHITEPLAYER)
	{
		xdistance = toSquareNumx - fromSquareNumx;
		ydistance = toSquareNumy - fromSquareNumy;
		if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == WHITEMULE || CMCheckersBoard[fromSquareNumy][fromSquareNumx] == WHITESOLDIER)
		{
			if (fromSquareNumx == numRowsInBoard - 2)
			{
				if (ydistance == 2) // jumping
				{
					if (toSquareNumx == 0)
					{
						CMCheckersBoard[fromSquareNumy + 2][0] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][numRowsInBoard - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						if (toSquareNumy == numRowsInBoard - 1)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == WHITEMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx + 2] = WHITEKING;
						}
						return true;

					}
					else if (xdistance == -2)
					{
						CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						if (toSquareNumy == numRowsInBoard - 1)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == WHITEMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx - 2] = WHITEKING;
						}
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == 1)
				{
					if (xdistance == 1)
					{
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						if (toSquareNumy == numRowsInBoard - 1)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == WHITEMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = WHITEKING;
						}
						return true;
					}
					else if (xdistance == -1)
					{
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						if (toSquareNumy == numRowsInBoard - 1)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == WHITEMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = WHITEKING;
						}
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance < 0) //piece moving in wrong direction
				{
					return false;
				}
				else // something went wrong
				{
					return false;
				}
			}
			else if (fromSquareNumx == 1)
			{
				if (ydistance == 2) // jumping
				{
					if (xdistance == 2)
					{
						CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx + 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						if (toSquareNumy == numRowsInBoard - 1)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == WHITEMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx + 2] = WHITEKING;
						}
						return true;

					}
					else if (toSquareNumx == numRowsInBoard - 1)
					{
						CMCheckersBoard[fromSquareNumy + 2][numRowsInBoard - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][0] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						if (toSquareNumy == numRowsInBoard - 1)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == WHITEMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx - 2] = WHITEKING;
						}
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == 1)
				{
					if (xdistance == 1)
					{
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						if (toSquareNumy == numRowsInBoard - 1)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == WHITEMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = WHITEKING;
						}
						return true;
					}
					else if (xdistance == -1)
					{
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						if (toSquareNumy == numRowsInBoard - 1)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == WHITEMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = WHITEKING;
						}
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance < 0) //piece moving in wrong direction
				{
					return false;
				}
				else // something went wrong
				{
					return false;
				}
			}
			else if (fromSquareNumx == 0)
			{
				if (ydistance == 2) // jumping
				{
					if (xdistance == 2)
					{
						CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx + 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						if (toSquareNumy == numRowsInBoard - 1)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == WHITEMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx + 2] = WHITEKING;
						}
						return true;

					}
					else if (toSquareNumx == (numRowsInBoard - 2))
					{
						CMCheckersBoard[fromSquareNumy + 2][numRowsInBoard - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][numRowsInBoard - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						if (toSquareNumy == numRowsInBoard - 1)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == WHITEMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx - 2] = WHITEKING;
						}
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == 1)
				{
					if (xdistance == 1)
					{
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						if (toSquareNumy == numRowsInBoard - 1)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == WHITEMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = WHITEKING;
						}
						return true;
					}
					else if (toSquareNumx == numRowsInBoard - 1)
					{
						CMCheckersBoard[fromSquareNumy + 1][numRowsInBoard - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						if (toSquareNumy == numRowsInBoard - 1)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == WHITEMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = WHITEKING;
						}
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance < 0) //piece moving in wrong direction
				{
					return false;
				}
				else // something went wrong
				{
					return false;
				}
			}
			else if (fromSquareNumx == (numRowsInBoard - 1))
			{
				if (ydistance == 2) // jumping
				{
					if (toSquareNumx == 1)
					{
						CMCheckersBoard[fromSquareNumy + 2][1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][0] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						if (toSquareNumy == numRowsInBoard - 1)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == WHITEMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx + 2] = WHITEKING;
						}
						return true;
					}
					else if (xdistance == -2)
					{
						CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						if (toSquareNumy == numRowsInBoard - 1)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == WHITEMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx - 2] = WHITEKING;
						}
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == 1)
				{
					if (toSquareNumx == 0)
					{
						CMCheckersBoard[fromSquareNumy + 1][0] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						if (toSquareNumy == numRowsInBoard - 1)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == WHITEMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = WHITEKING;
						}
						return true;
					}
					else if (xdistance == -1)
					{
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						if (toSquareNumy == numRowsInBoard - 1)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == WHITEMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = WHITEKING;
						}
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance < 0) //piece moving in wrong direction
				{
					return false;
				}
				else // something went wrong
				{
					return false;
				}
			}
			else
			{
				if (abs(xdistance) > 2 || abs(ydistance) > 2)
				{

					return false; //piece moving too far
				}
				else if (ydistance == 2) // jumping
				{
					if (xdistance == 2)
					{
						CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx + 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						if (toSquareNumy == numRowsInBoard - 1)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == WHITEMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx + 2] = WHITEKING;
						}
						return true;

					}

					else if (xdistance == -2)
					{
						CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						if (toSquareNumy == numRowsInBoard - 1)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == WHITEMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx - 2] = WHITEKING;
						}
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == 1)
				{
					if (xdistance == 1)
					{
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						if (toSquareNumy == numRowsInBoard - 1)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == WHITEMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = WHITEKING;
						}
						return true;
					}
					else if (xdistance == -1)
					{
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						if (toSquareNumy == numRowsInBoard - 1)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == WHITEMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = WHITEKING;
						}
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance < 0) //piece moving in wrong direction
				{
					return false;
				}
				else // something went wrong
				{
					return false;
				}
			}
		}
		else //CMCheckersBoard[fromSquareNumy][fromSquareNumy] == WHITEKING
		{
			if (fromSquareNumx == numRowsInBoard - 2)
			{
				if (ydistance == 2) // jumping
				{
					if (toSquareNumx == 0)
					{
						CMCheckersBoard[fromSquareNumy + 2][0] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][numRowsInBoard - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;

					}
					else if (xdistance == -2)
					{
						CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == 1)
				{
					if (xdistance == 1)
					{
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else if (xdistance == -1)
					{
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == -2) // jumping
				{
					if (toSquareNumx == 0)
					{
						CMCheckersBoard[fromSquareNumy - 2][0] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][numRowsInBoard - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;
					}
					else if (xdistance == -2)
					{
						CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == -1)
				{
					if (xdistance == +1)
					{
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else if (xdistance == -1)
					{
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else if (fromSquareNumx == 1)
			{
				if (ydistance == 2) // jumping
				{
					if (xdistance == 2)
					{
						CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx + 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;

					}

					else if (toSquareNumx == numRowsInBoard - 1)
					{
						CMCheckersBoard[fromSquareNumy + 2][numRowsInBoard - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][0] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == 1)
				{
					if (xdistance == 1)
					{
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else if (xdistance == -1)
					{
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == -2) // jumping
				{
					if (xdistance == 2)
					{
						CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx + 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;

					}
					else if (toSquareNumx == numRowsInBoard - 1)
					{
						CMCheckersBoard[fromSquareNumy - 2][numRowsInBoard - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][0] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == -1)
				{
					if (xdistance == +1)
					{
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else if (xdistance == -1)
					{
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}

			}
			else if (fromSquareNumx == numRowsInBoard - 1)
			{
				if (ydistance == 2) // jumping
				{
					if (toSquareNumx == 1)
					{
						CMCheckersBoard[fromSquareNumy + 2][1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][0] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;

					}
					else if (xdistance == -2)
					{
						CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == 1)
				{
					if (toSquareNumx == 0)
					{
						CMCheckersBoard[fromSquareNumy + 1][0] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else if (xdistance == -1)
					{
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == -2) // jumping
				{
					if (toSquareNumx == 1)
					{
						CMCheckersBoard[fromSquareNumy - 2][1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][0] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;

					}
					else if (xdistance == -2)
					{
						CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == -1)
				{
					if (toSquareNumx == 0)
					{
						CMCheckersBoard[fromSquareNumy - 1][0] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else if (xdistance == -1)
					{
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}


			}
			else if (fromSquareNumx == 0)
			{
				if (ydistance == 2) // jumping
				{
					if (xdistance == 2)
					{
						CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx + 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;

					}
					else if (toSquareNumx == numRowsInBoard - 2)
					{
						CMCheckersBoard[fromSquareNumy + 2][numRowsInBoard - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][numRowsInBoard - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == 1)
				{
					if (xdistance == 1)
					{
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else if (toSquareNumx == numRowsInBoard - 1)
					{
						CMCheckersBoard[fromSquareNumy + 1][numRowsInBoard - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == -2) // jumping
				{
					if (xdistance == 2)
					{
						CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx + 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;

					}
					else if (toSquareNumx == numRowsInBoard - 2)
					{
						CMCheckersBoard[fromSquareNumy - 2][numRowsInBoard - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][numRowsInBoard - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == -1)
				{
					if (xdistance == +1)
					{
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else if (toSquareNumx == numRowsInBoard - 1)
					{
						CMCheckersBoard[fromSquareNumy - 1][numRowsInBoard - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				if (abs(xdistance) > 2 || abs(ydistance) > 2)
				{

					return false; //piece moving too far
				}
				else if (ydistance == 2) // jumping
				{
					if (xdistance == 2)
					{
						CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx + 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;

					}

					else if (xdistance == -2)
					{
						CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == 1)
				{
					if (xdistance == 1)
					{
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else if (xdistance == -1)
					{
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else
					{
						return false;
					}
				}


				else if (ydistance == -2) // jumping
				{
					if (xdistance == 2)
					{
						CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx + 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;

					}

					else if (xdistance == -2)
					{
						CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == -1)
				{
					if (xdistance == +1)
					{
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else if (xdistance == -1)
					{
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
		}
	}
	else if (player == REDPLAYER)
	{
		xdistance = toSquareNumx - fromSquareNumx;
		ydistance = toSquareNumy - fromSquareNumy;
		if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == REDMULE || CMCheckersBoard[fromSquareNumy][fromSquareNumx] == REDSOLDIER)
		{
			if (fromSquareNumx == numRowsInBoard - 2)
			{
				if (ydistance == -2) // jumping
				{
					if (toSquareNumx == 0)
					{
						CMCheckersBoard[fromSquareNumy - 2][0] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][numRowsInBoard - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						if (toSquareNumy == 0)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == REDMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx + 2] = REDKING;
						}
						return true;
					}

					else if (xdistance == -2)
					{
						CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						if (toSquareNumy == 0)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == REDMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx - 2] = REDKING;
						}
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == -1)
				{
					if (xdistance == +1)
					{
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						if (toSquareNumy == 0)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == REDMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = REDKING;
						}
						return true;
					}
					else if (xdistance == -1)
					{
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						if (toSquareNumy == 0)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == REDMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = REDKING;
						}
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance > 0) //piece moving in wrong direction
				{
					return false;
				}
				else // something went wrong
				{
					return false;
				}
			}
			else if (fromSquareNumx == 1)
			{
				if (ydistance == -2) // jumping
				{
					if (toSquareNumx == numRowsInBoard - 1)
					{
						CMCheckersBoard[fromSquareNumy - 2][numRowsInBoard - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][0] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						if (toSquareNumy == 0)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == REDMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx + 2] = REDKING;
						}
						return true;
					}
					else if (xdistance == -2)
					{
						CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						if (toSquareNumy == 0)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == REDMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx - 2] = REDKING;
						}
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == -1)
				{
					if (xdistance == +1)
					{
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						if (toSquareNumy == 0)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == REDMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = REDKING;
						}
						return true;
					}
					else if (xdistance == -1)
					{
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						if (toSquareNumy == 0)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == REDMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = REDKING;
						}
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance > 0) //piece moving in wrong direction
				{
					return false;
				}
				else // something went wrong
				{
					return false;
				}
			}
			else if (fromSquareNumx == 0)
			{
				if (ydistance == -2) // jumping
				{
					if (xdistance == 2)
					{
						CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx + 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						if (toSquareNumy == 0)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == REDMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx + 2] = REDKING;
						}
						return true;
					}

					else if (toSquareNumx == numRowsInBoard - 2)
					{
						CMCheckersBoard[fromSquareNumy - 2][numRowsInBoard - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][numRowsInBoard - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						if (toSquareNumy == 0)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == REDMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx - 2] = REDKING;
						}
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == -1)
				{
					if (xdistance == +1)
					{
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						if (toSquareNumy == 0)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == REDMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = REDKING;
						}
						return true;
					}
					else if (toSquareNumx == numRowsInBoard - 1)
					{
						CMCheckersBoard[fromSquareNumy - 1][numRowsInBoard - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						if (toSquareNumy == 0)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == REDMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = REDKING;
						}
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance > 0) //piece moving in wrong direction
				{
					return false;
				}
				else // something went wrong
				{
					return false;
				}
			}
			else if (fromSquareNumx == (numRowsInBoard - 1))
			{
				if (ydistance == -2) // jumping
				{
					if (toSquareNumx == 1)
					{
						CMCheckersBoard[fromSquareNumy - 2][1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][0] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						if (toSquareNumy == 0)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == REDMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx + 2] = REDKING;
						}
						return true;
					}
					else if (toSquareNumx == numRowsInBoard - 3)
					{
						CMCheckersBoard[fromSquareNumy - 2][numRowsInBoard - 3] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][numRowsInBoard - 2] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						if (toSquareNumy == 0)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == REDMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx - 2] = REDKING;
						}
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == -1)
				{
					if (toSquareNumx == 0)
					{
						CMCheckersBoard[fromSquareNumy - 1][0] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						if (toSquareNumy == 0)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == REDMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = REDKING;
						}
						return true;
					}
					else if (toSquareNumx == numRowsInBoard - 2)
					{
						CMCheckersBoard[fromSquareNumy - 1][numRowsInBoard - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						if (toSquareNumy == 0)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == REDMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = REDKING;
						}
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance > 0) //piece moving in wrong direction
				{
					return false;
				}
				else // something went wrong
				{
					return false;
				}
			}
			else
			{
				if (abs(xdistance) > 2 || abs(ydistance) > 2)
				{

					return false; //piece moving too far
				}
				else if (ydistance == -2) // jumping
				{
					if (xdistance == 2)
					{
						CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx + 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						if (toSquareNumy == 0)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == REDMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx + 2] = REDKING;
						}
						return true;
					}

					else if (xdistance == -2)
					{
						CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						if (toSquareNumy == 0)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == REDMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx - 2] = REDKING;
						}
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == -1)
				{
					if (xdistance == +1)
					{
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						if (toSquareNumy == 0)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == REDMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = REDKING;
						}
						return true;
					}
					else if (xdistance == -1)
					{
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						if (toSquareNumy == 0)
						{
							if (CMCheckersBoard[fromSquareNumy][fromSquareNumx] == REDMULE)
							{
								cout << "Enter any character to terminate the game then press the enter key" << endl;
								char c = '\0';
								cin >> c;
								return 0;
							}
							CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = REDKING;
						}
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance > 0) //piece moving in wrong direction
				{
					return false;
				}
				else // something went wrong
				{
					return false;
				}
			}
		}
		else //CMCheckersBoard[fromSquareNumy][fromSquareNumy] == REDKING
		{
			if (fromSquareNumx == numRowsInBoard - 2)
			{
				if (ydistance == 2) // jumping
				{
					if (toSquareNumx == 0)
					{
						CMCheckersBoard[fromSquareNumy + 2][0] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][numRowsInBoard - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;

					}
					else if (xdistance == -2)
					{
						CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == 1)
				{
					if (xdistance == 1)
					{
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else if (xdistance == -1)
					{
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == -2) // jumping
				{
					if (toSquareNumx == 0)
					{
						CMCheckersBoard[fromSquareNumy - 2][0] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][numRowsInBoard - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;
					}
					else if (xdistance == -2)
					{
						CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == -1)
				{
					if (xdistance == +1)
					{
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else if (xdistance == -1)
					{
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else if (fromSquareNumx == 1)
			{
				if (ydistance == 2) // jumping
				{
					if (xdistance == 2)
					{
						CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx + 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;

					}

					else if (toSquareNumx == numRowsInBoard - 1)
					{
						CMCheckersBoard[fromSquareNumy + 2][numRowsInBoard - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][0] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == 1)
				{
					if (xdistance == 1)
					{
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else if (xdistance == -1)
					{
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == -2) // jumping
				{
					if (xdistance == 2)
					{
						CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx + 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;

					}
					else if (toSquareNumx == numRowsInBoard - 1)
					{
						CMCheckersBoard[fromSquareNumy - 2][numRowsInBoard - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][0] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == -1)
				{
					if (xdistance == +1)
					{
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else if (xdistance == -1)
					{
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}

			}
			else if (fromSquareNumx == numRowsInBoard - 1)
			{
				if (ydistance == 2) // jumping
				{
					if (toSquareNumx == 1)
					{
						CMCheckersBoard[fromSquareNumy + 2][1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][0] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;

					}
					else if (xdistance == -2)
					{
						CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == 1)
				{
					if (toSquareNumx == 0)
					{
						CMCheckersBoard[fromSquareNumy + 1][0] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else if (xdistance == -1)
					{
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == -2) // jumping
				{
					if (toSquareNumx == 1)
					{
						CMCheckersBoard[fromSquareNumy - 2][1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][0] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;

					}
					else if (xdistance == -2)
					{
						CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == -1)
				{
					if (toSquareNumx == 0)
					{
						CMCheckersBoard[fromSquareNumy - 1][0] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else if (xdistance == -1)
					{
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}


			}
			else if (fromSquareNumx == 0)
			{
				if (ydistance == 2) // jumping
				{
					if (xdistance == 2)
					{
						CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx + 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;

					}
					else if (toSquareNumx == numRowsInBoard - 2)
					{
						CMCheckersBoard[fromSquareNumy + 2][numRowsInBoard - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][numRowsInBoard - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == 1)
				{
					if (xdistance == 1)
					{
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else if (toSquareNumx == numRowsInBoard - 1)
					{
						CMCheckersBoard[fromSquareNumy + 1][numRowsInBoard - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == -2) // jumping
				{
					if (xdistance == 2)
					{
						CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx + 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;

					}
					else if (toSquareNumx == numRowsInBoard - 2)
					{
						CMCheckersBoard[fromSquareNumy - 2][numRowsInBoard - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][numRowsInBoard - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == -1)
				{
					if (xdistance == +1)
					{
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else if (toSquareNumx == numRowsInBoard - 1)
					{
						CMCheckersBoard[fromSquareNumy - 1][numRowsInBoard - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				{ }
				if (abs(xdistance) > 2 || abs(ydistance) > 2)
				{

					return false; //piece moving too far
				}
				else if (ydistance == 2) // jumping
				{
					if (xdistance == 2)
					{
						CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx + 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;

					}

					else if (xdistance == -2)
					{
						CMCheckersBoard[fromSquareNumy + 2][fromSquareNumx - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == 1)
				{
					if (xdistance == 1)
					{
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx + 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else if (xdistance == -1)
					{
						CMCheckersBoard[fromSquareNumy + 1][fromSquareNumx - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == -2) // jumping
				{
					if (xdistance == 2)
					{
						CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx + 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;

					}

					else if (xdistance == -2)
					{
						CMCheckersBoard[fromSquareNumy - 2][fromSquareNumx - 2] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = 0;
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						jumped = true;
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (ydistance == -1)
				{
					if (xdistance == +1)
					{
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx + 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else if (xdistance == -1)
					{
						CMCheckersBoard[fromSquareNumy - 1][fromSquareNumx - 1] = CMCheckersBoard[fromSquareNumy][fromSquareNumx];
						CMCheckersBoard[fromSquareNumy][fromSquareNumx] = 0;
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
		}
	}
	else
	{
		return false;
	}
}
bool CheckList(int inArray1[], int inArray2[], int xIndex, int yIndex)
{
	if (xIndex == 0)
	{
		return true;
	}
	else if (yIndex == 0)
	{
		return false;
	}
	else
	{
		return false;
	}

}