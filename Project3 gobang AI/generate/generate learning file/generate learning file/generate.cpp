#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;



int main()
{
	ifstream in("D:/Practice-of-Fundamental-Programming/Project3 gobang AI/clinet_win/history/historygame9.txt", ios::in);
	if (!in)
	{
		exit(-1);
	}
	string line;
	int linenum=0;
	while (!in.eof())
	{
		getline(in, line);
		linenum++;
	}
	in.close();
	//linenum--;
	cout << linenum<<endl;
	ifstream inchess("D:/Practice-of-Fundamental-Programming/Project3 gobang AI/clinet_win/history/historygame9.txt", ios::in);
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
		stepscore[i]= (int)(((i + 1) / 2 + 1) * k);
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
		s1 = chessline.substr(0,3);//num
		s2 = chessline.substr(3,2);//row
		s3 = chessline.substr(5,2);//col
		s4 = chessline.substr(7,1);//color
		s23 += s2;
		s23 += s3;
		cout << s1 << ' ' << s2<<' ' << s3<<' ' << s4 << endl;


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
					cout<<newlearnline<<endl;
					break;
				}
				flagcheck = learnline.substr(j * (chesslen + 1) + 12,2*i);
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
						newlearnline += learnline.substr(j * (chesslen + 1) + 12, learnline.length()- j * (chesslen + 1) + 12);
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
		getline(in_file,oneline);
		out_file << oneline << endl;

	}
	in_file.close();
	out_file.close();

	return 0;

}