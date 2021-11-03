#include<iostream>
#include<fstream>
#include<cassert>
#include<string>
#include"complex.h"
#include"read.h"
using namespace std;

void welcome_info()
{
	ifstream in_file(".\\welcome.txt", ios::in);
	char log[500] = { 0 };
	if (in_file.is_open())
	{
		while (!in_file.eof()) {
			in_file.getline(log, 500);
			cout << log << endl;
		}
	}
	else
	{
		cerr << "file open error!" << endl;
		exit(-1);
	}
	in_file.close();
	cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|***************************************************************|" << "Here is something you have to know before using:                                          |" << endl;
	cout << "|********************Tree Diagram Calculator********************|" << "1.The operations you can use are:'+','-','*','/','^','cjg','arg','|...|''(',')'.          |" << endl;
	cout << "|***************************************************************|" <<"2.Please input the Comlex numbers that is congenial with reason and common sense.         |" << endl;
	cout << "|Welcome to use this complex number calculator by Cardinal.     |" <<"3.you can type 'quit' if you have finished your calculation and want to exit the program. |"<< endl;
	cout << "|We are trying to help you calculate Infinite Possibilities.    |" << "4.If you have other problems or constructive suggestions, please contact Mr. Skywalker    |"<< endl;
	cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << endl;
	
}

void choose_info()
{
	cout << "---------------------------------------" << endl;
	cout << "| 1.Expression Evaluator              |" << endl;
	cout << "| 2.Distance Generate                 |" << endl;
	cout << "| 3.Solve Equations                   |" << endl;
	cout << "| 4.View History                      |" << endl;
	cout << "| 5.Quit                              |" << endl;
	cout << "---------------------------------------" << endl;
	cout << "Please choose the function you like:";
}

void welcome_input(int x)
{
	if(x==1)
	cout << "Please input your expression here: " << endl;
	else if (x == 2)
	{
		cout << "Please input two complex numbers here: " << endl;
	}
	if (x == 3)
	{
		cout << "Please input your equations here: " << endl;
	}
	if (x == 4)
	{
		cout << "You can check your history here with up and down." << endl;
	}
}

void legal_output(string str)
{
	complex res;
	res = str_transfer(str);
	cout << "The result is : " ;
	cout.precision(6);
	if (res.real != 0)
		cout << fixed << res.real;
	if (res.img > 0 && res.real != 0)
		cout << "+" << res.img << "i" << endl;
	else if (res.img > 0 && res.real == 0)
		cout << res.img << "i" << endl;
	else if (res.img < 0)
		cout << res.img << "i" << endl;
	else
		cout << endl;
}

void goodbye_info()
{
	ifstream in_file(".\\goodbye.txt", ios::in);
	char log[500] = { 0 };
	if (in_file.is_open())
	{
		while (!in_file.eof())
		{
			in_file.getline(log, 500);
			cout << log << endl;
		}
	}
	else{
		cerr << "file open error!" << endl;
		exit(-1);
	}
	in_file.close();
}

int CountLines(char* filename)
{
	ifstream ReadFile;
	int n = 0;
	string tmp;
	ReadFile.open(filename, ios::in);
	if (ReadFile.fail())
	{
		return 0;
	}
	else//ÎÄ¼þ´æÔÚ
	{
		while (getline(ReadFile, tmp, '\n'))
		{
			n++;
		}
		ReadFile.close();
		return n;
	}
}