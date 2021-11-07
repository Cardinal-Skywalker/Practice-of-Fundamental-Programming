#include<iostream>
#include<fstream>
#include<Windows.h>
#include<conio.h>
#include"Avalon.h"
#include"welcome.h"
#include"Gilgamesh.h"
using namespace std;

void admin_sign_up()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD word = FOREGROUND_RED;
	WORD word2 = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	Avalon gate;
	bool iffail = true;
	string name, pass1,pass2;
	int i = 1;
	while (iffail)
	{
		iffail = false;
		cout << "输入管理员ID：";
		cin >> name;
		cout << endl;
		cout << "输入管理员密码：";
		cin >> pass1;
		cout << endl;
		cout << "请再次输入密码：";
		cin >> pass2;
		cout << endl;
		ifstream in_file(".\\管理员\\管理员.txt", ios::in);
		if (!in_file) exit(-1);
		string prename, prepass;
		int x;
		i = 1;
		while (!in_file.eof())
		{
			i++;
			in_file >> x >>prename >> prepass;
			if (prename == name)
			{
				SetConsoleTextAttribute(handle, word);
				cout << "ERROR: " << name << " 已被使用" << endl;
				SetConsoleTextAttribute(handle, word2);
				iffail = true;
				break;
			}
		}
		if (pass1 != pass2)
		{
			iffail = true;
			SetConsoleTextAttribute(handle, word);
			cout << "ERROR,password is illegal!" << endl;
			SetConsoleTextAttribute(handle, word2);
		}
	}
	cout << "注册成功！" << endl;
	gate.admin_num++;
	gate.renew_Avalon();
	Gilgamesh newadmin;
	newadmin.create_admin_file(i,name, pass1);
}

void admin_sign_in()
{
	bool iffail = true;
	string name, pass1;
	while (iffail)
	{
		int size = 20;
		char c;
		int count = 0;
		char* password = new char[size]; // 动态申请空间
		system("cls");
		welcome_info();
		iffail = true;
		cout << "输入管理员ID: ";
		cin >> name;
		cout << endl;
		cout << "输入管理员密码：";
		while ((c = _getch()) != '\r')
		{
			if (c == 8)
			{ // 退格
				if (count == 0)
				{
					continue;
				}
				putchar('\b'); // 回退一格
				putchar(' '); // 输出一个空格将原来的*隐藏
				putchar('\b'); // 再回退一格等待输入
				count--;
			}
			if (count == size - 1) { // 最大长度为size-1
				continue;
			}
			if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {  // 密码只可包含数字和字母
				putchar('*');  // 接收到一个字符后, 打印一个*
				password[count] = c;
				count++;
			}
		}
		password[count] = '\0';
		pass1 = password;
		delete[] password; // 释放空间
		cout << endl;

		//cin >> pass1;
		cout << endl;
		ifstream in_file(".\\管理员\\管理员.txt", ios::in);
		if (!in_file) exit(-1);
		string prename, prepass;
		int x;
		while (!in_file.eof())
		{
			in_file >> x >> prename >> prepass;
			if (prename == name)
			{
				if (pass1 != prepass)
				{
					iffail = true;
				}
				else
				{
					iffail = false;
					Gilgamesh admin(x, name, pass1);
					cout << "Conecting......" << endl;
					admin.enter_Avalon();
				}
				break;
			}
		}
		in_file.close();
		if (iffail)
		{
			cout << "账号或密码错误!" << endl;
			Sleep(4 * 1000);
		}
	}
}