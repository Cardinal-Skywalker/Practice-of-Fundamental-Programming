#include"Gilgamesh.h"
#include<iostream>
#include<fstream>
#include"Avalon.h"
#include"welcome.h"
using namespace std;

void Gilgamesh:: create_admin_file(int x,string name,string pass)
{
	ofstream out_file(".\\����Ա\\����Ա.txt", ios::app);
	if (!out_file) exit(-1);
	out_file<< endl << x <<' ' << name << ' ' << pass;
	out_file.close();
}

void  Gilgamesh::enter_Avalon()
{
	Avalon gate;
	system("cls");
	welcome_info();
	gate.note_display(0);
	admin_func_chooce();
	cout << "���������" << endl;
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
		else if (choose == "7")
		{
			system("cls");
			welcome_info();
			gate.note_display(1);
			cout << "1.�ظ�����   2.�뿪" << endl;
			string cho;
			cin >> cho;
			if (cho == "1")
				gate.note_handle();
		}
		else
		{
			cout << "invalid choose!" << endl;
		}
		admin_func_chooce();
		cout << "���������" << endl;
		cin >> choose;
	}
}
