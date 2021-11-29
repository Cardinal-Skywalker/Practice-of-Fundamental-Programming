#ifndef Reversi_h
#define Reversi_h
#include <stdio.h>
#include <ctime>
#include "ClientSocket.h"
//#include"chess.h"

using namespace std;

class Reversi{
private:
    ClientSocket client_socket;
    int ownColor;
    int oppositeColor;

	//function 

	 // according to chessman position (row , col) , generate one step message in order to send to server
    void generateOneStepMessage(int row, int col);

public:
	pair<int, int> step();
    
    void saveChessBoard();

	void handleMessage(int row, int col, int color);
public:
    Reversi();
    ~Reversi();
	void setOwnColor(int color);

    void authorize(const char *id , const char *pass);
    
    void gameStart();
    
    void gameOver();
    
    void roundStart(int round);
    
    void oneRound();
    
    void roundOver(int round);
    
    int observe();
    
};


struct Chess
{
	int type;
	int row;
	int col;

	int val;
	int ang_0[5];
	int ang_45[5];
	int ang_90[5];
	int ang_135[5];

	int num_3;
	int num_4;
	Chess()
	{
		type = -1;
		row = -1;
		col = -1;
		val = 0;
		for (int i = 0; i < 5; i++)
		{
			ang_0[i] = 0;
			ang_45[i] = 0;
			ang_90[i] = 0;
			ang_135[i] = 0;

		}
	}
	void initchess(int i, int j)
	{
		row = i;
		col = j;
	}
	void cal_val()
	{

		int num_3 = 0;
		int num_4 = 0;
		int num_5 = 0;
		int s = 0;
		for (int i = 0; i < 5; i++)
		{
			s += ang_0[i] + ang_45[i] + ang_90[i] + ang_135[i];
		
			if (ang_0[i] == 3)
			{
				num_3++;
			}
			if (ang_45[i] == 3)
			{
				num_3++;
			}
			if (ang_90[i] == 3)
			{
				num_3++;
			}
			if (ang_135[i] == 3)
			{
				num_3++;
			}


			if (ang_0[i] == 4)
			{
				num_4++;
			}
			if (ang_45[i] == 4)
			{
				num_4++;
			}
			if (ang_90[i] == 4)
			{
				num_4++;
			}
			if (ang_135[i] == 4)
			{
				num_4++;
			}

			if (ang_0[i] == 5)
			{
				num_5++;
			}
			if (ang_45[i] == 5)
			{
				num_5++;
			}
			if (ang_90[i] == 5)
			{
				num_5++;
			}
			if (ang_135[i] == 5)
			{
				num_5++;
			}
		}
			val = s;
			if (num_3 >= 2 )
			{
				val = 10000;
			}
			if (num_3 >= 4)
			{
				val = 100000;
			}
			if (num_4 >= 2 || (num_3 - 1) * num_4 != 0)
			{
				val = 4000000;
			}
			if (num_5 != 0)
			{
				val = 100000000;
			}
	}
};

class Board
{
public:
	Chess chess[19][19];
	void handlemes(int row, int col, int color);
	void renew_ang(int row, int col);
	int get_point(int row, int col,int color);
	void board_display()
	{
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
				cout <<chess[i][j].type << ' ';
			cout << endl;
		}
	}
	Board()
	{
		init_board();
	}
	void init_board()
	{
	for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				chess[i][j].initchess(i, j);
				chess[i][j].type = -1;
			}
		}
		chess[9][9].type = 1;
		renew_ang(9,9);
	}
};

#endif /* Reversi_h */
