#pragma once
#include<iostream>
#include<string>
#include"Gilgamesh.h"
using namespace std;
class Treasure
{
public:
	string id;
	string name;
	string brand;
	double price;
	int num;
};

class Avalon
{
friend class Gilgamesh;
public:
	Treasure treasure[100];
	int user_num;
	int admin_num;
	int treasure_num;
	void user_query(int user_idnum);
	void user_order(int user_idnum);
	void user_add(int user_idnum);
	void user_delete(int user_idnum);
	void user_display(int user_idnum);
	void user_cart_display(int user_idnum);
	//void treasure_sort();
	Avalon()
	{
		init_Avalon();
	}
	void renew_Avalon();
private:
	
	void init_Avalon();

	void treasure_add();
	void treasure_delete();
	void change_treasure_num();
	void sold_display();
};

/*class warpper {
public:
	static Avalon gate;
};*/