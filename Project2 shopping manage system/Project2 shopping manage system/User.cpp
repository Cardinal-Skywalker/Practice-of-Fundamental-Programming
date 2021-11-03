#include"User.h"
#include<iostream>
#include<fstream>
#include"Avalon.h"
#include"welcome.h"
using namespace std;

void User::visit_Avalon()
{
	Avalon gate;
	user_func_chooce();
	cout << "输入操作：" << endl;
	int choose;
	cin >> choose;
	while (choose != 1)
	{

		if (choose == 2)
		{
			gate.user_query(idnum);
		}
		if (choose == 3)
		{
			gate.user_display(idnum);
		}
		if (choose == 4)
		{
			gate.user_add(idnum);
		}
		if (choose == 5)
		{
			gate.user_delete(idnum);
		}
		if (choose == 6)
		{
			gate.user_cart_display(idnum);
		}
		if (choose == 7)
		{
			gate.user_order(idnum);
		}
		else
		{
			cout << "invalid choose!" << endl;
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
	out_file << name << ' ' << pass << endl;
	out_file.close();
}

void User::create_user_cart_file(int x)
{
	string path = ".\\用户\\uer";
	char i[3];
	_itoa_s(x, i, 10);
	path += i;
	path += ".txt";
	ofstream out_file(path, ios::out);
	if (!out_file) exit(-1);
	out_file << "ID	名称	品牌	价格	数量" << endl;
	out_file.close();
}

void  User::create_user_history_file(int x)
{
	string path = ".\\用户\\history_user";
	char i[3];
	_itoa_s(x, i, 10);
	path += i;
	path += ".txt";
	ofstream out_file(path, ios::out);
	if (!out_file) exit(-1);
	out_file << "ID	名称	品牌	价格	数量" << endl;
	out_file.close();
}