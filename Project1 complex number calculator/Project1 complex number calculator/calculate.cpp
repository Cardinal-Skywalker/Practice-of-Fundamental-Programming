#include<iostream>
#include<string>
#include<stack>
#include<queue>
#include<queue>
#include<cmath>
#include<windows.h>
#include"complex.h"
#include"read.h"
#include<cassert>

using namespace std;
string finalcalculate(queue<string> q)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD word = FOREGROUND_RED;
	WORD word2 = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	assert(!q.empty());
	complex result;
	result.img = 0;
	result.real = 0;
	string res;
	stack<string> tempnum;
	while (!q.empty())
	{
		string str;
		 str=q.front();
		if (str !="+" && str != "-" && str != "*" && str != "/" && str != "^" && str != "(" && str != ")" && str != "a" && str != "m" && str != "c")
		{
			tempnum.push(str);
			q.pop();
		}
		else if (str == "+")
		{
			string operand1,operand2;
			if (tempnum.empty()) cerr << "There is no operand for operation +" << endl;
			operand1 = tempnum.top();
			tempnum.pop();
			if (tempnum.empty()) cerr << "There is only one operand for operation +" << endl;
			operand2 = tempnum.top();
			//cout << operand1 << ' ' << operand2 << endl;
			tempnum.pop();
			complex num1;
			num1.clear();
			num1= str_transfer(operand1);
			complex num2;
			num2.clear();
			num2 = str_transfer(operand2);
			result = num1 + num2;
			//cout << result.real<<' '<< result.img << endl;
			tempnum.push(com_transfer(result));
			//cout << com_transfer(result) << "op+"<<endl;
			q.pop();
			result.clear();
			num1.clear();
			num2.clear();

		}
		else if (str == "-")
		{
			string operand1, operand2;
			if (tempnum.empty()) cerr << "There is no operand for operation +" << endl;
			operand1 = tempnum.top();
			tempnum.pop();
			if (tempnum.empty()) cerr << "There is only one operand for operation +" << endl;
			operand2 = tempnum.top();
			//cout << operand1 << ' ' << operand2 << endl;
			tempnum.pop();
			complex num1 = str_transfer(operand1);
			complex num2 = str_transfer(operand2);
			result = num2 - num1;
			//cout << result.real << ' ' << result.img << endl;
			tempnum.push(com_transfer(result));
			//cout << com_transfer(result) << "op-" << endl;
			q.pop();
			result.clear();
		}
		else if (str == "*")
		{
			string operand1, operand2;
			if (tempnum.empty()) cerr << "There is no operand for operation +" << endl;
			operand1 = tempnum.top();
			tempnum.pop();
			if (tempnum.empty()) cerr << "There is only one operand for operation +" << endl;
			operand2 = tempnum.top();
			//cout << operand1 << ' ' << operand2 << endl;
			tempnum.pop();
			complex num1 = str_transfer(operand1);
			complex num2 = str_transfer(operand2);
			result = num2 * num1;
			//cout << result.real << ' ' << result.img << endl;
			tempnum.push(com_transfer(result));
			//cout << com_transfer(result) << "op*" << endl;
			q.pop();
			result.clear();
		}
		else if (str == "/")
		{
			string operand1, operand2;
			if (tempnum.empty()) cerr << "There is no operand for operation +" << endl;
			operand1 = tempnum.top();
			tempnum.pop();
			if (tempnum.empty()) cerr << "There is only one operand for operation +" << endl;
			operand2 = tempnum.top();
			tempnum.pop();
			complex num1 = str_transfer(operand1);
			complex num2 = str_transfer(operand2);
			if (num1.img == 0 && num1.real == 0) {
				SetConsoleTextAttribute(handle, word);
				cerr << "Divisor has become 0 unexpectedly!" << endl;
				SetConsoleTextAttribute(handle, word2);
			}
			result = num2 / num1;
			tempnum.push(com_transfer(result));
			q.pop();
			result.clear();
		}
		else if (str == "a")
		{
			string operand1;
			if (tempnum.empty()) cerr << "There is no operand for operation arg" << endl;
			operand1 = tempnum.top();
			//cout << operand1 << endl;
			tempnum.pop();
			complex num1 = str_transfer(operand1);
			result.real = atan2(num1.img,num1.real);
			result.img = 0;
			//cout << result.real << ' ' << result.img << endl;
			tempnum.push(com_transfer(result));
			//cout << com_transfer(result) << "oparg" << endl;
			q.pop();
			result.clear();
		}
		else if (str == "c")
		{
			string operand1;
			if (tempnum.empty()) cerr << "There is no operand for operation cjg" << endl;
			operand1 = tempnum.top();
			tempnum.pop();
			complex num1 = str_transfer(operand1);
			result.real = num1.real;
			result.img = -num1.img;
			tempnum.push(com_transfer(result));
			q.pop();
			result.clear();
		}
		else if (str == "m")
		{
			string operand1;
			if (tempnum.empty()) cerr << "There is no operand for operation mod" << endl;
			operand1 = tempnum.top();
			tempnum.pop();
			complex num1 = str_transfer(operand1);
			result.real = sqrt(num1.real * num1.real + num1.img * num1.img);
			result.img = 0;
			tempnum.push(com_transfer(result));
			q.pop();
			result.clear();
		}
		else if (str == "^")
		{
		string operand1, operand2;
		if (tempnum.empty()) cerr << "There is no operand for operation ^" << endl;
		operand1 = tempnum.top();
		tempnum.pop();
		if (tempnum.empty()) cerr << "There is only one operand for operation ^" << endl;
		operand2 = tempnum.top();
		//cout << operand1 << ' ' << operand2 << endl;
		tempnum.pop();
		complex num1 = str_transfer(operand1);
		complex num2 = str_transfer(operand2);
		result.img= 0;
		result.real = 1;
		if(num1.img != 0){
			SetConsoleTextAttribute(handle, word);
			cerr << "Exponent is not a real number!" << endl;
			SetConsoleTextAttribute(handle, word2);
		}
		if (num1.real >= 0)
		{
			for (int i = 0; i < num1.real; i++)
				result = result * num2;
		}
		else {
			for (int i = 0; i > num1.real; i--)
				result = result /num2;
		}
		//cout << result.img << endl;
		tempnum.push(com_transfer(result));
		q.pop();
		result.clear();
		}
	}
	result.clear();
	assert(q.empty());
	return tempnum.top();
}