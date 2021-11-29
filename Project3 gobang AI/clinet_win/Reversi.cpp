

#define _CRT_SECURE_NO_WARNINGS
#include "Reversi.h"
#include<fstream>
#include<string>
//#include"chess.h"
using namespace std;
#define random(x) (rand()%x)
#define ROWS 19
#define COLS 19
#define ROUNDS 3
extern Board board;
extern int historynum;
extern int chessnum;
extern string flag;
extern bool findinlearn;

void AI_study();

Reversi::Reversi(){
    client_socket = ClientSocket();
    oppositeColor = ownColor = -1;
}

Reversi::~Reversi(){}
void Reversi::setOwnColor(int color)
{
	if (color != 0 || color != 1)
		return;
	ownColor = color;
	oppositeColor = 1 - color;
}
;

/*
 send id and password to server by socket
 rtn != 0 represents socket transfer error
 */
void Reversi::authorize(const char *id , const char *pass)
{
    client_socket.connectServer();
    std::cout << "Authorize " << id << std::endl;
    char msgBuf[BUFSIZE];
    memset(msgBuf , 0 , BUFSIZE);
    msgBuf[0] = 'A';
    memcpy(&msgBuf[1] , id , 9);
    memcpy(&msgBuf[10] , pass , 6);
    int rtn = client_socket.sendMsg(msgBuf);
    if (rtn != 0) printf("Authorized Failed!\n");
}

// 用户id输入，服务器上需要有对应的账号密码：对应文件 players-0.txt
void Reversi::gameStart()
{
    char id[12] = {0}, passwd[10] = {0};
	strcpy(id, ID);
	strcpy(passwd, PASSWORD);
    authorize(id, passwd);
    
    printf("Game Start!\n");
    
    for (int round = 0 ; round < ROUNDS ; round++){
        roundStart(round);
        oneRound();
        roundOver(round);
		AI_study();
    }
    gameOver();
    client_socket.close();
}

void Reversi::gameOver()
{
    printf("Game Over!\n");
	
}

//发一次消息，走哪一步，等两个消息，1.自己的步数行不行 2.对面走了哪一步 
void Reversi::roundStart(int round)
{
    printf("Round %d Ready Start!\n" , round);
	chessnum = 1;
	findinlearn = true;
	//findinlearn = false;
	historynum++;
	string path = "D:/Practice-of-Fundamental-Programming/Project3 gobang AI/clinet_win/history/historygame";
	char a[10] = { '\0' };
	sprintf_s(a, "%d", historynum);
	path += a;
	path += ".txt";
	ofstream out(path, ios::out);
	if (!out)
	{
		exit(-1);
	}
	out << "00109090";//步数，位置，颜色
	out.close();
	flag = "01";
	chessnum++;
	board.init_board();
	board.board_display();
    // first time receive msg from server
    int rtn = client_socket.recvMsg();
    if (rtn != 0) return ;
    if(strlen(client_socket.getRecvMsg()) < 2)
        printf("Authorize Failed!\n");
    else
        printf("Round start received msg %s\n", client_socket.getRecvMsg());
    switch (client_socket.getRecvMsg()[1]) {
            // this client : black chessman
        case 'B':
            ownColor = 0;
            oppositeColor = 1;
            rtn = client_socket.sendMsg("BB");
            printf("Send BB -> rtn: %d\n", rtn);
            if (rtn != 0) return;
            break;
        case 'W':
            ownColor = 1;
            oppositeColor = 0;
            rtn = client_socket.sendMsg("BW");
            printf("Send BW -> rtn: %d\n", rtn);
            if (rtn != 0) return ;
            break;
        default:
            printf("Authorized Failed!\n");
            break;
    }
}

void Reversi::oneRound()
{
    int STEP = 1;
    switch (ownColor) {
        case 0:
            while (STEP < 10000) {
                
				pair<int, int> chess = step();                        // take action, send message
                
                // lazi only excute after server's message confirm  in observe function
                generateOneStepMessage(chess.first, chess.second);
                
                
                if (observe() >= 1) break;     // receive RET Code
                
                if (observe() >= 1) break;    // see white move
                STEP++;
                // saveChessBoard();
            }
            printf("One Round End\n");
            break;
        case 1:
            while (STEP < 10000) {
                
                if (observe() >= 1) break;    // see black move
                
				pair<int, int> chess = step();                        // take action, send message
                // lazi only excute after server's message confirm  in observe function
                generateOneStepMessage(chess.first,chess.second);
                
                
                if (observe() >= 1) break;     // receive RET Code
                // saveChessBoard();
                STEP++;
            }
            printf("One Round End\n");
            break;
            
        default:
            break;
    }
}

void Reversi::roundOver(int round)
{
    printf("Round %d Over!\n", round);
    // reset initializer

    ownColor = oppositeColor = -1;
}

int Reversi::observe()
{
	int rtn = 0;
	int recvrtn = client_socket.recvMsg();
	if (recvrtn != 0) return 1;
	printf("receive msg %s\n", client_socket.getRecvMsg());
	switch (client_socket.getRecvMsg()[0]) {
	case 'R':
	{
		switch (client_socket.getRecvMsg()[1]) {
		case 'Y':   // valid step
			switch (client_socket.getRecvMsg()[2]) {
			case 'P':   // update chessboard
			{
				int desRow = (client_socket.getRecvMsg()[3] - '0') * 10 + client_socket.getRecvMsg()[4] - '0';
				int desCol = (client_socket.getRecvMsg()[5] - '0') * 10 + client_socket.getRecvMsg()[6] - '0';
				int color = (client_socket.getRecvMsg()[7] - '0');
				//你应该在这里处理desRow和desCol，推荐使用函数
				handleMessage(desRow, desCol, color);

				printf("a valid step of : (%d %d)\n", desRow, desCol);
				break;
			}
			case 'N':   // R0N: enemy wrong step
			{
				//
				printf("a true judgement of no step\n");
				break;
			}
			}

			break;
		case 'W':
			// invalid step
			switch (client_socket.getRecvMsg()[2]) {
			case 'P': {
				int desRow = (client_socket.getRecvMsg()[3] - '0') * 10 + client_socket.getRecvMsg()[4] - '0';
				int desCol = (client_socket.getRecvMsg()[5] - '0') * 10 + client_socket.getRecvMsg()[6] - '0';
				int color = (client_socket.getRecvMsg()[7] - '0');
				printf("Invalid step , server random a true step of : (%d %d)\n", desRow, desCol);
				//你应该在这里处理desRow和desCol，推荐使用函数
				handleMessage(desRow, desCol, color);
				break;
			}
			case 'N': {
				printf("a wrong judgement of no step\n");
				break;
			}
			default:
				break;
			}
			break;
		case '1':

			printf("Error -1: Msg format error!\n");
			rtn = -1;
			break;
		case '2':

			printf("Error -2: Corrdinate error!\n");
			rtn = -2;
			break;
		case '4':

			printf("Error -4: Invalid step!\n");
			rtn = -4;
			break;
		default:

			printf("Error -5: Other error!\n");
			rtn = -5;
			break;
		}
		break;
	}
	case 'E':
	{
		switch (client_socket.getRecvMsg()[1]) {
		case '0':
			// game over
			rtn = 2;
			break;
		case '1':
			// round over
			rtn = 1;
		default:
			break;
		}
		break;
	}
	default:
		break;
	}
	return rtn;
}

void Reversi::generateOneStepMessage(int row, int col)
{
	char msg[BUFSIZE];
	memset(msg, 0, sizeof(msg));

	//put row and col in the message
	msg[0] = 'S';
	msg[1] = 'P';
	msg[2] = '0' + row / 10;
	msg[3] = '0' + row % 10;
	msg[4] = '0' + col / 10;
	msg[5] = '0' + col % 10;
	msg[6] = '\0';

	//print
	printf("generate one step at possition (%2d,%2d) : %s\n", row, col, msg);


	client_socket.sendMsg(msg);
}

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
			else if (j < 0)
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

int  Board::get_point(int row, int col,int color)
{
	if (chess[row][col].type != -1)
		return -1;
	else
	{
		int total = 0;
		int total1 = 0;
		int total2 = 0;
		chess[row][col].type = 0;
		renew_ang(row, col);
		total1 += chess[row][col].val;
		for (int i = row - 4; i < row + 5; i++)
		{
			if (i < 0 || i>=19)
				continue;
			else
			{
				for (int j = col - 4; j < col + 5; j++)
				{
					if (j < 0 || j>=19)
						continue;
					else if (chess[i][j].type == -1) continue;
					else
					{
						int past = chess[i][j].val;
						renew_ang(i, j);
						int dif = chess[i][j].val - past;
						dif = dif < 0 ? -dif : dif;
						total1 += dif;
						chess[i][j].val = past;
						chess[row][col].type = -1;
						renew_ang(i, j);
						chess[row][col].type = 0;
					}
				}
			}
		}

		chess[row][col].type = 1;
		renew_ang(row, col);
		total2 += chess[row][col].val;
		for (int i = row - 4; i < row + 5; i++)
		{
			if (i < 0 || i>=19)
				continue;
			else
			{
				for (int j = col - 4; j < col + 5; j++)
				{
					if (j < 0 || j>=19)
						continue;
					else if (chess[i][j].type == -1) continue;
					else
					{
						int past = chess[i][j].val;
						renew_ang(i, j);
						int dif = chess[i][j].val - past;
						dif = dif < 0 ? -dif : dif;
						total2 += dif;
						chess[i][j].val = past;
						chess[row][col].type = -1;
						renew_ang(i, j);
						chess[row][col].type = 1;
					}
				}
			}
		}
		
		chess[row][col].type = -1;
		if (color == 0)
		{
				total = 3 * total1 + 2*total2;
		}
		else
		{
				total = 2*total1 + 3*total2;
		}
		//cout << total << endl;
		return total;
	}
}

void Board::handlemes(int row, int col, int color)
{
	chess[row][col].type = color;
	chess[row][col].row = row;
	chess[row][col].col = col;
	renew_ang(row, col);
	cout << row<<' '<<col<<' ' << chess[row][col].val <<' ' << chess[row][col].type << endl;
}



/*-------------------------last three function--------------------------------
* step : find a good position to lazi your chess.
* saveChessBoard : save the chess board now.
* handleMessage: handle the message from server.
*/



pair<int, int> Reversi::step()
{
	//TODO:Generate a valid step here
	int point[19][19];
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			point[i][j] = 0;
			point[i][j] = board.get_point(i, j,ownColor);
		}
	}
	//int r = rand() % 19;
	//int c = rand() % 19;
	int r = -1;
	int c = -1;
	if (findinlearn)
	{
		int chesslen = (chessnum - 1) * 2 + 3 + 4 + 5;
		int id = 0;
		string learnline;
		ifstream in("D:/Practice-of-Fundamental-Programming/Project3 gobang AI/clinet_win/learning.txt", ios::in);
		if (!in)
		{
			exit(-1);
		}
		for (int i = 0; i < chessnum; i++)
		{
			if (in.eof())
			{
				findinlearn = false;
				learnline = "";
				break;
			}
			getline(in, learnline);
		}
		if (findinlearn)
		{
			int x = 0;
			int t = 0;
			int max = 0;
			findinlearn = false;
			for (int j = 0;; j++)
			{
				if (j * (chesslen + 1) >= learnline.length())
				{
					break;
				}
				cout << flag << endl;
				if (flag == learnline.substr(j * (chesslen + 1) + 12, 2 * (chessnum - 1)))
				{
					findinlearn = true;
					x++;
					string learnscore = learnline.substr(j * (chesslen + 1) + 7, 5);
					int chessscore = 10000 * (learnscore[0] - '0') + 1000 * (learnscore[1] - '0') + 100 * (learnscore[2] - '0') + 10 * (learnscore[3] - '0') + learnscore[4] - '0';
					cout << chessscore << endl;
					if (chessscore>max )
					{
						max = chessscore;
						string ro = learnline.substr(j * (chesslen + 1) + 3, 2);
						string co = learnline.substr(j * (chesslen + 1) + 5, 2);
						t = x;
						r = stoi(ro);
						c = stoi(co);
					}
				}
			}
			cout << "max:" << max << endl;
			if (max < 49980) { findinlearn = false; cout << "not good in learning!" << endl; }
			char a[10] = { '\0' };
			sprintf_s(a, "%02d", t);
			flag += a;//找到后更新flag
			cout <<t<<"&" << a << endl;
			cout << "new:" << flag << endl;
			cout << "find in learning!" << endl;
		}
		in.close();
	}

	if(!findinlearn)
	{
		int r2 = 0;
		int c2 = 0;
		cout << "did not find in learning!" << endl;
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				cout << point[i][j] << ' ';
				if (point[i][j] > point[r2][c2]&&(i!=r||j!=c))
				{
					r2 = i;
					c2 = j;
				}
			}
			cout << endl;
		}
		
		r = r2;
		c = c2;
	}
	cout << "send: ";
	cout << r << ' ' << c << ' ' << board.chess[r][c].val << ' ' << board.chess[r][c].type << endl;
	return make_pair(r, c);

}



void Reversi::saveChessBoard()
{
	  
}

void Reversi::handleMessage(int row, int col, int color) {
	board.handlemes(row, col, color);
	cout << "receive" << endl;
	//board.board_display();
	string path = "D:/Practice-of-Fundamental-Programming/Project3 gobang AI/clinet_win/history/historygame";
	char a[10] = { '\0' };
	sprintf_s(a, "%d", historynum);
	path += a;
	path += ".txt";
	ofstream out(path, ios::app);
	if (!out)
	{
		exit(-1);
	}
	string onestep = "";
	char chessn[10] = { '\0' };
	sprintf_s(chessn, "%03d", chessnum);
	onestep += chessn;
	char chessr[10] = { '\0' };
	sprintf_s(chessr, "%02d", row);
	onestep += chessr;
	char chessc[10] = { '\0' };
	sprintf_s(chessc, "%02d", col);
	onestep += chessc;
	if (chessnum % 2 == 0)
		onestep += "1";
	else
		onestep += "0";
	out << endl << onestep;//步数，位置，颜色
	out.close();
	if (findinlearn&&color==oppositeColor)
	{
		int chesslen = (chessnum-1) * 2 + 3 + 4 + 5;
		int id = 0;
		string learnline;
		ifstream in("D:/Practice-of-Fundamental-Programming/Project3 gobang AI/clinet_win/learning.txt", ios::in);
		if (!in)
		{
			exit(-1);
		}
		for (int i = 0; i < chessnum; i++)
		{
			if (in.eof())
			{
				findinlearn = false;
				learnline = "";
				break;
			}
			getline(in, learnline);
		}
		if (findinlearn)
		{
			int x = 0;
			for (int j = 0;; j++)
			{
				if (j * (chesslen + 1) >= learnline.length())
				{
					findinlearn = false;
					break;
				}
				cout << chessnum<<" " << flag<<" " << onestep << endl;
				if (flag == learnline.substr(j * (chesslen + 1) + 12, 2 * (chessnum - 1)))
				{
					x++;
					if (learnline.substr(j * (chesslen + 1), 7) == onestep.substr(0, 7))
					{
						char y[5] = { '\0' };
						sprintf_s(y,"%02d", x);
						flag += y;//找到后更新flag
						break;
					}
				}

			}
		}
		in.close();
	}


	chessnum++;
}


void AI_study()
{

	string historypath = "D:/Practice-of-Fundamental-Programming/Project3 gobang AI/clinet_win/history/historygame";
	char a[10] = { '\0' };
	sprintf_s(a, "%d", historynum);
	historypath += a;
	historypath += ".txt";
	ifstream in(historypath, ios::in);
	if (!in)
	{
		exit(-1);
	}
	string line;
	int linenum = 0;
	while (!in.eof())
	{
		getline(in, line);
		linenum++;
	}
	in.close();
	//linenum--;
	cout << linenum << endl;
	if (linenum >= 350) return;
	ifstream inchess(historypath, ios::in);
	if (!inchess)
	{
		exit(-1);
	}

	ifstream fs("D:/Practice-of-Fundamental-Programming/Project3 gobang AI/clinet_win/learning.txt", ios::in);
	if (!fs)
	{
		exit(-1);
	}

	ofstream out("D:/Practice-of-Fundamental-Programming/Project3 gobang AI/clinet_win/learningtemp.txt", ios::out);
	if (!out)
	{
		exit(-1);
	}

	int* stepscore = new int[linenum];
	double k = (1 + linenum / 2) * linenum / 2;//y=x拟合
	k = 4000 / k;
	for (int i = 0; i < linenum; i++)
	{
		stepscore[i] = (int)(((i + 1) / 2 + 1) * k);
		if ((i + 1) % 2 != linenum % 2)
			stepscore[i] = -stepscore[i];
		cout << stepscore[i] << ' ';
	}
	cout << endl;
	string chessline;
	string learnline;
	string flag = "";

	for (int i = 0; i < linenum; i++)
	{
		string newlearnline = "";
		//string step[100];
		//001 0909 0
		//002 0505 1
		getline(inchess, chessline);
		//int num;
		//int row, col;
		//int color;
		string s1, s2, s3, s4;
		string s23 = "";
		s1 = chessline.substr(0, 3);//num
		s2 = chessline.substr(3, 2);//row
		s3 = chessline.substr(5, 2);//col
		s4 = chessline.substr(7, 1);//color
		s23 += s2;
		s23 += s3;
		cout << s1 << ' ' << s2 << ' ' << s3 << ' ' << s4 << endl;


		//0010909(point)[]
		//0020505(point)[01]//(i)(row,col)(point)[2*(i-1)]//3+4+5+2*i-2=2*i+9
		if (!fs.eof())
		{
			int id = 0;
			getline(fs, learnline);
			int chesslen = i * 2 + 3 + 4 + 5;
			string flagcheck = "";

			for (int j = 0;; j++)
			{
				cout << "pastline:" << learnline << endl;
				if (j * (chesslen + 1) >= learnline.length())
				{
					id++;
					newlearnline += learnline;
					newlearnline += s1;
					newlearnline += s2;
					newlearnline += s3;
					int score = 50000 + stepscore[i];
					if (score < 0) score = 0;
					char a[10] = { '\0' };
					sprintf_s(a, "%05d", score);
					newlearnline += a;
					newlearnline += flag;
					newlearnline += " ";
					char b[5] = { '\0' };
					sprintf_s(b, "%02d", id);
					flag += b;
					out << newlearnline << endl;
					cout << newlearnline << endl;
					break;
				}
				flagcheck = learnline.substr(j * (chesslen + 1) + 12, 2 * i);
				if (flag == flagcheck)
				{
					id++;
					if (learnline.substr(j * (chesslen + 1) + 3, 4) == s23)
					{
						string oldscore = learnline.substr(j * (chesslen + 1) + 7, 5);
						int newscore = stoi(oldscore) + stepscore[i];
						char a[10] = { '\0' };
						sprintf_s(a, "%05d", newscore);
						newlearnline += learnline.substr(0, j * (chesslen + 1) + 7);
						newlearnline += a;
						newlearnline += learnline.substr(j * (chesslen + 1) + 12, learnline.length() - j * (chesslen + 1) + 12);
						out << newlearnline << endl;
						cout << newlearnline << endl;
						char b[5] = { '\0' };
						sprintf_s(b, "%02d", id);
						flag += b;
						break;
					}
				}
			}


		}
		else
		{
			newlearnline += s1;
			newlearnline += s2;
			newlearnline += s3;
			int score = 50000 + stepscore[i];
			if (score < 0) score = 0;
			char a[10] = { '\0' };
			sprintf_s(a, "%05d", score);
			newlearnline += a;
			newlearnline += flag;
			newlearnline += " ";
			flag += "01";//更新标志
			out << newlearnline << endl;
			cout << newlearnline << endl;
		}



	}
	while (!fs.eof())
	{
		getline(fs, learnline);
		out << learnline << endl;
	}


	fs.close();
	inchess.close();
	out.close();

	ofstream out_file("D:/Practice-of-Fundamental-Programming/Project3 gobang AI/clinet_win/learning.txt", ios::out);
	if (!out_file)
	{
		exit(-1);
	}

	ifstream in_file("D:/Practice-of-Fundamental-Programming/Project3 gobang AI/clinet_win/learningtemp.txt", ios::in);
	if (!in_file)
	{
		exit(-1);
	}
	string oneline;
	while (!in_file.eof())
	{
		getline(in_file, oneline);
		out_file << oneline << endl;

	}
	in_file.close();
	out_file.close();

}
