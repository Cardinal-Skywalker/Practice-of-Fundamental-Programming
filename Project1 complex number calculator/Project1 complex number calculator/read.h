#pragma once
#include<iostream>
#include<string>
#include<stack>
#include<queue>
#include<cmath>
#include<windows.h>
#include"complex.h"
using namespace std;
string pretreat(string str);//�ַ���Ԥ����
bool check_str(string str);//�Ϸ��Լ���
queue<string> get_postfix(string str);//��׺���ʽת��׺
complex str_transfer(string str);//�ַ���ת����
string com_transfer(complex x);//����ת�ַ���
