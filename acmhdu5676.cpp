//============================================================================
// Name        : helloworld.cpp
// Author      : ahu
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
/*
ztr loves lucky numbers. Everybody knows that positive integers are lucky if their decimal representation doesn't contain digits other than 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

Lucky number is super lucky if it's decimal representation contains equal amount of digits 4 and 7. For example, numbers 47, 7744, 474477 are super lucky and 4, 744, 467 are not.

One day ztr came across a positive integer n. Help him to find the least super lucky number which is not less than n.
ztr喜欢幸运数字，他对于幸运数字有两个要求
1：十进制表示法下只包含4、7
2：十进制表示法下4和7的数量相等
比如47,474477就是
而4,744,467则不是

现在ztr想知道最小的但不小于n的幸运数字是多少
*/



#include<list>
#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<algorithm>
#include<functional>
#include<queue>
#include<string>
using namespace std;

typedef unsigned long long ulong;

bool func(string& vec, int idx, int Number4, int Number7, string& res)
{
	if (idx >= vec.size())
		return true;
	if (vec[idx] < '4')
	{
		while (Number4>0)
		{
			res.push_back('4');
			--Number4;
		}
		while (Number7 > 0)
		{
			res.push_back('7');
			--Number7;
		}
		return true;
	}
	if (vec[idx] == '4')
	{
		if (Number4 > 0)
		{
			res.push_back('4');
			--Number4;
			if (func(vec, idx + 1, Number4, Number7, res))
				return true;
			else
			{
				++Number4;
				res.pop_back();
				if (Number7 > 0)
				{
					res.push_back('7');
					--Number7;
					while (Number4 > 0)
					{
						res.push_back('4');
						--Number4;
					}
					while (Number7 > 0)
					{
						res.push_back('7');
						--Number7;
					}
					return true;
				}
				else
					return false;
			}
		}
		else
		{
			while (Number7 > 0)
			{
				res.push_back('7');
				--Number7;
			}
			return true;
		}
	}
	if (vec[idx] > '4' && vec[idx] < '7')
	{
		if (Number7 > 0)
		{
			res.push_back('7');
			--Number7;
			while (Number4 > 0)
			{
				res.push_back('4');
				--Number4;
			}
			while (Number7 > 0)
			{
				res.push_back('7');
				--Number7;
			}
			return true;
		}
		else
			return false;
	}
	if (vec[idx] == '7')
	{
		if (Number7 > 0)
		{
			res.push_back('7');
			--Number7;
			if (func(vec, idx + 1, Number4, Number7, res))
				return true;
			else
			{
				res.pop_back();
				++Number7;
				return false;
			}
		}
		else
			return false;
	}
	return false;
}

string minLuckyNumber(string n)
{
	size_t S = n.size();
	//ulong res = 0;
	string res;
	if ((S & 1) == 0)
	{
		if (func(n, 0, (S >> 1), (S >> 1), res))
			return res;
		//res.clear();
		res = string();
		S += 2;
	}
	else
		++S;
	S >>= 1;
	for (size_t i = 0; i < S; ++i)
		res.push_back('4');
	for (size_t i = 0; i < S; ++i)
		res.push_back('7');
	return res;
}


int main()
{
	istream& in = cin;
	//ifstream in("input.txt");
	int T;
	in >> T;
	for (int i = 0; i < T; ++i)
	{
		string s;
		in >> s;
		//in >> n;
		cout << minLuckyNumber(s) << endl;
	}

	return 0;
}
