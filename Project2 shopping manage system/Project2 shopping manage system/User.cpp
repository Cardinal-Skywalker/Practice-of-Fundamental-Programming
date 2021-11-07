#include"User.h"
#include<iostream>
#include<Windows.h>
#include<fstream>
#include"Avalon.h"
#include"welcome.h"
using namespace std;

void User::visit_Avalon()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD word = FOREGROUND_RED;
	WORD word2 = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	Avalon gate;
	system("cls");
	welcome_info();
	user_func_chooce();
	cout << "输入操作：" << endl;
	string choose;
	cin >> choose;
	while (choose != "1")
	{
		system("cls");
		welcome_info();
		if (choose == "2")
		{
			system("cls");
			welcome_info();
			gate.user_display(idnum);
		
		}
		else if (choose == "3")
		{
			system("cls");
			welcome_info();
			gate.user_display(idnum);
			gate.user_query(idnum);
		}
		else if (choose == "4")
		{
			system("cls");
			welcome_info();
			gate.user_display(idnum);
			gate.user_add(idnum);
		}
		else if (choose == "5")
		{
			system("cls");
			welcome_info();
			gate.user_delete(idnum);
		}
		else if (choose == "6")
		{
			system("cls");
			welcome_info();
			gate.user_cart_display(idnum);
		}
		else if (choose == "7")
		{
			system("cls");
			welcome_info();
		gate.user_order(idnum);
		}
		else if (choose == "8")
		{
			system("cls");
			welcome_info();
			gate.user_history_display(idnum);
		}
		else if (choose == "9")
		{
			system("cls");
			welcome_info();
			gate.user_order_display(idnum);
		}
		else
		{
			SetConsoleTextAttribute(handle, word);
			cout << "invalid choose!" << endl;
			SetConsoleTextAttribute(handle, word2);
		}
		user_func_chooce();
		cout << "输入操作：" << endl;
		cin >> choose;
	}
}

void User::create_user_file(int x, string name, string pass)
{
	ofstream out_file(".\\用户\\用户.txt", ios::app);
	if (!out_file) exit(-1);
	out_file <<endl<< name << ' ' << pass;
	out_file.close();
}

void User::create_user_cart_file(int x)
{
	string path = ".\\用户\\user";
	char a[10] = { '\0' };
	sprintf_s(a, "%d", x);
	path += a;
	path += ".txt";
	ofstream out_file(path, ios::out);
	if (!out_file) exit(-1);
	out_file << "ID	名称	品牌	价格	数量"<<endl;
	out_file.close();
}

void  User::create_user_history_file(int x)
{
	string path = ".\\用户\\history_user";
	char a[10] = { '\0' };
	sprintf_s(a, "%d", x);
	path += a;
	path += ".txt";
	ofstream out_file(path, ios::out);
	if (!out_file) exit(-1);
	out_file << "ID	名称	品牌	价格	数量	操作";
	out_file.close();
}

void  User::create_user_order_file(int x)
{
	string path = ".\\用户\\order_user";
	char a[10] = { '\0' };
	sprintf_s(a, "%d", x);
	path += a;
	path += ".txt";
	ofstream out_file(path, ios::out);
	if (!out_file) exit(-1);
	out_file << "地址"<<' ';
	out_file.close();
}