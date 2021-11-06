#include<iostream>
#include<fstream>
#include<windows.h>
#include"Gilgamesh.h"
#include"Avalon.h"
#include"User.h"
#include"welcome.h"
#include"adminop.h"
#include"userop.h"
using namespace std;


int main()
{
	system("cls");
	welcome_info();
	boot_interface();
	int choose;
	cout << "选择操作:";
 	cin >> choose;
	while (choose != 5)
	{
		if (choose == 1)
		{
			user_sign_in();
		}
		if (choose == 2)
		{
			user_sign_up();
		}
		if (choose == 3)
		{
			admin_sign_in();
		}
		if (choose == 4)
		{
			admin_sign_up();
		}
		system("cls");
		welcome_info();
		boot_interface();
		cout << "选择操作:";
		cin >> choose;
	}

	goodbye_info();
	Sleep(4 * 1000);
}