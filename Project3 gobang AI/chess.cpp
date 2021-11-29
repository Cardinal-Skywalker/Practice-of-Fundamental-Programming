#include<iostream>
#include"chess.h"

void Board::renew_ang(int row, int col)
{
	//ang_0
	for (int i = 0; i < 5; i++)
	{
		int x = 0;
		for (int j = col - i; j < col + 5 - i; j++)
		{
			if (j >= 19)
			{
				x = 0;
				break;
			}
			else if(j < 0 )
			{
				x = 0;
				break;
			}
			else if (chess[row][j].type == -1)
				continue;
			else if (chess[row][j].type == chess[row][col].type)
			{
				x++;
			}
			else
			{
				x = 0;
				break;
			}
		}
		chess[row][col].ang_0[i] = x;
	}

	//ang_90
	for (int i = 0; i < 5; i++)
	{
		int x = 0;
		for (int j = row - i; j < row + 5 - i; j++)
		{
			if (j >= 19)
			{
				x = 0;
				break;
			}
			else if (j < 0)
			{
				x = 0;
				break;
			}
			else if (chess[j][col].type == -1)
				continue;
			else if (chess[j][col].type == chess[row][col].type)
			{
				x++;
			}
			else
			{
				x = 0;
				break;
			}
		}
		chess[row][col].ang_90[i] = x;
	}

	//ang_45
	for (int i = 0; i < 5; i++)
	{
		int x = 0;
		int k = col + i;
		for (int j = row - i; j < row + 5 - i; j++)
		{
			if (k <= col + i - 5) break;
			if (j >= 19||k>=19)
			{
				x = 0;
				break;
			}
			else if (j < 0||k<0)
			{
				x = 0;
				break;
			}
			else if (chess[j][k].type == -1)
			{
				k--;
				continue;
			}
				
			else if (chess[j][k].type == chess[row][col].type)
			{
				x++;
			}
			else
			{
				x = 0;
				break;
			}
			k--;
		}
		chess[row][col].ang_45[i] = x;
	}

	//ang_135
	for (int i = 0; i < 5; i++)
	{
		int x = 0;
		int k = col - i;
		for (int j = row - i; j < row + 5 - i; j++)
		{
			if (k >= col - i + 5) break;
			if (j >= 19 || k >= 19)
			{
				x = 0;
				break;
			}
			else if (j < 0 || k < 0)
			{
				x = 0;
				break;
			}
			else if (chess[j][k].type == -1)
			{
				k++;
				continue;
			}

			else if (chess[j][k].type == chess[row][col].type)
			{
				x++;
			}
			else
			{
				x = 0;
				break;
			}
			k++;
		}
		chess[row][col].ang_135[i] = x;
	}
	chess[row][col].cal_val();
}

int  Board::get_point(int row, int col)
{
	if (chess[row][col].type != -1)
		return -1;
	else
	{

		int total = 0;
		chess[row][col].type = 0;
		renew_ang(row, col);
		total += chess[row][col].val;
		for (int i = row - 4;i < row + 5; i++)
		{
			if (i < 0 || i>19)
				continue;
			else
			{
				for (int j = col - 4; j < col + 5; j++)
				{
					if (j < 0 || j>19)
						continue;
					else if (chess[i][j].type = -1) continue;
					else
					{
						int past = chess[i][j].val;
						renew_ang(i,j);
						int dif = chess[i][j].val - past;
						dif = dif < 0 ? -dif : dif;
						total += dif;
						chess[row][col].type = -1;
						renew_ang(i, j);
						chess[row][col].type = 0;
					}
				}
			}
		}

		chess[row][col].type = 1;
		renew_ang(row, col);
		total += chess[row][col].val;
		for (int i = row - 4; i < row + 5; i++)
		{
			if (i < 0 || i>19)
				continue;
			else
			{
				for (int j = col - 4; j < col + 5; j++)
				{
					if (j < 0 || j>19)
						continue;
					else if (chess[i][j].type = -1) continue;
					else
					{
						int past = chess[i][j].val;
						renew_ang(i, j);
						int dif = chess[i][j].val - past;
						dif = dif < 0 ? -dif : dif;
						total += dif;
						chess[row][col].type = -1;
						renew_ang(i, j);
						chess[row][col].type = 1;
					}
				}
			}
		}

		return total;
	}
}

Board board;