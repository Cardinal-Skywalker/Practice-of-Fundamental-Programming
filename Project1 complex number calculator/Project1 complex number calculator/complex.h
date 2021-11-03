#pragma once
#include<iostream>
#include<cmath>
#include<cassert>
struct complex
{
	double real;
	double img;
	void clear()
	{
		real = 0;
		img = 0;
	}
	complex()
	{
		real = 0;
		img = 0;
	}
	complex operator+ (complex x)
	{
		complex c;
		c.img = x.img + img;
		c.real = x.real + real;
		return c;
	}
	complex operator- (complex x)
	{
		complex c;
		c.img = -x.img + img;
		c.real = -x.real + real;
		return c;
	}
	complex operator* (complex x)
	{
		complex c;
		c.img = x.img * real + x.real * img;
		c.real = x.real * real - x.img * img;
		return c;
	}
	complex operator/ (complex x)
	{
		complex c;
		c.img = (-x.img * real + x.real * img) / (x.real * x.real + x.img * x.img);
		c.real = (x.real * real + x.img * img) /(x.real*x.real+x.img*x.img);
		return c;
	}
};