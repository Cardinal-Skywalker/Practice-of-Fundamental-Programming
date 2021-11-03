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
	out_file << x <<' ' << name << ' ' << pass << endl;
	out_file.close();
}

void  Gilgamesh::enter_Avalon()
{
	Avalon gate;
	admin_func_chooce();
	cout << "输入操作：" << endl;
	int choose;
	cin >> choose;
	while (choose != 0)
	{

		if (choose == 1)
		{
			gate.user_query(idnum);
		}
		if (choose == 2)
		{
			gate.treasure_add();
		}
		if (choose == 3)
		{
			gate.treasure_delete();
		}
		if (choose == 4)
		{
			gate.change_treasure_num();
		}
		if (choose == 5)
		{
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

