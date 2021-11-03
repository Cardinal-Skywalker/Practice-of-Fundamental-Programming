#pragma once
#include<iostream>
#include<string>
#include<stack>
#include<queue>
#include<cmath>
#include<windows.h>
#include"complex.h"
using namespace std;
string pretreat(string str);//字符串预处理
bool check_str(string str);//合法性检验
queue<string> get_postfix(string str);//中缀表达式转后缀
complex str_transfer(string str);//字符串转复数
string com_transfer(complex x);//复数转字符串
