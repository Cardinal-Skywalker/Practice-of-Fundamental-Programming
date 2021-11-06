#include<iostream>
#include<fstream>
#include<Windows.h>
#include<iomanip>
#include"Avalon.h"
using namespace std;

void Avalon::init_Avalon()
{
	ifstream in_file(".\\�̵�\\������Ϣ.txt", ios::in);
	if (!in_file)
		exit(-1);
	in_file >> user_num >> admin_num>> treasure_num;
	in_file.close();
	ifstream in(".\\�̵�\\���.txt", ios::in);
	string head;
	getline(in, head);
	int i = 0;
	while (!in.eof())
	{
		in >> treasure[i].id >> treasure[i].name >>treasure[i].brand>> treasure[i].price >> treasure[i].num;
		i++;
	}
	in.close();
	if (treasure_num != i-1)
		cerr << "something wrong!" << endl;
}

void Avalon::renew_Avalon()
{
	ofstream out_file(".\\�̵�\\������Ϣ.txt", ios::out);
	if (!out_file)
		exit(-1);
	out_file <<user_num << ' ' << admin_num<<' '<<treasure_num;
	out_file.close();
	ofstream out(".\\�̵�\\���.txt", ios::out);
	string head = "ID	����	Ʒ��	�۸�	����";
	out << head << endl;
	int i = 0;
	for(int i = 0;i<treasure_num;i++)
	{
		out << treasure[i].id << " " << treasure[i].name << " " << treasure[i].brand << " " << treasure[i].price << " " << treasure[i].num << endl;;
	}
	out.close();
}

void Avalon::user_add(int user_idnum)
{
	cout << "������ƷID��������";
	string goods_id;
	int num;
	cin >> goods_id >> num;
	cout << "*******************" << endl;
	int i;
	int k = 0;
	Treasure  treasure_in_cart[100];
	string path = ".\\�û�\\user";
	char a[10] = { '\0' };
	sprintf_s(a, "%d", user_idnum);
	path += a;
	path += ".txt";
	for (i = 0; i < treasure_num; i++)
	{
		if (treasure[i].id == goods_id)
		{
			if (treasure[i].num == -1) cout << "��Ʒ�ѱ��¼ܣ�" << endl;
			else
			{
				if (treasure[i].num < num)
					cout << "��治�㣡" << endl;
				else if (num <= 0)
				{
					i = treasure_num - 1;
				}
				else
				{
					treasure[i].num -= num;
					renew_Avalon();
					ifstream in_file(path, ios::in);
					if (!in_file) exit(-1);
					string head;
					bool get_in_cart = false;
					getline(in_file, head);
					while (!in_file.eof())
					{
						in_file >> treasure_in_cart[k].id >> treasure_in_cart[k].name >> treasure_in_cart[k].brand >> treasure_in_cart[k].price >> treasure_in_cart[k].num;
						if (in_file.eof()) break;
						if (treasure_in_cart[k].id == goods_id)
						{
							get_in_cart = true;
							treasure_in_cart[k].num += num;
						}
						k++;
					}
					in_file.close();
					if (!get_in_cart)
					{
						treasure_in_cart[k].id = goods_id;
						treasure_in_cart[k].name = treasure[i].name;
						treasure_in_cart[k].brand = treasure[i].brand;
						treasure_in_cart[k].price = treasure[i].price;
						treasure_in_cart[k].num = num;
						k++;
					}
					break;
				}
			}
		}
	}
	if (i >= treasure_num)
		cout << "��������ȷ����ƷID������" << endl;
	else
	{
		ofstream out_file(path, ios::out);
		if (!out_file) exit(-1);
		out_file << "ID	����	Ʒ��	�۸�	����" << endl;
		for (int m = 0; m < k; m++)
		{
			out_file << treasure_in_cart[m].id << ' ' << treasure_in_cart[m].name << ' ' << treasure_in_cart[m].brand << ' ' << treasure_in_cart[m].price << ' ' << treasure_in_cart[m].num << endl;
		}
		out_file.close();
	}
	cout << "���ﳵ���У�" << endl;
	user_cart_display(user_idnum);
}

void Avalon::user_delete(int user_idnum)
{
	cout << "���ﳵ���У�" << endl;
	user_cart_display(user_idnum);

	cout << "������ƷID��������";
	string goods_id;
	int num;
	cin >> goods_id >> num;
	cout << "*******************" << endl;
	int i;
	int k = 0;
	Treasure  treasure_in_cart[100];
	string path = ".\\�û�\\user";
	char a[10] = { '\0' };
	sprintf_s(a, "%d", user_idnum);
	path += a;
	path += ".txt";
	for (i = 0; i < treasure_num; i++)
	{
		if (treasure[i].id == goods_id)
		{
			if (treasure[i].num == -1) cout << "��Ʒ�ѱ��¼�!" << endl;
			else
			{
				treasure[i].num += num;
				renew_Avalon();
				ifstream in_file(path, ios::in);
				if (!in_file) exit(-1);
				string head;
				bool get_in_cart = false;
				getline(in_file, head);
				while (!in_file.eof())
				{
					in_file >> treasure_in_cart[k].id >> treasure_in_cart[k].name >> treasure_in_cart[k].brand >> treasure_in_cart[k].price >> treasure_in_cart[k].num;
					if (in_file.eof()) break;
					if (treasure_in_cart[k].id == goods_id)
					{
						get_in_cart = true;
						if (treasure_in_cart[k].num < num)
						{
							cout << "��������ȷ��ID��������" << endl;
						}
						else {
							treasure_in_cart[k].num -= num;
							if (treasure_in_cart[k].num == 0)
								k--;
						}
					}
					k++;
				}
				in_file.close();
				if (!get_in_cart)
				{
					cout << "��������ȷ����ƷID������" << endl;
				}
				break;
			}
		}
	}
	if (i == treasure_num)
		cout << "��������ȷ����ƷID������" << endl;
	else
	{
		ofstream out_file(path, ios::out);
		if (!out_file) exit(-1);
		out_file << "ID	����	Ʒ��	�۸�	����" << endl;
		for (int m = 0; m < k; m++)
		{
			out_file << treasure_in_cart[m].id << ' ' << treasure_in_cart[m].name << ' ' << treasure_in_cart[m].brand << ' ' << treasure_in_cart[m].price << ' ' << treasure_in_cart[m].num << endl;
		}
		out_file.close();
	}
	cout << "���ﳵ���У�" << endl;
	user_cart_display(user_idnum);
	//Sleep(4 * 1000);
}

void  Avalon::user_display(int user_idnum)
{
	cout << "********************************************" << endl;
	cout << left << setw(10) << "ID" << setw(10) <<"����" << setw(10) <<"Ʒ��" << setw(10) <<"�۸�" << setw(10) <<"����" << endl;
	for (int i = 0; i < treasure_num; i++)
	{
		if(treasure[i].num>=0)
		cout << left << setw(10) <<treasure[i].id << setw(10)<< treasure[i].name << setw(10) << treasure[i].brand << setw(10) << treasure[i].price << setw(10) << treasure[i].num << endl;
	}
	cout << "********************************************" << endl;
}

void  Avalon::admin_display()
{

	cout << "********************************************" << endl;
	cout << left << setw(10) << "ID" << setw(10) << "����" << setw(10) << "Ʒ��" << setw(10) << "�۸�" << setw(10) << "����" << endl;
	for (int i = 0; i < treasure_num; i++)
	{
			cout << left << setw(10) << treasure[i].id << setw(10) << treasure[i].name << setw(10) << treasure[i].brand << setw(10) << treasure[i].price << setw(10) << treasure[i].num << endl;
	}
	cout << "********************************************" << endl;
}

void  Avalon::user_cart_display(int user_idnum)
{
	string path = ".\\�û�\\user";
	char a[10] = { '\0' };
	sprintf_s(a, "%d", user_idnum);
	path += a;
	path += ".txt";
	//cout << path << endl;
	ifstream in_file(path, ios::in);
	if (!in_file) exit(-1);
	//string line;
	cout << "********************************************" << endl;
	/*while (in_file.eof())
	{
		getline(in_file, line);
		cout << line << endl;
	}
	in_file.close();*/
	Treasure temp;
	string head;
	getline(in_file, head);
	cout << left << setw(10) << "ID" << setw(10) << "����" << setw(10) << "Ʒ��" << setw(10) << "�۸�" << setw(10) << "����" << endl;
	while (!in_file.eof())
	{
		in_file >> temp.id >> temp.name >> temp.brand >> temp.price >> temp.num;
		if (in_file.eof()) break;
		if(temp.num>=1)
			cout << left << setw(10) << temp.id << setw(10) << temp.name << setw(10) << temp.brand << setw(10) << temp.price << setw(10) << temp.num << endl;
	}
	cout << "********************************************" << endl;
}

void  Avalon::treasure_add()
{
	string newname;
	string newbrand;
	double newprice;
	int newnum;
	cout << "������Ʒ����";
	cin >> newname;
	cout << "����Ʒ������";
	cin >> newbrand;
	cout << "������Ʒ�۸�";
	cin >> newprice;
	cout << "������Ʒ������";
	cin >> newnum;
	int i;
	for (i = 0; i < treasure_num; i++)
	{
		if (treasure[i].name == newname && treasure[i].brand == newbrand)
		{
			treasure[i].num += newnum;
			treasure[i].price = newprice;
			break;
		}
	}
	if (i == treasure_num)
	{
		
		char a[10] = { '\0' };
		sprintf_s(a, "%d", treasure_num);
		treasure_num++;
		string strs = "F";
		int len;
		for (len = 0;; len++)
		{
			if (a[len] == '\0')
				break;
			for (int s = 0; s < 3 - len; s++)
				strs += "0";
			strs += a;
			treasure[i].name = newname;
			treasure[i].brand = newbrand;
			treasure[i].price = newprice;
			treasure[i].num = newnum;
			treasure[i].id = strs;
		}
	}
	renew_Avalon();
}

void Avalon::treasure_delete()
{
	cout << "������ƷID��";
	string goods_id;
	cin >> goods_id;
	cout << "*******************" << endl;
	int i;
	for (i = 0; i < treasure_num; i++)
	{
		if (treasure[i].id == goods_id)
		{
			treasure[i].num = -1;
		}
	}
	if (i == treasure_num)
		cout << "��������ȷ����ƷID������" << endl;
	else
	{
		renew_Avalon();
	}
}

void Avalon::change_treasure_numorprice()
{
	cout << "������ƷID��";
	string goods_id;
	int num;
	double newprice;
	cin >> goods_id;
	cout << "�����޸ĺ���Ʒ����";
	cin>> num;
	cout << "�����޸ĺ���Ʒ�۸�";
	cin >> newprice;
	cout << "*******************" << endl;
	int i;
	for (i = 0; i < treasure_num; i++)
	{
		if (treasure[i].id == goods_id)
		{
			treasure[i].num = num;
			treasure[i].price = newprice;
		}
	}
	if (i == treasure_num)
		cout << "��������ȷ����ƷID������" << endl;
	else
	{
		renew_Avalon();
	}
}


void  Avalon::sold_display()
{
	ifstream in_file(".\\�̵�\\�����嵥.txt", ios::in);
	if (!in_file) exit(-1);
	//string line;
	cout << "*****************************************************************************************" << endl;
	Treasure temp;
	string head;
	getline(in_file, head);
	string username;
	cout << left << setw(10) << "ID" << setw(10) << "����" << setw(10) << "Ʒ��" << setw(10) << "�۸�" << setw(10) << "����" <<setw(10) << "�û���" << endl;
	while (!in_file.eof())
	{
		in_file >> temp.id >> temp.name >> temp.brand >> temp.price; if (in_file.eof()) break; 
		in_file >> temp.num >> username;
		
		if (temp.num >= 1)
			cout << left << setw(10) << temp.id << setw(10) << temp.name << setw(10) << temp.brand << setw(10) << temp.price << setw(10) << temp.num << setw(10) <<username << endl;
	}
	cout << "*****************************************************************************************" << endl;
}

void Avalon::user_order(int user_idnum)
{
	cout << "��ȷ�϶�����" << endl;
	user_cart_display(user_idnum);
	cout << "========================" << endl;
	cout << "1.ȥ֧��   2.������" << endl;
	cout << "========================" << endl;
	cout << "��ѡ��";
	string choose;
	cin >> choose;
	if (choose == "1")
	{
		ofstream out_file(".\\�̵�\\�����嵥.txt", ios::app);
		if (!out_file) exit(-1);
		string path = ".\\�û�\\user";
		char a[10] = { '\0' };
		sprintf_s(a, "%d", user_idnum);
		path += a;
		path += ".txt";
		ifstream in_file(path, ios::in);
		if (!in_file) exit(-1);
		Treasure temp;
		string head;
		getline(in_file, head);
		while (!in_file.eof())
		{
			in_file >> temp.id >> temp.name >> temp.brand >> temp.price >> temp.num;
			if (in_file.eof()) break;
			if (temp.num >= 1)
			out_file << endl  << temp.id <<' ' << temp.name <<' ' << temp.brand <<' ' << temp.price << ' ' << temp.num <<' '<< "user"<< user_idnum;
		}
		out_file.close();
		in_file.close();
		string path2 = ".\\�û�\\user";
		char a2[10] = { '\0' };
		sprintf_s(a2, "%d", user_idnum);
		path2 += a2;
		path2 += ".txt";
		ofstream out(path2, ios::out);
		string head2 = "ID	����	Ʒ��	�۸�	����";
		out << head2 << endl;
		out.close();
		cout << "֧���ɹ���лл�ݹˣ�" << endl;
		Sleep(3 * 1000);
	}

}