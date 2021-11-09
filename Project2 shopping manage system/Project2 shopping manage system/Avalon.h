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
	void renew_usercart(int user_idnum);
	Avalon()
	{
		init_Avalon();
		for(int i = 1;i<= user_num;i++)
			renew_usercart(i);
	}
	void renew_Avalon();
	void user_history_display(int user_idnum);
	void user_order_display(int user_idnum);
	void admin_to_user_display(int user_idnum);
	void user_to_admin(int user_idnum);
	void clear_userboard(int user_idnum);
private:
	void init_Avalon();
	void treasure_add();
	void admin_display();
	void treasure_delete();
	void change_treasure_numorprice();
	void sold_display();
	void note_display(int x);
	void note_handle();
	bool check_cart_and_id(int user_idnum,string fixid);
};
