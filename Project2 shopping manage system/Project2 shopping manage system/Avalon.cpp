#include<iostream>
#include<fstream>
#include<string>
#include<Windows.h>
#include<iomanip>
#include<conio.h>
#include"welcome.h"
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
	string pathh = ".\\�û�\\history_user";
	char a2[10] = { '\0' };
	sprintf_s(a2, "%d", user_idnum);
	pathh += a2;
	pathh += ".txt";
	ofstream out(pathh, ios::app);
	if (!out) exit(-1);

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
<<<<<<< HEAD
							out << endl << treasure_in_cart[k].id << ' ' << treasure_in_cart[k].name << ' ' << treasure_in_cart[k].brand << ' ' << treasure_in_cart[k].price << ' ' << num << ' ' << 1;
=======
							out << endl << treasure_in_cart[k].id << ' ' << treasure_in_cart[k].name << ' ' << treasure_in_cart[k].brand << ' ' << treasure_in_cart[k].price << ' ' << treasure_in_cart[k].num << ' ' << 1;
>>>>>>> e7e1c9595f1628c89278f19eaa6d6ca37ab0ace0
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
						out << endl << treasure_in_cart[k].id << ' ' << treasure_in_cart[k].name << ' ' << treasure_in_cart[k].brand << ' ' << treasure_in_cart[k].price << ' ' << treasure_in_cart[k].num << ' ' << 1;
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
	out.close();
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

	string pathh = ".\\�û�\\history_user";
	char a2[10] = { '\0' };
	sprintf_s(a2, "%d", user_idnum);
	pathh += a2;
	pathh += ".txt";
	ofstream out(pathh, ios::app);
	if (!out) exit(-1);

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
							treasure[i].num += num;
							renew_Avalon();
							treasure_in_cart[k].num -= num;
							out << endl << treasure_in_cart[k].id << ' ' << treasure_in_cart[k].name << ' ' << treasure_in_cart[k].brand << ' ' << treasure_in_cart[k].price << ' ' <<num << ' ' << 2;
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
	out.close();
	//Sleep(4 * 1000);
}

void  Avalon::user_display(int user_idnum)
{
	cout << "******************************************************" << endl;
	cout << left << setw(12) << "ID" << setw(12) <<"����" << setw(12) <<"Ʒ��" << setw(12) <<"�۸�" << setw(12) <<"����" << endl;
	for (int i = 0; i < treasure_num; i++)
	{
		if(treasure[i].num>=0)
		cout << left << setw(12) <<treasure[i].id << setw(12)<< treasure[i].name << setw(12) << treasure[i].brand << setw(12) << treasure[i].price << setw(12) << treasure[i].num << endl;
	}
	cout << "******************************************************" << endl;
}

void  Avalon::admin_display()
{

 cout << "******************************************************" << endl;
	cout << left << setw(12) << "ID" << setw(12) << "����" << setw(12) << "Ʒ��" << setw(12) << "�۸�" << setw(12) << "����" << endl;
	for (int i = 0; i < treasure_num; i++)
	{
			cout << left << setw(12) << treasure[i].id << setw(12) << treasure[i].name << setw(12) << treasure[i].brand << setw(12) << treasure[i].price << setw(12) << treasure[i].num << endl;
	}
 cout << "******************************************************" << endl;
}

void  Avalon::user_cart_display(int user_idnum)
{
	string path = ".\\�û�\\user";
	char a[10] = { '\0' };
	sprintf_s(a, "%d", user_idnum);
	path += a;
	path += ".txt";
	ifstream in_file(path, ios::in);
	if (!in_file) exit(-1);
<<<<<<< HEAD
 cout << "******************************************************" << endl;
=======
	cout << "********************************************" << endl;
>>>>>>> e7e1c9595f1628c89278f19eaa6d6ca37ab0ace0
	Treasure temp;
	string head;
	getline(in_file, head);
	cout << left << setw(12) << "ID" << setw(12) << "����" << setw(12) << "Ʒ��" << setw(12) << "�۸�" << setw(12) << "����" << endl;
	while (!in_file.eof())
	{
		in_file >> temp.id >> temp.name >> temp.brand >> temp.price >> temp.num;
		if (in_file.eof()) break;
		if(temp.num>=1)
			cout << left << setw(12) << temp.id << setw(12) << temp.name << setw(12) << temp.brand << setw(12) << temp.price << setw(12) << temp.num << endl;
	}
 cout << "******************************************************" << endl;
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
			if (treasure[i].num == -1)
				treasure[i].num++;
			treasure[i].num += newnum;
			treasure[i].price = newprice;
			break;
		}
	}
	if (i == treasure_num)
	{
		char a[10] = { '\0' };
		sprintf_s(a, "%04d", treasure_num);
		treasure_num++;
		string strs = "F";
			strs += a;
			treasure[i].name = newname;
			treasure[i].brand = newbrand;
			treasure[i].price = newprice;
			treasure[i].num = newnum;
			treasure[i].id = strs;
	}
	cout << "��ӳɹ���" << endl;
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
			break;
		}
	}
	if (i == treasure_num)
		cout << "��������ȷ����ƷID������" << endl;
	else
		cout << "ɾ���ɹ���" << endl;
	renew_Avalon();
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
			if (treasure[i].price != newprice)
			{
				for (int uid = 1; uid <= user_num; uid++)
				{
					if (check_cart_and_id(uid, goods_id))
					{
						string path = ".\\�û�\\admin2user";
						char a[10] = { '\0' };
						sprintf_s(a, "%d", uid);
						path += a;
						path += ".txt";
						ofstream out1(path, ios::app);
						if (!out1) exit(-1);
						out1 << endl << "��ע�⣡�����ﳵ�е���Ʒ��"<< treasure[i].brand<<"��"<< treasure[i].name<<"("<<goods_id<<")�м۸�䶯��"<<"��"<< treasure[i].price<<"�䶯Ϊ"<<newprice << endl;
						out1.close();
						renew_usercart(uid);
					}
				}
			}
			treasure[i].price = newprice;
			break;
		}
	}
	if (i == treasure_num)
		cout << "��������ȷ����ƷID������" << endl;
	else
<<<<<<< HEAD
		cout << "��Ʒ��Ϣ�޸ĳɹ���" << endl; 

	renew_Avalon();
}

=======
		cout << "��Ʒ��Ϣ�޸ĳɹ���" << endl;
	renew_Avalon();
}

>>>>>>> e7e1c9595f1628c89278f19eaa6d6ca37ab0ace0
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
	cout << left << setw(12) << "ID" << setw(12) << "����" << setw(12) << "Ʒ��" << setw(12) << "�۸�" << setw(12) << "����" <<setw(12) << "�û���" << endl;
	while (!in_file.eof())
	{
		in_file >> temp.id >> temp.name >> temp.brand >> temp.price; if (in_file.eof()) break; 
		in_file >> temp.num >> username;
		
		if (temp.num >= 1)
			cout << left << setw(12) << temp.id << setw(12) << temp.name << setw(12) << temp.brand << setw(12) << temp.price << setw(12) << temp.num << setw(12) <<username << endl;
	}
	cout << "*****************************************************************************************" << endl;
}

void Avalon::user_order(int user_idnum)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD word = FOREGROUND_RED;
	WORD word2 = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	SetConsoleTextAttribute(handle, word);
	cout << "��ȷ�϶�����" << endl;
	SetConsoleTextAttribute(handle, word2);
	user_cart_display(user_idnum);
	cout << "========================" << endl;
	cout << "1.ȥ֧��   2.������" << endl;
	cout << "========================" << endl;
	cout << "��ѡ��";
	string choose;
	cin >> choose;
	if (choose == "1")
	{
		double s = 0;
		string path = ".\\�û�\\user";
		char a[10] = { '\0' };
		sprintf_s(a, "%d", user_idnum);
		path += a;
		path += ".txt";
		ifstream in_file(path, ios::in);
		if (!in_file) exit(-1);
		string addr;
		cout << "�������ַ��" << endl;
		getchar();
		getline(cin, addr);
		Treasure temp;
		string head;
		getline(in_file, head);
		while (!in_file.eof())
		{
			in_file >> temp.id >> temp.name >> temp.brand >> temp.price >> temp.num;
			if (in_file.eof()) break;
			if (temp.num >= 1)
			{
				s = s + temp.num * temp.price;
			}
		}
		in_file.close();
		cout.precision(2);
		cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
		cout << "һ����Ҫ���" << fixed << s << "Ԫ" << "    ���͵�ַ��" << addr << endl;
		cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

		cout << "========================" << endl;
		cout << "1.����֧��   2.������" << endl;
		cout << "========================" << endl;
		cout << "��ѡ��";
		string choose2;
		cin >> choose2;
		if (choose2 == "1")
		{
		ofstream out_file(".\\�̵�\\�����嵥.txt", ios::app);
		if (!out_file) exit(-1);

		string patha = ".\\�û�\\order_user";
		char aa[10] = { '\0' };
		sprintf_s(aa, "%d", user_idnum);
		patha += aa;
		patha += ".txt";
		ofstream outa(patha, ios::app);
		if (!outa) exit(-1);
		outa << addr;

			ifstream in_file2(path, ios::in);

			if (!in_file2) exit(-1);

			string headt;
			getline(in_file2, headt);

			while (!in_file2.eof())
			{
				in_file2 >> temp.id >> temp.name >> temp.brand >> temp.price >> temp.num;
				if (in_file2.eof()) break;
				if (temp.num >= 1)
				{
					outa << endl << temp.id << ' ' << temp.name << ' ' << temp.brand << ' ' << temp.price << ' ' << temp.num;
					out_file << endl << temp.id << ' ' << temp.name << ' ' << temp.brand << ' ' << temp.price << ' ' << temp.num << ' ' << "user" << user_idnum;
				}
			}
			in_file2.close();

			outa << endl << "=" << ' ' << "=" << ' ' << "=" << ' ' << 0 << ' ' << 0;
			outa << endl << "��ַ" << ' ';
			outa.close();
			out_file.close();

			string path2 = ".\\�û�\\user";
			char a2[10] = { '\0' };
			sprintf_s(a2, "%d", user_idnum);
			path2 += a2;
			path2 += ".txt";
			ofstream out(path2, ios::out);
			string head2 = "ID	����	Ʒ��	�۸�	����";
			out << head2 << endl;
			out.close();
			SetConsoleTextAttribute(handle, word);
			cout << "֧���ɹ���лл�ݹˣ�" << endl;
			SetConsoleTextAttribute(handle, word2);
			Sleep(3 * 1000);
		}
		else
		{
			SetConsoleTextAttribute(handle, word);
			cout << "֧��ʧ�ܣ�" << endl;
			SetConsoleTextAttribute(handle, word2);
			Sleep(3 * 1000);
		}
	}

}

void Avalon::user_query(int user_idnum)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD word = FOREGROUND_RED;
	WORD word2 = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	string path = ".\\�û�\\history_user";
	char a[10] = { '\0' };
	sprintf_s(a, "%d", user_idnum);
	path += a;
	path += ".txt";
	ofstream out_file(path, ios::app);
	if (!out_file) exit(-1);
	cout << "�������ѯ���ݣ�";
	string search;
	int findnum = 0;
	getchar();
	getline(cin, search);
<<<<<<< HEAD
 cout << "******************************************************" << endl;
	cout << left << setw(12) << "ID" << setw(12) << "����" << setw(12) << "Ʒ��" << setw(12) << "�۸�" << setw(12) << "����" << endl;
=======
	cout << "********************************************" << endl;
	cout << left << setw(10) << "ID" << setw(10) << "����" << setw(10) << "Ʒ��" << setw(10) << "�۸�" << setw(10) << "����" << endl;
>>>>>>> e7e1c9595f1628c89278f19eaa6d6ca37ab0ace0
	bool ifcomplete = false;
	for (int i = 0; i < treasure_num; i++)
	{
		if (treasure[i].name == search)
		{	
			ifcomplete = true;
			if (treasure[i].num == -1)
				continue;
			findnum++;
			out_file << endl << treasure[i].id << ' ' << treasure[i].name << ' ' << treasure[i].brand << ' ' << treasure[i].price << ' ' << treasure[i].num << ' ' << 0;
<<<<<<< HEAD
			cout << left << setw(12) << treasure[i].id << setw(12) << treasure[i].name << setw(12) << treasure[i].brand << setw(12) << treasure[i].price << setw(12) << treasure[i].num << endl;
=======
			cout << left << setw(10) << treasure[i].id << setw(10) << treasure[i].name << setw(10) << treasure[i].brand << setw(10) << treasure[i].price << setw(10) << treasure[i].num << endl;
>>>>>>> e7e1c9595f1628c89278f19eaa6d6ca37ab0ace0
		}
	}
	for (int i = 0; i < treasure_num; i++)
	{
		if (treasure[i].brand == search)
		{
			ifcomplete = true;
			if (treasure[i].num == -1)
				continue;
			findnum++;
			out_file << endl << treasure[i].id << ' ' << treasure[i].name << ' ' << treasure[i].brand << ' ' << treasure[i].price << ' ' << treasure[i].num << ' ' << 0;
<<<<<<< HEAD
			cout << left << setw(12) << treasure[i].id << setw(12) << treasure[i].name << setw(12) << treasure[i].brand << setw(12) << treasure[i].price << setw(12) << treasure[i].num << endl;
=======
			cout << left << setw(10) << treasure[i].id << setw(10) << treasure[i].name << setw(10) << treasure[i].brand << setw(10) << treasure[i].price << setw(10) << treasure[i].num << endl;
>>>>>>> e7e1c9595f1628c89278f19eaa6d6ca37ab0ace0
		}
	}
	for (int i = 0; i < treasure_num; i++)
	{
		if (treasure[i].id == search)
		{
			ifcomplete = true;
			if (treasure[i].num == -1)
				continue;
			findnum++;
			out_file << endl << treasure[i].id << ' ' << treasure[i].name << ' ' << treasure[i].brand << ' ' << treasure[i].price << ' ' << treasure[i].num << ' ' << 0;
<<<<<<< HEAD
			cout << left << setw(12) << treasure[i].id << setw(12) << treasure[i].name << setw(12) << treasure[i].brand << setw(12) << treasure[i].price << setw(12) << treasure[i].num << endl;
=======
			cout << left << setw(10) << treasure[i].id << setw(10) << treasure[i].name << setw(10) << treasure[i].brand << setw(10) << treasure[i].price << setw(10) << treasure[i].num << endl;
>>>>>>> e7e1c9595f1628c89278f19eaa6d6ca37ab0ace0
		}
	}
	if (ifcomplete && findnum == 0)
	{
		cout << "������ѯ����Ʒ" << search << "���¼�!" << endl;
	}
	if (!ifcomplete)
	{
		int a[100];
		int b[100];
		int x = 0;
		for (int i = 0; i < treasure_num; i++)
		{
			bool iffind = false;
			a[x] = 0;
			b[x] = 0;
			for (int k = 0; k < search.length(); k++)
			{
				int last1 = 0;
				int last2 = 0;
				for (int j = last1; j < treasure[i].name.length(); j++)
				{
					if (search[k] == treasure[i].name[j])
					{
						if (k< search.length()-1&& j < treasure[i].name.length()-1&&(unsigned char)search[k] >= 0x81 && (unsigned char)search[k] <= 0xFE &&         //��λ
							(unsigned char)search[k + 1] >= 0x40 && (unsigned char)search[k + 1] <= 0xFE)
						{
							if (search[k + 1] == treasure[i].name[j + 1])
							{
								j++;
								k++;
								iffind = true;
								last1 = j;
								b[x]++;
							}
						}
						/*else if (treasure[i].name[j] >= 'a' && treasure[i].name[j] <= 'z' || treasure[i].name[j] >= 'A' && treasure[i].name[j] <= 'Z' || treasure[i].name[j] >= '0' && treasure[i].name[j] <= '9')
						{
							iffind = true;
							last1 = j;
							b[x]++;
						}*/
					}
				}	
				for (int j = last2; j < treasure[i].brand.length(); j++)
				{
					if (search[k] == treasure[i].brand[j])
					{
						if (k < search.length() - 1 && j < treasure[i].brand.length() - 1 && (unsigned char)search[k] >= 0x81 && (unsigned char)search[k] <= 0xFE &&         //��λ
							(unsigned char)search[k + 1] >= 0x40 && (unsigned char)search[k + 1] <= 0xFE)
						{
							if (search[k + 1] == treasure[i].brand[j + 1])
							{
								j++;
								k++;
								iffind = true;
								last1 = j;
								b[x]++;
							}
						}
						/*else if (treasure[i].name[j] >= 'a' && treasure[i].name[j] <= 'z' || treasure[i].name[j] >= 'A' && treasure[i].name[j] <= 'Z' || treasure[i].name[j] >= '0' && treasure[i].name[j] <= '9')
						{
							iffind = true;
							last1 = j;
							b[x]++;
						}*/
					}
				}

			}
			if (iffind)
			{
				a[x] = i;
				x++;
			}
		}
		
		for (int j = 0; j < x; j++)
		{
			for (int k = j; k < x; k++)
			{
				if (b[j] < b[k])
				{
					int temp = b[j];
					b[j] = b[k];
					b[k] = temp;
					temp = a[j];
					a[j] = a[k];
					a[k] = temp;
				}
			}
		}
		if (b[0] == 0)
		{
			SetConsoleTextAttribute(handle, word);
			cout << "������ѯ����Ʒ�����ڣ�" << endl;
			SetConsoleTextAttribute(handle, word2);
		}
		else
		{
			for (int i = 0; i < x; i++)
			{
				if (b[0] != 0)
				{
					out_file << endl << treasure[a[i]].id<<' '<< treasure[a[i]].name<<' ' << treasure[a[i]].brand<<' ' << treasure[a[i]].price<<' ' << treasure[a[i]].num << ' ' << 0;
<<<<<<< HEAD
					cout << left << setw(12) << treasure[a[i]].id << setw(12) << treasure[a[i]].name << setw(12) << treasure[a[i]].brand << setw(12) << treasure[a[i]].price << setw(12) << treasure[a[i]].num << endl;
=======
					cout << left << setw(10) << treasure[a[i]].id << setw(10) << treasure[a[i]].name << setw(10) << treasure[a[i]].brand << setw(10) << treasure[a[i]].price << setw(10) << treasure[a[i]].num << endl;
>>>>>>> e7e1c9595f1628c89278f19eaa6d6ca37ab0ace0
				}
			}
		}
	}
	out_file.close();
<<<<<<< HEAD
 cout << "******************************************************" << endl;
=======
	cout << "********************************************" << endl;
>>>>>>> e7e1c9595f1628c89278f19eaa6d6ca37ab0ace0
}

void  Avalon::user_history_display(int user_idnum)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD word = FOREGROUND_RED;
	WORD word2 = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	string path = ".\\�û�\\history_user";
	char a[10] = { '\0' };
	sprintf_s(a, "%d", user_idnum);
	path += a;
	path += ".txt";
	ifstream in_file(path, ios::in);
	if (!in_file) exit(-1);
	cout << "******************************************************" << endl;
	Treasure temp;
	int op;
	string head;
	getline(in_file, head);
<<<<<<< HEAD
	cout << left << setw(12) << "ID" << setw(12) << "����" << setw(12) << "Ʒ��" << setw(12) << "�۸�" << setw(12) << "����" << setw(12) << "����" << endl;
=======
	cout << left << setw(10) << "ID" << setw(10) << "����" << setw(10) << "Ʒ��" << setw(10) << "�۸�" << setw(10) << "����" << setw(10) << "����" << endl;
>>>>>>> e7e1c9595f1628c89278f19eaa6d6ca37ab0ace0
	while (!in_file.eof())
	{
		in_file >> temp.id >> temp.name;
		if (in_file.eof()) break;
		in_file >> temp.brand >> temp.price >> temp.num >> op;
		if (temp.num >= 1)
		{
<<<<<<< HEAD
			cout << left << setw(12) << temp.id << setw(12) << temp.name << setw(12) << temp.brand << setw(12) << temp.price << setw(12) << temp.num;
			SetConsoleTextAttribute(handle, word);
			if (op == 0) cout << left << setw(12) <<"��ѯ��Ʒ";
			else if (op == 1) cout << left << setw(12) << "�����Ʒ�����ﳵ";
			else if (op == 2) cout << left << setw(12) << "�ӹ��ﳵ������Ʒ";
=======
			cout << left << setw(10) << temp.id << setw(10) << temp.name << setw(10) << temp.brand << setw(10) << temp.price << setw(10) << temp.num;
			SetConsoleTextAttribute(handle, word);
			if (op == 0) cout << left << setw(10) <<"��ѯ��Ʒ";
			else if (op == 1) cout << left << setw(10) << "�����Ʒ�����ﳵ";
			else if (op == 2) cout << left << setw(10) << "�ӹ��ﳵ������Ʒ";
>>>>>>> e7e1c9595f1628c89278f19eaa6d6ca37ab0ace0
			SetConsoleTextAttribute(handle, word2);
			cout << endl;
		}
	}
	in_file.close();
	cout << "******************************************************" << endl;
	cout << "======================================================" << endl;
	cout << "1.�˳�   2.�����ʷ��¼" << endl;
	cout << "======================================================" << endl;
	string choose;
	cin >> choose;
	if (choose == "2")
	{
		ofstream out(path, ios::out);
		string head2 = "ID	����	Ʒ��	�۸�	����	����";
		out << head2;
		out.close();
		SetConsoleTextAttribute(handle, word);
		cout << "�����¼��ɾ����" << endl;
		SetConsoleTextAttribute(handle, word2);
		Sleep(3 * 1000);
	}
}

void Avalon::user_order_display(int user_idnum)
{
	Treasure order[10][10];
	int order_num[10];
	string address[10];
	string check;
	order_num[0] = 0;
	address[0] = " ";
	string patha = ".\\�û�\\order_user";
	char aa[10] = { '\0' };
	sprintf_s(aa, "%d", user_idnum);
	patha += aa;
	patha += ".txt";
	ifstream infile(patha, ios::in);
	if (!infile) exit(-1);
	int i = 0;
	int j = 0;
	infile >> check;
	while (!infile.eof())
	{
		if (check == "��ַ"&&j == 0)
			infile >> address[i];
		else if(j==0)
		{
			cerr << "��ַ��ȡ����";
			exit(-1);
		}
		if (infile.eof()) break;
		infile >> order[i][j].id;
		if (infile.eof()) break;
		infile >> order[i][j].name;
		if (infile.eof()) break;
		infile >> order[i][j].brand;
		if (infile.eof()) break;
		infile >> order[i][j].price;
		if (infile.eof()) break;
		infile >> order[i][j].num;
		if (infile.eof()) break;
		if (order[i][j].id == "=")
		{
			order_num[i] = j;
			i++;
			j = 0;
			infile >> check;
<<<<<<< HEAD
=======

>>>>>>> e7e1c9595f1628c89278f19eaa6d6ca37ab0ace0
			if (infile.eof()) break;
			continue;
		}
		j++;

	}
	char ch;
<<<<<<< HEAD
	int getnum = 0;
	for (;;)
	{
=======
	for (;;)
	{
		int getnum = 0;
>>>>>>> e7e1c9595f1628c89278f19eaa6d6ca37ab0ace0
		ch = _getch();
		if (ch == 27) break;
		ch = _getch();
		if (ch == 72)
		{
<<<<<<< HEAD
			getnum--;
		}
		else if (ch == 80)
		{
			getnum++;
=======
			getnum++;
		}
		else if (ch == 80)
		{
			getnum--;
>>>>>>> e7e1c9595f1628c89278f19eaa6d6ca37ab0ace0
		}
		if (getnum <= 0)
			getnum = 0;
		if (getnum >= i - 1)
			getnum = (i - 1) < 0 ? 0 : (i - 1);
		system("cls");
		welcome_info();
<<<<<<< HEAD
	//	cout << i << ' ' << getnum << endl;
		cout.precision(2);
		cout << "��Ķ�����" << endl;
		cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
		cout << left << setw(12) << "ID" << setw(12) << "����" << setw(12) << "Ʒ��" << setw(12) << "�۸�" << setw(12) << "����" << endl;
		double sum = 0;
		for (int s = 0; s < order_num[getnum]; s++)
		{
				cout << left << setw(12) << order[getnum][s].id << setw(12) << order[getnum][s].name << setw(12) << order[getnum][s].brand << setw(12) << order[getnum][s].price  << setw(12) << order[getnum][s].num << endl;
				sum = sum + order[getnum][s].price * order[getnum][s].num;
		}
		cout << "���͵�ַ��" << address[getnum] << endl;
		cout << "�ܼۣ�" << fixed << sum <<"Ԫ" << endl;
		cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
	}

	infile.close();
}

void Avalon::admin_to_user_display(int user_idnum)
{
 cout << "******************************************************" << endl;
	cout << "�̼����ԣ�" << endl;
	string path = ".\\�û�\\admin2user";
	char a[10] = { '\0' };
	sprintf_s(a, "%d", user_idnum);
	path += a;
	path+= ".txt";
	ifstream infile(path, ios::in);
	if (!infile) exit(-1);
	string line;
	getline(infile,line);
	while (!infile.eof())
	{
		getline(infile, line);
		cout << line << endl;;
	}
	infile.close();
 cout << "******************************************************" << endl;
}

void Avalon::user_to_admin(int user_idnum)
{
	admin_to_user_display(user_idnum);
	cout << "�������������Է�����" << endl;
	string note;
	cin >> note;
	ofstream out(".\\����Ա\\���԰�.txt",ios::app);
	if (!out)
		exit(-1);
	out << endl<<note<<' '<<user_idnum<<' '<<1;
	out.close();
	cout << "��л���ķ���������Ա�ᾡ�촦��" << endl;
	Sleep(2 * 1000);
}

void  Avalon::note_display(int t)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD word0 = FOREGROUND_RED;
	WORD word2 = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	ifstream in_file(".\\����Ա\\���԰�.txt", ios::in);
	if (!in_file) exit(-1);
	//string line;
	cout << "*****************************************************************************************" << endl;
	string word;
	int userid;
	int x;
	getline(in_file, word);
	while (!in_file.eof())
	{
		in_file >> word >> userid >> x;
		if (x == 1)
		{
			cout << "user" << userid << "�����ԣ�" << word;
			SetConsoleTextAttribute(handle, word0);
			cout<< "  ������" << endl;
			SetConsoleTextAttribute(handle, word2);
		}
		else
		{
			if (t == 1)
				cout << "user" << userid << "�����ԣ�" << word << "  �Ѵ���" << endl;
		}
	}
	cout << "*****************************************************************************************" << endl;
	in_file.close();
}

void Avalon::note_handle()
{
	cout << "������Ҫ�����û��ı�ţ�";
	int name;
	cin >> name;
	system("cls");
	welcome_info();
	cout << "��Ҫ��ϵ�Ŀͻ���user" << name << endl;
	cout << "ta�������ǣ�" << endl;
	ifstream in_file(".\\����Ա\\���԰�.txt", ios::in);
	if (!in_file) exit(-1);
	cout << "*****************************************************************************************" << endl;
	string word[100];
	int userid[100];
	int x[100];
	int i = 0;
	getline(in_file, word[0]);
	while (!in_file.eof())
	{
		in_file >> word[i] >> userid[i] >> x[i];
		if (x[i] == 1&&userid[i] == name)
			cout << word[i] << endl;
		i++;
	}
	cout << "*****************************************************************************************" << endl;
	in_file.close();
	cout << "��������Ļظ���";
	string answer;
	cin >> answer;

	string path = ".\\�û�\\admin2user";
	char a[10] = { '\0' };
	sprintf_s(a, "%d", name);
	path += a;
	path += ".txt";
	ofstream out1(path, ios::app);
	if (!out1) exit(-1);
	out1 << endl << answer;
	out1.close();
	ofstream out(".\\����Ա\\���԰�.txt", ios::out);
	if (!out) exit(-1);
	if (i <= 90)
	{
		for (int k = 0; k < i; k++)
		{
			if (userid[k] == name)
				out << endl << word[k] << ' ' << userid[k] << ' ' << 0;
			else
			{
				out << endl << word[k] << ' ' << userid[k] << ' ' << x[k];
			}
		}
	}
	out.close();
	system("cls");
	welcome_info();
	cout << "������ɣ����԰������ݣ�" << endl;
	note_display(1);
}

void Avalon::clear_userboard(int user_idnum)
{
	string path = ".\\�û�\\admin2user";
	char a[10] = { '\0' };
	sprintf_s(a, "%d", user_idnum);
	path += a;
	path += ".txt";
	ofstream out(path, ios::out);
	out.close();
}

bool Avalon::check_cart_and_id(int user_idnum,string fixid)
{
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
		if (temp.num >= 1 && temp.id == fixid)
			return true;
	}
	return false;
}

void Avalon::renew_usercart(int user_idnum)
{
	int k = 0;
	Treasure  treasure_in_cart[100];
	string path = ".\\�û�\\user";
	char a[10] = { '\0' };
	sprintf_s(a, "%d", user_idnum);
	path += a;
	path += ".txt";
	ifstream in_file(path, ios::in);
	if (!in_file) exit(-1);
	string head;
	getline(in_file, head);
	while (!in_file.eof())
	{
			in_file >> treasure_in_cart[k].id >> treasure_in_cart[k].name >> treasure_in_cart[k].brand >> treasure_in_cart[k].price >> treasure_in_cart[k].num;
			if (in_file.eof()) break;
			for (int i = 0; i < treasure_num; i++)
			{
				if (treasure[i].id == treasure_in_cart[k].id)
				{
					treasure_in_cart[k].price = treasure[i].price;
					break;
				}
			}
			k++;
	}
	//k--;
	in_file.close();
	ofstream out_file(path, ios::out);
	if (!out_file) exit(-1);
	out_file << "ID	����	Ʒ��	�۸�	����" << endl;
	for (int m = 0; m < k; m++)
	{
		out_file << treasure_in_cart[m].id << ' ' << treasure_in_cart[m].name << ' ' << treasure_in_cart[m].brand << ' ' << treasure_in_cart[m].price << ' ' << treasure_in_cart[m].num << endl;
	}
	out_file.close();
=======
		cout << "��Ķ�����" << endl;
		cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
		cout << left << setw(10) << "ID" << setw(10) << "����" << setw(10) << "Ʒ��" << setw(10) << "�۸�" << setw(10) << "����" << endl;
		for (int s = 0; s < order_num[getnum]; s++)
		{
				cout << left << setw(10) << order[getnum][s].id << setw(10) << order[getnum][s].name << setw(10) << order[getnum][s].brand << setw(10) << order[getnum][s].price  << setw(10) << order[getnum][s].num << endl;
		}
		cout << "���͵�ַ��" << address[getnum] << endl;
		cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;


	}



	infile.close();
>>>>>>> e7e1c9595f1628c89278f19eaa6d6ca37ab0ace0
}