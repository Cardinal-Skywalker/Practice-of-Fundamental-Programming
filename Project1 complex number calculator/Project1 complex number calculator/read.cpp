#include<iostream>
#include<string>
#include<stack>
#include<queue>
#include<cmath>
#include <sstream>
#include<windows.h>
#include"complex.h"
using namespace std;

//合法性预检验
bool check_str(string str)
{
	int len = str.length();
	int par = 0;
	int mod = 0;
	bool ifbreak = false;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD word = FOREGROUND_RED;
	WORD word2 = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE;
	for (int i = 0; i < len; i++)
	{		
		if (par < 0)
		{
			for (int j = 0; j < i; j++)
				cout << str[j];
			SetConsoleTextAttribute(handle, word);
			cout << str[i];
			SetConsoleTextAttribute(handle, word2);
			for (int j = i + 1; j < len; j++)
				cout << str[j];
			SetConsoleTextAttribute(handle, word);
			cout << ' ' << "error: parentheses cannot match." << endl;
			ifbreak = true;
			break;
		}
		//左括号后不能是^ ) + * /
		if (str[i] == '(')
		{
			par++;
			//cout << "(" << par << endl;
			if (i == len - 1) break;
			else if (str[i + 1] == '^' || str[i + 1] == ')' || str[i + 1] == '+'|| str[i + 1] == '*'|| str[i + 1] == '/')
			{
				for (int j = 0; j < i; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << str[i] << str[i + 1];
				SetConsoleTextAttribute(handle, word2);
				for (int j = i + 2; j < len; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << ' ' << "error: illegle input after left-parenthes." << endl;
				ifbreak = true;
				break;
			}
		}
		//右括号后不能是arg,cjg,数字
		else if (str[i] == ')')  
		{
			par--;
			//cout << ")" << par << endl;
			if (i == len - 1) break;
			else if (str[i + 1] == 'a' || str[i + 1] == 'c' || (str[i + 1] >= '0' && str[i + 1] <= '9'))
			{
				for (int j = 0; j < i; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << str[i] << str[i + 1];
				SetConsoleTextAttribute(handle, word2);
				for (int j = i + 2; j < len; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << ' ' << "error: illegle input after right-parenthes." << endl;
				ifbreak = true;
				break;
			}	
		}
		//||不嵌套
		else if (str[i] == '|' && mod == 0)
		{ 
			mod++;
			if (i == len - 1) break;
			else if (str[i + 1] == '+' || str[i + 1] == '-' || str[i + 1] == ')'|| str[i + 1]=='*'|| str[i + 1] == '/'||str[i + 1] == '|')
			{
				for (int j = 0; j < i; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << str[i] << str[i + 1];
				SetConsoleTextAttribute(handle, word2);
				for (int j = i + 2; j < len; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << ' ' << "error: illegle input after left-magnitude." << endl;
				ifbreak = true;
				break;
			}
		}
		else if (str[i] == '|' && mod == 1) 
		{
			mod--;
			if (i == len - 1) break;
			else if (str[i + 1] == 'i' || str[i + 1] == 'a' || str[i + 1] == 'c' || (str[i + 1] >='0' && str[i + 1] <= '9'))
			{
				SetConsoleTextAttribute(handle, word2);
				for (int j = 0; j < i; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << str[i] << str[i + 1];
				SetConsoleTextAttribute(handle, word2);
				for (int j = i + 2; j < len; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << ' ' << "error: illegle input after right-magnitude." << endl;
				ifbreak = true;
				break;
			}
		}
		else if (str[i] == 'a')
		{
			if (i > len - 6)
			{
				SetConsoleTextAttribute(handle, word2);
				for (int j = 0; j < i; j++)
					cout << str[j];
				for (int j = i; j < len; j++)
				{
					SetConsoleTextAttribute(handle, word);
					cout << str[j];
				}
				SetConsoleTextAttribute(handle, word);
				cout << "error: wrong input in arg." << endl;
				ifbreak = true;
				break;
			}
			if(str[i+1]!='r') {
				for (int j = 0; j < i; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << str[i] << str[i + 1];
				SetConsoleTextAttribute(handle, word2);
				for (int j = i + 2; j < len; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << ' ' << "error: illegle input after a." << endl;
				ifbreak = true;
				break;
			}
			if(str[i+2]!='g') {
				for (int j = 0; j < i; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << str[i] << str[i + 1]<<str[i+2];
				SetConsoleTextAttribute(handle, word2);
				for (int j = i + 3; j < len; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << ' ' << "error: illegle input after r." << endl;
				ifbreak = true;
				break;
			}
			if(str[i+3] != '(') {
				SetConsoleTextAttribute(handle, word2);
				for (int j = 0; j < i; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << str[i] << str[i + 1]<< str[i + 2]<< str[i + 3];
				SetConsoleTextAttribute(handle, word2);
				for (int j = i +4 ; j < len; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << ' ' << "error: illegle input after arg." << endl;
				ifbreak = true;
				break;
			}
			par++;
			i = i + 3;
		}
		else if (str[i] == 'c')
		{
			if (i > len - 6)
			{
				SetConsoleTextAttribute(handle, word2);
				for (int j = 0; j < i; j++)
					cout << str[j];
				for (int j = i; j < len; j++)
				{
					SetConsoleTextAttribute(handle, word);
					cout << str[j];
				}
				SetConsoleTextAttribute(handle, word);
				cout << "error: wrong input in cjg." << endl;
				ifbreak = true;
				break;
			}
			if (str[i + 1] != 'j') {
				SetConsoleTextAttribute(handle, word2);
				for (int j = 0; j < i; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << str[i] << str[i + 1];
				SetConsoleTextAttribute(handle, word2);
				for (int j = i + 2; j < len; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << ' ' << "error: illegle input after c." << endl;
				ifbreak = true;
				break;
			}
			if (str[i + 2] != 'g') {
				SetConsoleTextAttribute(handle, word2);
				for (int j = 0; j < i; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << str[i] << str[i + 1] << str[i + 2];
				SetConsoleTextAttribute(handle, word2);
				for (int j = i + 3; j < len; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << ' ' << "error: illegle input after j." << endl;
				ifbreak = true;
				break;
			}
			if (str[i + 3] != '(') {
				SetConsoleTextAttribute(handle, word2);
				for (int j = 0; j < i; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << str[i] << str[i + 1] << str[i + 2] << str[i + 3];
				SetConsoleTextAttribute(handle, word2);
				for (int j = i + 4; j < len; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << ' ' << "error: illegle input after cjg." << endl;
				ifbreak = true;
				break;
			}
			par++;
			i = i + 3;
		}
		//i后不能是( i 数 a ,c,|
		else if (str[i] == 'i')
		{
			if (i == len - 1) break;
			else if (str[i + 1] == 'a' || str[i + 1] == 'c' || (str[i + 1] >= '0' && str[i + 1] <= '9')||str[i+1]=='('||str[i + 1] == 'i'||(str[i + 1] == '|'&&mod==0))
			{
				SetConsoleTextAttribute(handle, word2);
				for (int j = 0; j < i; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << str[i] << str[i + 1];
				SetConsoleTextAttribute(handle, word2);
				for (int j = i + 2; j < len; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << ' ' << "error: illegle input after i." << endl;
				ifbreak = true;
				break;
			}
		}
		//^后不能是),i,^,-,/
		else if (str[i] == '^')
		{
			if (i == len - 1) break;
			else if (str[i + 1] == ')' || str[i + 1] == 'i' || str[i + 1]=='^' || str[i + 1] == '-'|| str[i + 1] == '/')
			{
				SetConsoleTextAttribute(handle, word2);
				for (int j = 0; j < i; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << str[i] << str[i + 1];
				SetConsoleTextAttribute(handle, word2);
				for (int j = i + 2; j < len; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << ' ' << "error: illegle input after power( ^ )." << endl;
				ifbreak = true;
				break;
			}
		}
		//+后不能是+ - * / ^ )
		else if (str[i] == '+')
		{
			if (i == len - 1) break;
			else if (str[i + 1] == ')' || str[i + 1] == '+' || str[i + 1] == '^' || str[i + 1] == '-'|| str[i + 1] == '*'|| str[i + 1] == '/')
			{
				SetConsoleTextAttribute(handle, word2);
				for (int j = 0; j < i; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << str[i] << str[i + 1];
				SetConsoleTextAttribute(handle, word2);
				for (int j = i + 2; j < len; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << ' ' << "error: illegle input after addition( + )." << endl;
				SetConsoleTextAttribute(handle, word2);
				ifbreak = true;
				break;
			}
		}
		else if (str[i] == '-')
		{
			if (i == len - 1) break;
			else if (str[i + 1] == ')' || str[i + 1] == '+' || str[i + 1] == '^' || str[i + 1] == '-' || str[i + 1] == '*' || str[i + 1] == '/')
			{
				for (int j = 0; j < i; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << str[i] << str[i + 1];
				SetConsoleTextAttribute(handle, word2);
				for (int j = i + 2; j < len; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << ' ' << "error: illegle input after subtraction( - )." << endl;
				ifbreak = true;
				break;
			}
		}
		else if (str[i] == '*')
		{
			if (i == len - 1) break;
			else if (str[i + 1] == ')' || str[i + 1] == '+' || str[i + 1] == '^' || str[i + 1] == '-' || str[i + 1] == '*' || str[i + 1] == '/')
			{
				for (int j = 0; j < i; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << str[i] << str[i + 1];
				SetConsoleTextAttribute(handle, word2);
				for (int j = i + 2; j < len; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << ' ' << "error: illegle input after multiplication ( * )." << endl;
				ifbreak = true;
				break;
			}
		}
		else if (str[i] == '/')
		{
			if (i == len - 1) break;
			else if (str[i + 1] == ')' || str[i + 1] == '+' || str[i + 1] == '^' || str[i + 1] == '-' || str[i + 1] == '*' || str[i + 1] == '/')
			{
				for (int j = 0; j < i; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << str[i] << str[i + 1];
				for (int j = i + 2; j < len; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << ' ' << "error: illegle input after division( / )." << endl;
				ifbreak = true;
				break;
			}
		}
		else if (str[i] >= '0' && str[i] <= '9')
		{
			if (i == len - 1) break;
			if (str[i + 1] == ' ')
			{
				int j = i + 1;
				while (str[j] == ' ' && j < len)
				{
					j++;
				}
				if (j == len) break;
				else if ((str[j] >= '0' && str[j] <= '9') || str[j] == '(' || str[j] == '|')
				{
					for (int k = 0; k < i; k++)
						cout << str[k];
					SetConsoleTextAttribute(handle, word);
					cout << str[i] << str[j];
					for (int k = j+1; j < len; j++)
						cout << str[j];
					SetConsoleTextAttribute(handle, word);
					cout << ' ' << "error: illegle input after real number." << endl;
					ifbreak = true;
					break;
				}
			}
		}
		else if (str[i] == '.')
		{
			if (i == len - 1) break;
			if (str[i + 1] < '0' || str[i + 1]>'9')
			{
				for (int j = 0; j < i; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << str[i] << str[i + 1];
				for (int j = i + 2; j < len; j++)
					cout << str[j];
				SetConsoleTextAttribute(handle, word);
				cout << ' ' << "error: illegle input after radix point( . )." << endl;
				ifbreak = true;
				break;
			}
		}
		else if (str[i] == ' ') {

		}
		else
		{
			for (int j = 0; j < i; j++)
				cout << str[j];
			SetConsoleTextAttribute(handle, word);
			cout << str[i] ;
			SetConsoleTextAttribute(handle, word2);
			for (int j = i + 1; j < len; j++)
				cout << str[j];
			SetConsoleTextAttribute(handle, word);
			cout << ' ' << "error: illegle input." << endl;
			ifbreak = true;
			break;
		}
	}
	if (!ifbreak)
	{
		SetConsoleTextAttribute(handle, word2);
		for (int j = 0; j < len-1; j++)
			cout << str[j];
		if (str[len - 1] == '+')
		{
			SetConsoleTextAttribute(handle, word);
			cout << str[len - 1];
			SetConsoleTextAttribute(handle, word);
			cout << ' ' << "there is a extra '+' in the end." << endl;
			ifbreak = true;
		}
		else if (str[len - 1] == '.')
		{
			SetConsoleTextAttribute(handle, word);
			cout << str[len - 1];
			SetConsoleTextAttribute(handle, word);
			cout << ' ' << "there is a extra '.' in the end." << endl;
			ifbreak = true;
		}
		else if (str[len - 1] == '-')
		{
			SetConsoleTextAttribute(handle, word);
			cout << str[len - 1];
			SetConsoleTextAttribute(handle, word);
			cout << ' ' << "there is a extra '-' in the end." << endl;
			ifbreak = true;
		}
		else if (str[len - 1] == '*')
		{
			SetConsoleTextAttribute(handle, word);
			cout << str[len - 1];
			SetConsoleTextAttribute(handle, word);
			cout << ' ' << "there is a extra '*' in the end." << endl;
			ifbreak = true;
		}
		else if (str[len - 1] == '/')
		{
			SetConsoleTextAttribute(handle, word);
			cout << str[len - 1];
			SetConsoleTextAttribute(handle, word);
			cout << ' ' << "there is a extra '/' in the end." << endl;
			ifbreak = true;
		}
		else if (str[len - 1] == '^')
		{
			SetConsoleTextAttribute(handle, word);
			cout << str[len - 1];
			SetConsoleTextAttribute(handle, word);
			cout << ' ' << "there is a extra '^' in the end." << endl;
			ifbreak = true;
		}
		else { SetConsoleTextAttribute(handle, word2);  cout << str[len - 1]; }
		if ( par != 0)
		{
			SetConsoleTextAttribute(handle, word);
			cout <<' ' << "error: parentheses cannot match." << endl;
			ifbreak = true;
		}
		else if (mod!= 0)
		{
			SetConsoleTextAttribute(handle, word);
			cout << ' '<<"error: magnitude('|') cannot match." << endl;
			ifbreak = true;
		}
	}
	SetConsoleTextAttribute(handle, word2);
	cout << endl;
	return ifbreak;
}

//字符串预处理
string pretreat(string str)
{
	int len = str.length();
	string tstr = "";
	int judge = 0;
	for (int i = 0; i < len; i++)
	{
		if (str[i] == ' ') continue;
		if (i == 0)
		{
			if (str[i] == '-')
			{
				tstr+='0';
				tstr+='-';
			}
			else if (str[i] == '|')
			{
				tstr+='m';
				tstr+='(';
				judge++;
			}
			else if (str[i] == 'a') {
				i = i + 2;
				tstr+='a';
			}
			else if (str[i] == 'c') {
				i = i + 2;
				tstr+='c';
			}
			else
				tstr+=str[i];
		}
		else if (str[i] == 'i' && str[i - 1] == ')')
		{
			tstr+='*';
			tstr+='i';
		}
		else if (str[i] == '-' && str[i - 1] == '(')
		{
			tstr+='0';
			tstr+='-';
		}
		else if (str[i] == '|')
		{
			if (judge % 2 == 0)
			{
				tstr+='m';
				tstr+='(';
				judge++;
			}
			else
			{
				tstr+= ')';
				judge++;
			}
		}
		else if (str[i] == 'a') {
			i = i + 2;
			tstr+='a';
		}
		else if (str[i] == 'c') {
			i = i + 2;
			tstr+='c';
		}
		else
			tstr += str[i];
	}
	return tstr;
}

//in stack priority
int get_isp(char ch)
{
	if (ch == '(') return 1;
	else if (ch == '+' || ch == '-') return 3;
	else if (ch == '*' || ch == '/') return 5;
	else if (ch == '^') return 7;
	else if (ch == 'a' || ch == 'm' || ch == 'c') return 9;
	else if (ch == ')') return 10;
	else return 0;
}
//in coming priority
int get_icp(char ch)
{
	if (ch == '(') return 10;
	else if (ch == '+' || ch == '-') return 2;
	else if (ch == '*' || ch == '/') return 4;
	else if (ch == '^') return 6;
	else if (ch == 'a' || ch == 'm' || ch == 'c') return 8;
	else if (ch == ')') return 1;
	else return 0;
}
//中缀转后缀
queue<string> get_postfix(string str)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD word = FOREGROUND_RED;
	WORD word2 = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	stack<char> opstack;
	queue<string> res;
	string temp;
	int len = str.length();
	int i = 0;
	int dotcount=0;
	while (i < len)
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.')
		{
			temp.push_back(str[i]);
			if(str[i] == '.')
				dotcount++;
			if (dotcount > 1) { SetConsoleTextAttribute(handle, word); cerr << "input wrong! You cannot input decimal point like this!" << endl;			SetConsoleTextAttribute(handle, word2); while (!res.empty()) res.pop();res.push("NULL"); break; }
		}
		else if (str[i] == 'i')
		{
			temp.push_back(str[i]);
			res.push(temp);
			temp.clear();
			dotcount = 0;
		}
		else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'||str[i]=='^'||str[i] == '('||str[i]==')'|| str[i] == 'a' || str[i] == 'm' || str[i] == 'c')
		{
			if (!temp.empty())
			{
				res.push(temp);
				temp.clear();
				dotcount = 0;
			}
			if (opstack.empty())
				opstack.push(str[i]);
			else
			{
				while (!opstack.empty())
				{
					char tem = opstack.top();
					if (get_isp(tem) > get_icp(str[i]))//如果栈顶元素的优先级大于当前元素,退出栈顶元素加入res中 
					{
						temp.push_back(tem);
						res.push(temp);
						temp.clear();
						dotcount = 0;
						opstack.pop();
						if(!opstack.empty())
							tem = opstack.top();
					}
					else break;
				}
				if (str[i] == ')')
				{
					if (opstack.empty()) { SetConsoleTextAttribute(handle, word); cerr << "lack of (" << endl; SetConsoleTextAttribute(handle, word2);
					}
					if(opstack.top()=='(')
					opstack.pop();
				}
				else opstack.push(str[i]);
			}
			
		}
		if (i == len - 1&&!temp.empty())
		{
			res.push(temp);
			temp.clear();
			dotcount = 0;
		}
		i++;
	}
	while (!opstack.empty())
		{
		temp.push_back(opstack.top());
		res.push(temp);
		temp.clear();
		dotcount = 0;
		opstack.pop();
		}
	return res;
}

//字符串转复数
complex str_transfer(string str)
{
	int len = str.length();
	complex targ;
	targ.real = 0;
	targ.img = 0;
	if (str[len - 1] == 'i')
	{
		double x = 0;
		double y = 0;
		int locateop;
		for (locateop = 0; locateop < len; locateop++)
			if (str[locateop] == '+') break;
		if (locateop == len)
		{
			for (locateop = 0; locateop < len; locateop++)
				if (str[locateop] == '-') break;
		}
		if (locateop > 16&&locateop!=len) { cerr << "WARNING: The number you input is out of range! The result can be wrong." << endl; }
		if (str[0] == '-')
		{
			if (locateop == 0)
			{
				for (locateop = 1; locateop < len; locateop++)
					if (str[locateop] == '-') break;
			}
			if (locateop > 16 && locateop != len) { cerr << "WARNING: The number you input is out of range! The result can be wrong." << endl; }
			if (locateop == len)
			{
				string strtemp = str.substr(0, len - 1);
				if (len > 2)
					y = stod(strtemp);
				else y = -1;
				x = 0;
			}
			else if (locateop == len - 2)
			{
				string strtemp = str.substr(0, len - 2);
				x = stod(strtemp);
				y = 1;
				if (str[locateop] == '-') y = -y;
			}
			else if (locateop < len - 2)
			{
				string strtempx = str.substr(0, locateop);
				x = stod(strtempx);
				string strtempy = str.substr(locateop, len - locateop);
				y = stod(strtempy);
			}
		}
		else {
			for (locateop = 0; locateop < len; locateop++)
				if (str[locateop] == '+') break;
			if (locateop == len)
			{
				for (locateop = 0; locateop < len; locateop++)
					if (str[locateop] == '-') break;
			}
			//纯虚数
			if (locateop == len)
			{
				string strtemp = str.substr(0, len - 1);
				if (len > 1)
					y = stod(strtemp);
				else y = 1;
				x = 0;
				//cout <<fixed<< " trans" << y << endl;
			}
			else if (locateop == len - 2)
			{
				string strtemp = str.substr(0, len - 2);
				x = stod(strtemp);
				y = 1;
				if (str[locateop] == '-') y = -y;
			}
			else if (locateop < len - 2)
			{
				string strtempx = str.substr(0, locateop);
				x = stod(strtempx);
				string strtempy = str.substr(locateop, len - locateop);
				y = stod(strtempy);
			}
		}
		targ.real = x;
		targ.img = y;
	}
	else if (str[len-1] >= '0' && str[len-1] <= '9')
	{
		if (len> 16) { cerr << "WARNING: The number you input is out of range! The result can be wrong." << endl; }
		double x = 0;
		x = stod(str);
		targ.img = 0;
		targ.real = x;

	}
	else { cerr << "What your input is not a complex number."; exit(-1); }
	return targ;
}

//复数转字符串
string com_transfer(complex x)
{
	string targ="";
	char realpart[100] = { '\0' };
	sprintf_s(realpart, "%.10lf", x.real);
	targ += realpart;
	if (x.img != 0)
	{
		if(x.img>0)
			targ += '+';
		char imgpart[100] = {'\0'};
		sprintf_s(imgpart, "%.10lf", x.img);
		targ += imgpart;
		targ += 'i';
	}
	return targ;
}

