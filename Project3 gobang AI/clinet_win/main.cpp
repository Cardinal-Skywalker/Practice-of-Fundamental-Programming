#include "Reversi.h"
#include<fstream>
#include<conio.h>
//#include"testGUI.h"
using namespace std;
void game_replay(int num);
Board board;
int historynum;
int chessnum = 1;

bool findinlearn = true;
string flag;

int main() {
	board.board_display();
	ifstream  in_file("D:/Practice-of-Fundamental-Programming/Project3 gobang AI/clinet_win/informations.txt", ios::in);
	if (!in_file) {
		cerr << "1";
		system("pause");
		exit(-1); }
	in_file >> historynum;
	in_file.close();
	/* Normal code */
    srand((unsigned int)(time(nullptr)));
    Reversi reversi = Reversi();
    reversi.gameStart();
	ofstream  out_file("D:/Practice-of-Fundamental-Programming/Project3 gobang AI/clinet_win/informations.txt", ios::out);
	if (!out_file) exit(-1);
	out_file << historynum;
	out_file.close();
	cout << findinlearn << endl;
	system("pause");

	///* A simple GUI for test*/
	//Game test;
	////test.HumanGame(); 
	//test.AIGame(1); //humanColor = WHITE
	game_replay(historynum);
	return 0;
}


void game_replay(int num)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD word1 = BACKGROUND_RED| BACKGROUND_GREEN;
	WORD word2 = BACKGROUND_INTENSITY;
	int gamenum = num+1;
	char ch;
	for (;;)
	{
		cout << "选择对局：" << gamenum << endl;
		ch = _getch();
		if (ch == 27) break;
		ch = _getch();
		if (ch == 72)
			gamenum--;
		else if (ch == 80)
			gamenum++;
		if (gamenum <= 1)
			gamenum = 1;
		else if (gamenum >= num)
			gamenum = num;
		string path = "D:/Practice-of-Fundamental-Programming/Project3 gobang AI/clinet_win/history/historygame";
		char a[10] = { '\0' };
		sprintf_s(a, "%d", gamenum);
		path += a;
		path += ".txt";
		ifstream in(path, ios::in);
		int totalstep = 0;
		string line;
		while (!in.eof())
		{
			totalstep++;
			getline(in, line);
		}
		in.close();
		
		char ch2 = '0';
		int stepnum=0;
		for (;;)
		{
			ifstream in_file(path, ios::in);
			system("cls");
			cout << "第" << gamenum << "局的复盘：" << endl;
			if (ch2 == 77)
				stepnum++;
			else if (ch2 == 75)
				stepnum--;
			if (stepnum <= 0)
				stepnum = 1;
			else if (stepnum >= totalstep+1)
				stepnum = totalstep+1;
			int chessboard[19][19];
			cout << "第"<<stepnum - 1<<"步" << endl;
			memset(chessboard, -1, 19 * 19 * sizeof(int));
			string oneline;
			for (int k = 0; k < stepnum-1; k++)
			{
				getline(in_file, oneline);
				int row = 10 * (oneline[3] - '0') + oneline[4] - '0';
				int col = 10 * (oneline[5] - '0') + oneline[6] - '0';
				int color = oneline[7] - '0';
				chessboard[row][col] = color;
			}
			in_file.close();
			for (int i = 0; i < 19; i++)
			{
				SetConsoleTextAttribute(handle, word1);
				for (int j = 0; j < 19; j++)
				{
					if (chessboard[i][j] == -1)
						cout << "·";
					else if (chessboard[i][j] == 0)
						cout << "○";
					else if (chessboard[i][j] == 1)
						cout << "●";
				}

				cout << endl;
				SetConsoleTextAttribute(handle, word2);
			}
			SetConsoleTextAttribute(handle, word2);
			ch2 = _getch();
			if (ch2 == 27) break;
			ch2 = _getch();
		}
	}
}