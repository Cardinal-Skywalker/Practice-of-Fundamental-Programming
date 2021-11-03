#include<iostream>
#include<fstream>
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
		in >> treasure[i].id >> treasure[i].name >> treasure[i].price >> treasure[i].num;
		i++;
	}
	if (treasure_num != i)
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
		out << treasure[i].id << treasure[i].name << treasure[i].price << treasure[i].num;
	}

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
	char a[3];
	_itoa_s(user_idnum, a, 10);
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
	if (i == treasure_num)
		cout << "请输入正确的商品ID和数量" << endl;
	else
	{
		ofstream out_file(path, ios::out);
		if (!out_file) exit(-1);
		out_file << "ID	名称	品牌	价格	数量" << endl;
		for (int m = 0; m < k; m++)
		{
			out_file << treasure_in_cart[k].id << ' ' << treasure_in_cart[k].name << ' ' << treasure_in_cart[k].brand << ' ' << treasure_in_cart[k].price << ' ' << treasure_in_cart[k].num << endl;
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
	char a[3];
	_itoa_s(user_idnum, a, 10);
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
			out_file << treasure_in_cart[k].id << ' ' << treasure_in_cart[k].name << ' ' << treasure_in_cart[k].brand << ' ' << treasure_in_cart[k].price << ' ' << treasure_in_cart[k].num << endl;
		}
		out_file.close();
	}
}

void  Avalon::user_display(int user_idnum)
{
	ifstream in_file(".\\商店\\库存" , ios::in);
	if (!in_file) exit(-1);
	string line;
	cout << "**************************************" << endl;
	while (in_file.eof())
	{
		getline(in_file, line);
		cout << line << endl;
	}
	in_file.close();
	cout << "**************************************" << endl;
}

void  Avalon::user_cart_display(int user_idnum)
{
	string path = ".\\用户\\uer";
	char a[3];
	_itoa_s(user_idnum, a, 10);
	path += a;
	path += ".txt";
	ifstream in_file(path, ios::in);
	if (!in_file) exit(-1);
	string line;
	cout << "**************************************" << endl;
	while (in_file.eof())
	{
		getline(in_file, line);
		cout << line << endl;
	}
	in_file.close();
	cout << "**************************************" << endl;
}



