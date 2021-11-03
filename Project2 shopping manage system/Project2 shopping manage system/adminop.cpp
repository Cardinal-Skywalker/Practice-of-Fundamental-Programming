#include<iostream>
#include<fstream>
#include"Avalon.h"
#include"Gilgamesh.h"
using namespace std;

void admin_sign_up()
{
	Avalon gate;
	bool iffail = true;
	string name, pass1,pass2;
	int i = 1;
	while (iffail)
	{
		iffail = false;
		cout << "Please input your name: ";
		cin >> name;
		cout << endl;
		cout << "Please set your password:";
		cin >> pass1;
		cout << endl;
		cout << "Please input your password again:";
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
			in_file >> x >>prename >> prename;
			if (prename == name)
			{
				cout << "ERROR: " << name << " has been used" << endl;
				iffail = true;
				break;
			}
		}
		if (pass1 == pass2)
		{
			iffail = true;
			cout << "ERROR,password is illegal!" << endl;
		}
	}
	cout << "Registration Successful" << endl;
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
		iffail = false;
		cout << "Please input your name: ";
		cin >> name;
		cout << endl;
		cout << "Please set your password:";
		cin >> pass1;
		cout << endl;
		ifstream in_file(".\\管理员\\管理员.txt", ios::in);
		if (!in_file) exit(-1);
		string prename, prepass;
		int x;
		while (!in_file.eof())
		{
			in_file >> x >> prename >> prename;
			if (prename == name)
			{
				if (pass1 != prepass)
				{
					cout << "username or password wrong!" << endl;
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
		if (iffail)
			cout << "username or password wrong" << endl;
	}
}