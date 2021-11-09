#include<iostream>
#include<fstream>
#include<windows.h>
using namespace std;

void welcome_info()
{
	ifstream in_file(".\\商店\\welcome.txt", ios::in);
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
	cout << "==================================================================================================================" << endl;
}

void successful_info()
{
	ifstream in_file(".\\商店\\successful.txt", ios::in);
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
}


void linkstart_info()
{
	ifstream in_file(".\\商店\\linkstart.txt", ios::in);
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
	cout << "==================================================================================================================" << endl;
}

void boot_interface()
{
	cout << "====================================================================" << endl;
	cout << "1.用户登录   2.用户注册   3.管理员登录   4.管理员注册   5.退出" << endl;
	cout << "====================================================================" << endl;
}

void user_func_chooce()
{
	cout << "==================================================================================================================" << endl;
	cout << "1.注销登录   2.查看商品   3.商品搜索   4.添加商品至购物车   5.删除购物车商品   6.查看购物车  " << endl;
	cout << "==================================================================================================================" << endl;
	cout << "7.结账   8.浏览记录   9.查看订单   10.留言反馈   11.查看消息" << endl;
	cout << "==================================================================================================================" << endl;
}

void admin_func_chooce()
{
	cout << "==================================================================================================================" << endl;
	cout << "0.注销登录   1.查询商品   2.增加商品   3.删除商品   4.修改商品数量和价格   5.售货清单   6.已售清单   7.查看留言" << endl;
	cout << "==================================================================================================================" << endl;
}

void goodbye_info()
{
	ifstream in_file(".\\商店\\goodbye.txt", ios::in);
	char log[500] = { 0 };
	if (in_file.is_open())
	{
		while (!in_file.eof())
		{
			in_file.getline(log, 500);
			cout << log << endl;
		}
	}
	else {
		cerr << "file open error!" << endl;
		exit(-1);
	}
	in_file.close();
}