#include<iostream>
#include<fstream>
#include<Windows.h>
#include<conio.h>
#include"Avalon.h"
#include"User.h"
#include"welcome.h"
using namespace std;

void user_sign_up()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD word = FOREGROUND_RED;
	WORD word2 = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	bool iffail = true;
	string name, pass1, pass2;
	int i = 0;
	while (iffail)
	{
		iffail = false;
		cout << "�����û�����";
		cin >> name;
		cout << endl;
		cout << "�������룺";
		cin >> pass1;
		cout << endl;
		cout << "�ٴ��������룺";
		cin >> pass2;
		cout << endl;
		ifstream in_file(".\\�û�\\�û�.txt", ios::in);
		if (!in_file) exit(-1);
		string prename, prepass;
		i = 0;
		while (!in_file.eof())
		{
			i++;
			in_file >> prename >> prepass;
			if (prename == name)
			{
				SetConsoleTextAttribute(handle, word);
				cout << "ERROR: " << name << " �ѱ�ʹ��" << endl;
				SetConsoleTextAttribute(handle, word2);
				iffail = true;
				break;
			}
		}
		if (pass1 != pass2)
		{
			iffail = true;
			SetConsoleTextAttribute(handle, word);
			cout << "ERROR,password is illegal!" << endl;
			SetConsoleTextAttribute(handle, word2);
		}
		in_file.close();
	}
	cout << "ע��ɹ���" << endl;
	User newuser;
	newuser.create_user_file(i, name, pass1);
	newuser.create_user_cart_file(i);
	newuser.create_user_history_file(i);
	newuser.create_user_order_file(i);
	Avalon gate;
	gate.user_num++;
	gate.renew_Avalon();
}

void user_sign_in()
{
	bool iffail = true;
	string name, pass1;
	while (iffail)
	{
		int size = 20;
		char c;
		int count = 0;
		char* password = new char[size]; // ��̬����ռ�

		system("cls");
		welcome_info();
		cout << "=========================================================================================" << endl;
		iffail = true;
		cout << "�����û�����";
		cin >> name;
		cout << endl;
		cout << "�������룺";
		while ((c = _getch()) != '\r')
		{
			if (c == 8)
			{ // �˸�
				if (count == 0)
				{
					continue;
				}
				putchar('\b'); // ����һ��
				putchar(' '); // ���һ���ո�ԭ����*����
				putchar('\b'); // �ٻ���һ��ȴ�����
				count--;
			}
			if (count == size - 1) { // ��󳤶�Ϊsize-1
				continue;
			}
			if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {  // ����ֻ�ɰ������ֺ���ĸ
				putchar('*');  // ���յ�һ���ַ���, ��ӡһ��*
				password[count] = c;
				count++;
			}
		}
		password[count] = '\0';
		pass1 = password;
		delete[] password; // �ͷſռ�
		cout << endl;

		//cin >> pass1;
		cout << endl;
		ifstream in_file(".\\�û�\\�û�.txt", ios::in);
		if (!in_file) exit(-1);
		string prename, prepass;
		int x = 0;
		while (!in_file.eof())
		{
			x++;
			in_file >> prename >> prepass;
			if (prename == name)
			{
				if (pass1 != prepass)
				{
					iffail = true;
				}
				else
				{
					x--;
					cout << x;
					iffail = false;
					User user(x, name, pass1);
					cout << "Conecting......" << endl;
					user.visit_Avalon();
				}
				break;
			}
		}
		if (iffail)
		{
			cout << "�˺Ż��������" << endl;
			Sleep(4 * 1000);
		}
	}
}