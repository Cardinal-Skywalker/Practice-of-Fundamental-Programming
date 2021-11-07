#include"Gilgamesh.h"
#include<iostream>
#include<fstream>
#include"Avalon.h"
#include"welcome.h"
using namespace std;

void Gilgamesh:: create_admin_file(int x,string name,string pass)
{
	ofstream out_file(".\\管理员\\管理员.txt", ios::app);
	if (!out_file) exit(-1);
	out_file<< endl << x <<' ' << name << ' ' << pass;
	out_file.close();
}

void  Gilgamesh::enter_Avalon()
{
	Avalon gate;
	system("cls");
	welcome_info();
	admin_func_chooce();
	cout << "输入操作：" << endl;
	string choose;
	cin >> choose;
	while (choose != "0")
	{

		system("cls");
		welcome_info();
		if (choose == "1")
		{
			system("cls");
			welcome_info();
			gate.admin_display();
			gate.user_query(0);
		}
		else if (choose == "2")
		{
			system("cls");
			welcome_info();
			gate.admin_display();
			gate.treasure_add();
		}
		else if (choose == "3")
		{
			system("cls");
			welcome_info();
			gate.admin_display();
			gate.treasure_delete();
		}
		else if (choose == "4")
		{
			system("cls");
			welcome_info();
			gate.admin_display();
			gate.change_treasure_numorprice();
		}
		else if (choose == "5")
		{
			system("cls");
			welcome_info();
			gate.admin_display();
		}
		else if (choose == "6")
		{
			system("cls");
			welcome_info();
			gate.sold_display();
		}
		else
		{
			cout << "invalid choose!" << endl;
		}

		admin_func_chooce();
		cout << "输入操作：" << endl;
		cin >> choose;
	}
}
