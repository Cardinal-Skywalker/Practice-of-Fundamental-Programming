#include<iostream>
#include<fstream>
#include"Avalon.h"
#include"User.h"
using namespace std;

void user_sign_up()
{
	bool iffail = true;
	string name, pass1, pass2;
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
		ifstream in_file(".\\用户\\用户.txt", ios::in);
		if (!in_file) exit(-1);
		string prename, prepass;
		i = 1;
		while (!in_file.eof())
		{
			i++;
			in_file >> prename >> prename;
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
	User newuser;
	newuser.create_user_file(i, name, pass1);
	newuser.create_user_cart_file(i);
	newuser.create_user_history_file(i);
}

void user_sign_in()
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
		ifstream in_file(".\\用户\\用户.txt", ios::in);
		if (!in_file) exit(-1);
		string prename, prepass;
		int x = 0;
		while (!in_file.eof())
		{
			x++;
			in_file >> prename >> prename;
			if (prename == name)
			{
				if (pass1 != prepass)
				{
					cout << "username or password wrong!" << endl;
				}
				else
				{
					iffail = false;
					User user(x, name, pass1);
					cout << "Conecting......" << endl;
					user.visit_Avalon();
				}
				break;
			}
		}
		if (iffail)
			cout << "username or password wrong" << endl;
	}
}