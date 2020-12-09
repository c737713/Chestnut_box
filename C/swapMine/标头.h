#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

bool equal(int A, int B)
{
	bool res = false;
	if (A == B)
	{
		res = true;
	}
	return res;
}
//对比函数,如果相同则输出1,不同输出0.
