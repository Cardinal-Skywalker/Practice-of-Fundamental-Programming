#include<iostream>
#include<fstream>
#include<Windows.h>
#include<iomanip>
#include"Avalon.h"
using namespace std;

void Avalon::init_Avalon()
{
	ifstream in_file(".\\商店\\店铺信息.txt", ios::in);
	if (!in_file)
		exit(-1);
	in_file >> user_num >> admin_num>> treasure_num;
	in_file.close();
	ifstream in(".\\商店\\库存.txt", ios::in);
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
	ofstream out_file(".\\商店\\店铺信息.txt", ios::out);
	if (!out_file)
		exit(-1);
	out_file <<user_num << ' ' << admin_num<<' '<<treasure_num;
	out_file.close();
	ofstream out(".\\商店\\库存.txt", ios::out);
	string head = "ID	名称	品牌	价格	数量";
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
	cout << "输入商品ID和数量：";
	string goods_id;
	int num;
	cin >> goods_id >> num;
	cout << "*******************" << endl;
	int i;
	int k = 0;
	Treasure  treasure_in_cart[100];
	string path = ".\\用户\\user";
	char a[10] = { '\0' };
	sprintf_s(a, "%d", user_idnum);
	path += a;
	path += ".txt";
	for (i = 0; i < treasure_num; i++)
	{
		if (treasure[i].id == goods_id)
		{
			if (treasure[i].num == -1) cout << "商品已被下架！" << endl;
			else
			{
				if (treasure[i].num < num)
					cout << "库存不足！" << endl;
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
		cout << "请输入正确的商品ID和数量" << endl;
	else
	{
		ofstream out_file(path, ios::out);
		if (!out_file) exit(-1);
		out_file << "ID	名称	品牌	价格	数量" << endl;
		for (int m = 0; m < k; m++)
		{
			out_file << treasure_in_cart[m].id << ' ' << treasure_in_cart[m].name << ' ' << treasure_in_cart[m].brand << ' ' << treasure_in_cart[m].price << ' ' << treasure_in_cart[m].num << endl;
		}
		out_file.close();
	}
	cout << "购物车中有：" << endl;
	user_cart_display(user_idnum);
}

void Avalon::user_delete(int user_idnum)
{
	cout << "购物车中有：" << endl;
	user_cart_display(user_idnum);

	cout << "输入商品ID和数量：";
	string goods_id;
	int num;
	cin >> goods_id >> num;
	cout << "*******************" << endl;
	int i;
	int k = 0;
	Treasure  treasure_in_cart[100];
	string path = ".\\用户\\user";
	char a[10] = { '\0' };
	sprintf_s(a, "%d", user_idnum);
	path += a;
	path += ".txt";
	for (i = 0; i < treasure_num; i++)
	{
		if (treasure[i].id == goods_id)
		{
			if (treasure[i].num == -1) cout << "商品已被下架!" << endl;
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
							cout << "请输入正确的ID和数量！" << endl;
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
					cout << "请输入正确的商品ID和数量" << endl;
				}
				break;
			}
		}
	}
	if (i == treasure_num)
		cout << "请输入正确的商品ID和数量" << endl;
	else
	{
		ofstream out_file(path, ios::out);
		if (!out_file) exit(-1);
		out_file << "ID	名称	品牌	价格	数量" << endl;
		for (int m = 0; m < k; m++)
		{
			out_file << treasure_in_cart[m].id << ' ' << treasure_in_cart[m].name << ' ' << treasure_in_cart[m].brand << ' ' << treasure_in_cart[m].price << ' ' << treasure_in_cart[m].num << endl;
		}
		out_file.close();
	}
	cout << "购物车中有：" << endl;
	user_cart_display(user_idnum);
	//Sleep(4 * 1000);
}

void  Avalon::user_display(int user_idnum)
{
	cout << "********************************************" << endl;
	cout << left << setw(10) << "ID" << setw(10) <<"名称" << setw(10) <<"品牌" << setw(10) <<"价格" << setw(10) <<"数量" << endl;
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
	cout << left << setw(10) << "ID" << setw(10) << "名称" << setw(10) << "品牌" << setw(10) << "价格" << setw(10) << "数量" << endl;
	for (int i = 0; i < treasure_num; i++)
	{
			cout << left << setw(10) << treasure[i].id << setw(10) << treasure[i].name << setw(10) << treasure[i].brand << setw(10) << treasure[i].price << setw(10) << treasure[i].num << endl;
	}
	cout << "********************************************" << endl;
}

void  Avalon::user_cart_display(int user_idnum)
{
	string path = ".\\用户\\user";
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
	cout << left << setw(10) << "ID" << setw(10) << "名称" << setw(10) << "品牌" << setw(10) << "价格" << setw(10) << "数量" << endl;
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
	cout << "输入商品名：";
	cin >> newname;
	cout << "输入品牌名：";
	cin >> newbrand;
	cout << "输入商品价格：";
	cin >> newprice;
	cout << "输入商品数量：";
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
	cout << "输入商品ID：";
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
		cout << "请输入正确的商品ID和数量" << endl;
	else
	{
		renew_Avalon();
	}
}

void Avalon::change_treasure_numorprice()
{
	cout << "输入商品ID：";
	string goods_id;
	int num;
	double newprice;
	cin >> goods_id;
	cout << "输入修改后商品数：";
	cin>> num;
	cout << "输入修改后商品价格：";
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
		cout << "请输入正确的商品ID和数量" << endl;
	else
	{
		renew_Avalon();
	}
}


void  Avalon::sold_display()
{
	ifstream in_file(".\\商店\\已售清单.txt", ios::in);
	if (!in_file) exit(-1);
	//string line;
	cout << "*****************************************************************************************" << endl;
	Treasure temp;
	string head;
	getline(in_file, head);
	string username;
	cout << left << setw(10) << "ID" << setw(10) << "名称" << setw(10) << "品牌" << setw(10) << "价格" << setw(10) << "数量" <<setw(10) << "用户名" << endl;
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
	cout << "请确认订单！" << endl;
	user_cart_display(user_idnum);
	cout << "========================" << endl;
	cout << "1.去支付   2.再想想" << endl;
	cout << "========================" << endl;
	cout << "请选择：";
	string choose;
	cin >> choose;
	if (choose == "1")
	{
		ofstream out_file(".\\商店\\已售清单.txt", ios::app);
		if (!out_file) exit(-1);
		string path = ".\\用户\\user";
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
		string path2 = ".\\用户\\user";
		char a2[10] = { '\0' };
		sprintf_s(a2, "%d", user_idnum);
		path2 += a2;
		path2 += ".txt";
		ofstream out(path2, ios::out);
		string head2 = "ID	名称	品牌	价格	数量";
		out << head2 << endl;
		out.close();
		cout << "支付成功！谢谢惠顾！" << endl;
		Sleep(3 * 1000);
	}

}