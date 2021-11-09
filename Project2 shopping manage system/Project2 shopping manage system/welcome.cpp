#include<iostream>
#include<fstream>
#include<windows.h>
using namespace std;

void welcome_info()
{
	ifstream in_file(".\\�̵�\\welcome.txt", ios::in);
	char log[500] = { 0 };
	if (in_file.is_open())
	{
		while (!in_file.eof()) {
			in_file.getline(log, 500);
			cout << log << endl;
		}
	}
	else
	{
		cerr << "file open error!" << endl;
		exit(-1);
	}
	in_file.close();
	cout << "==================================================================================================================" << endl;
}

void successful_info()
{
	ifstream in_file(".\\�̵�\\successful.txt", ios::in);
	char log[500] = { 0 };
	if (in_file.is_open())
	{
		while (!in_file.eof()) {
			in_file.getline(log, 500);
			cout << log << endl;
		}
	}
	else
	{
		cerr << "file open error!" << endl;
		exit(-1);
	}
	in_file.close();
}


void linkstart_info()
{
	ifstream in_file(".\\�̵�\\linkstart.txt", ios::in);
	char log[500] = { 0 };
	if (in_file.is_open())
	{
		while (!in_file.eof()) {
			in_file.getline(log, 500);
			cout << log << endl;
		}
	}
	else
	{
		cerr << "file open error!" << endl;
		exit(-1);
	}
	in_file.close();
	cout << "==================================================================================================================" << endl;
}

void boot_interface()
{
	cout << "====================================================================" << endl;
	cout << "1.�û���¼   2.�û�ע��   3.����Ա��¼   4.����Աע��   5.�˳�" << endl;
	cout << "====================================================================" << endl;
}

void user_func_chooce()
{
	cout << "==================================================================================================================" << endl;
	cout << "1.ע����¼   2.�鿴��Ʒ   3.��Ʒ����   4.�����Ʒ�����ﳵ   5.ɾ�����ﳵ��Ʒ   6.�鿴���ﳵ  " << endl;
	cout << "==================================================================================================================" << endl;
	cout << "7.����   8.�����¼   9.�鿴����   10.���Է���   11.�鿴��Ϣ" << endl;
	cout << "==================================================================================================================" << endl;
}

void admin_func_chooce()
{
	cout << "==================================================================================================================" << endl;
	cout << "0.ע����¼   1.��ѯ��Ʒ   2.������Ʒ   3.ɾ����Ʒ   4.�޸���Ʒ�����ͼ۸�   5.�ۻ��嵥   6.�����嵥   7.�鿴����" << endl;
	cout << "==================================================================================================================" << endl;
}

void goodbye_info()
{
	ifstream in_file(".\\�̵�\\goodbye.txt", ios::in);
	char log[500] = { 0 };
	if (in_file.is_open())
	{
		while (!in_file.eof())
		{
			in_file.getline(log, 500);
			cout << log << endl;
		}
	}
	else {
		cerr << "file open error!" << endl;
		exit(-1);
	}
	in_file.close();
}