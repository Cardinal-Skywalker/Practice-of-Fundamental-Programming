#include<iostream>
#include<fstream>
#include<windows.h>
#include"Gilgamesh.h"
#include"Avalon.h"
#include"User.h"
#include"welcome.h"
#include"adminop.h"
using namespace std;


int main()
{
	system("cls");
	boot_interface();
	int choose;
	cin >> choose;
	while (choose != 5)
	{
		if (choose == 1)
		{
			void user_sign_in();
		}
		if (choose == 2)
		{
			void user_sign_up();
		}
		if (choose == 3)
		{
			admin_sign_in();
		}
		if (choose == 4)
		{
			admin_sign_up();
		}
	}

	goodbye_info();
}