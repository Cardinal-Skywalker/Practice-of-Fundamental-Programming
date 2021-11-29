#pragma once
#include<iostream>
using namespace std;

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
		for (int i = 0; i < 5; i++)
		{
			int s = 0;
			s += ang_0[i] + ang_45[i] + ang_90[i] + ang_135[i];
			val = s;
		}
	}
};

class Board
{
public:
	Chess chess[19][19];
	void renew_ang(int row,int col);
	int get_point(int row, int col);
	Board()
	{
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				chess[i][j].initchess(i, j);
			}
		}
	}
};

