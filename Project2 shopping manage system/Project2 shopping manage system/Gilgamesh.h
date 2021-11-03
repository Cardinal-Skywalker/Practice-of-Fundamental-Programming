#pragma once
#include<iostream>
#include<string>
#include"Avalon.h"
using namespace std;
class Gilgamesh
{
public:
	int idnum;
	string id;
	string password;
	Gilgamesh()
	{
		idnum = 0;
		//id = " ";
		//password = " ";
	}
	Gilgamesh(int x)
	{
		idnum = x;
		cin >> id >> password;
		create_admin_file(x,id,password);
	}
	Gilgamesh(int x, string name, string pass)
	{
		idnum = x;
		id = name;
		password = pass;
	}
	void create_admin_file(int x,string name,string pass);
	void enter_Avalon();   
};