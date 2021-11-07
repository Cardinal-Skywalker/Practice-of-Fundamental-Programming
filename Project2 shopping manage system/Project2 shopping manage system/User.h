#pragma once
#include<iostream>
#include<string>
#include"Avalon.h"
class User
{
public:
	int idnum;
	string id;
	string password;
	User()
	{
		idnum = 0;
		//id = " ";
		//password = " ";
	}
	User(int x, string name, string pass)
	{
		idnum = x;
		id = name;
		password = pass;
	}
	void visit_Avalon();
	void create_user_file(int x, string name, string pass);
	void create_user_cart_file(int x);
	void create_user_history_file(int x);
	void create_user_order_file(int x);
};

