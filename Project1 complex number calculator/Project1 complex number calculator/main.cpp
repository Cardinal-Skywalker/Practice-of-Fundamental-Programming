#include<iostream>
#include<stdlib.h>
#include<windows.h>
#include <conio.h>
#include"welcome.h"
#include"read.h"
#include"calculate.h"
#include"complex.h"

using namespace std;

int main()
{
	welcome_info();
	cout.precision(6);
	cout << fixed;
	bool back_choose = true;
	int badchoose = 1;
	while (back_choose)
	{
		system("cls");
		welcome_info();
		choose_info();
		string x;
		cin >> x;
		system("cls");
		welcome_info();
		if (x == "1")
		{
			badchoose = 0;
			string str;
			welcome_input(1);
			cin >> str;
			while (str != "quit" && str != "back")
			{
						if (str == "quit" || str == "back") {
							if (str == "quit") back_choose = false;
							else { system("cls"); welcome_info(); }
							break; 
						}
						system("cls");
						welcome_info();
						cout << "Your input is: ";
						bool ifillegle = check_str(str);
						if (!ifillegle)
						{
							string stri = pretreat(str);
							queue<string> basis104;
							basis104 = get_postfix(stri);
							if (basis104.front() != "NULL")
							{
								string result = finalcalculate(basis104);
								legal_output(result);
								fstream out_file(".\\userinput.txt",ios::app);
								if (!out_file) exit(-1);
								out_file << str << endl;
								out_file << result << endl;
								out_file.close();
							}
						}
						else
						{
							cout << "your input is illegle." << endl;
						}
						welcome_input(1);
						cin >> str;
			 }
			if(str=="quit") back_choose = false;
		}
		else if (x == "2")
		{
			badchoose = 0;
			welcome_input(2);
			string str1;
			cout << "Input the first number: ";
			cin >> str1;
			string str2;
			complex x1, x2, res;
			while (str1 != "quit" && str2 != "quit" && str1 != "back" && str2 != "back")
			{
				bool ifdis = true;
				cout << "Input the second number: ";
				cin >> str2;
				if (str2 == "quit" || str2 == "back") break;
				system("cls");
				welcome_info();
				string result1, result2;
				cout << "The first number is: ";
				bool ifillegle1 = check_str(str1);
				if (!ifillegle1)
				{
					string stri1 = pretreat(str1);
					queue<string> basis1;
					basis1 = get_postfix(stri1);
					if (basis1.front() != "NULL")
					{
						result1 = finalcalculate(basis1);
					}
				}
				else
				{
					cout << "your input is illegle." << endl;
					ifdis = false;
				}
				cout<< "The second number is: ";
				bool ifillegle2 = check_str(str2);
				if (!ifillegle2)
				{
					string stri2 = pretreat(str2);
					queue<string> basis2;
					basis2 = get_postfix(stri2);
					if (basis2.front() != "NULL")
					{
					result2 = finalcalculate(basis2);
					}
				}
				else
				{
					cout << "your input is illegle." << endl;
					ifdis = false;
				}
				if (ifdis)
				{
					x1 = str_transfer(result1);
					x2 = str_transfer(result2);
					res = x1 - x2;
					res.real = sqrt(res.real * res.real + res.img * res.img);
					res.img = 0;
					cout << "The distance is: " << res.real << endl;
					
				}
				cout << "----------------------------------------" << endl;
				cout << "Input the first number: ";
				cin >> str1;
			}
			if (str1 == "quit" || str2 == "quit")
			{
				back_choose =false;
			}
			if (str1 == "back" || str2 == "back")
			{
				back_choose = true;
			}

		}
		else if (x == "3")
		{
			badchoose = 0;
			string str = " ";
			while (str != "quit" && str != "back"&& str != "no"&& str != "n"&&str != "N")
			{
				welcome_input(3);
				double a, b, c;
				complex res1, res2;
				cout << "Please input the coefficient of x^2 :";
				cin >> a;
				cout << "Please input the coefficient of x :";
				cin >> b;
				cout << "Please input the constant coefficient( x^0) :";
				cin >> c;
				double delta = b * b - 4 * a * c;
				cout << "Your equation is:" << a << " * x ^ 2" << " + " << b << "*x" << "+" << c << " = 0" << endl;
				if (a == 0)
				{
					if (b == 0)
					{
						if (c == 0) cout << "The result can be any number you like." << endl;
						else cout << "No solution can meet this equation." << endl;
					}
					else
						cout << "The solution is: x =" << -c / b << endl;
				}
				else
				{
					if (delta == 0)
						cout << "The solution is: x_1 = x_2 = " << -b / (2 * a) << endl;
					else if (delta > 0)
					{
						cout << "The first solution is: x_1 = " << -b / (2 * a) + sqrt(delta) / (2 * a) << endl;
						cout << "The second solution is x_2 = " << -b / (2 * a) - sqrt(delta) / (2 * a) << endl;
					}
					else if (delta < 0)
					{
						if (a > 0)
						{
							cout << "The first solution is " << -b / (2 * a) << "+" << sqrt(-delta) / (2 * a) << "i" << endl;
							cout << "The second solution is " << -b / (2 * a) << "-" << sqrt(-delta) / (2 * a) << "i" << endl;
						}
						else
						{
							cout << "The first solution is " << -b / (2 * a) << "+" << -sqrt(-delta) / (2 * a) << "i" << endl;
							cout << "The second solution is " << -b / (2 * a) << sqrt(-delta) / (2 * a) << "i" << endl;
						}
					}
				}
				cout << "Do you want to continue ?(you can use 'back' to choose functions or 'quit' to exit the program.)" << endl;
				cin >> str;
				system("cls");
				welcome_info();
			}
			if (str == "quit")
				back_choose = false;
		}
		else if (x == "4") 
		{
		system("cls");
		welcome_info();
		welcome_input(4);
		char name[] = ".\\userinput.txt";
		int len = CountLines(name);
		int lineCount = 2;
		char ch;
		for(;;)
		{
		ifstream in_file(name, ios::ate);
		if (!in_file)
		{
			cout << "cannot open file";
			Sleep(2 * 1000);
			exit( -1);
		}
		in_file.seekg(-2, in_file.cur);
			//cout << len << endl;
		    ch = _getch();
			if (ch == 27) break;
			ch = _getch();
			if (ch == 72) {
				lineCount = lineCount + 2;
			}
			else if (ch == 80) {
				lineCount = lineCount - 2;
			}
			else continue;
			//cout << lineCount<<endl;
			if (lineCount < 4)  lineCount = 4;
			if (lineCount > len) lineCount = len;
			//cout << lineCount << endl;
			for (int i = 0; i < lineCount-1; i++)
			{
				// 查看前一个字符是否为回车符
				while (in_file.peek() != in_file.widen('\n'))
				{
					in_file.seekg(-1, in_file.cur);
				}
				// 跳过一行了，所以继续向前跳
				in_file.seekg(-1, in_file.cur);
			}
			in_file.seekg(2, in_file.cur);
			string  line,past_str;
			getline(in_file, past_str);
			getline(in_file, past_str);
			getline(in_file, line);
			system("cls");
			welcome_info();
			welcome_input(4);
			cout << "Your history is: " << past_str << endl;
			cout << "The result is: " << line << endl;
			in_file.clear();
			in_file.close();
		}
			
		}
		else if (x == "5") { back_choose = false; }
		else 
		{
		badchoose++;
		if (badchoose == 4)
		{ 
		cout << "WTF, ARE YOU KIDDING ME? WHY DO YOU ALWAYS CHALLENGE THE RULE? I DON'T THINK GIVING YOUR MORE CHOICE IS USEFUL. U_U" << endl;
		back_choose = false;	
		Sleep(1 * 1000);
		goodbye_info();
		Sleep(3 * 1000);
		return 0;
		}
		else
			cout << "I will give you another chance to choose the functions seriously! X_X" << endl;
		}
		
	}
	cout << "Do you want to save your legal input and result?(y/n)" << endl;
	char ans;
	cin >> ans;
	if (ans == 'n' || ans == 'b')
	{
		fstream out_file1(".\\userinput.txt", ios::out|ios::trunc);
		out_file1 << endl;
		out_file1 << endl;
		if (!out_file1) exit(-1);
		out_file1.close();
	}

	cout << "So you always think you can leave with 'quit' right?" << endl;
	Sleep(3 * 1000);
	cout << "Well, you are the boss. U_U" << endl;
	Sleep(1 * 1000);
	goodbye_info();
	Sleep(3 * 1000);
	return 0;
}