//============================================================================
// Name        : helloworld.cpp
// Author      : ahu
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include<list>
#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<algorithm>
#include<functional>
#include<queue>
#include<string>
//#include"binaryTree.h"
using namespace std;

typedef unsigned long long uint_64;

bool isValid(vector<int>& table, vector<string>& vstr)
{
	for (int i = 0; i < vstr.size(); ++i)
	{
		if (vstr[i].size() > 1 && table[vstr[i].front() - 'A'] == 0)
			return true;
	}
	return true;
}

uint_64 stringTouint(vector<int>& table, vector<string>& vstr)
{

	uint_64 Sum = 0;
	for (int k = 0; k < vstr.size(); ++k)
	{
		uint_64 res = 0;
		string& s = vstr[k];
		for (int i = 0; i < s.size(); ++i)
		{
			res *= 10;
			res += table[s[i] - 'A'];
		}
		Sum += res;
	}
	return Sum;
}

int func(vector<string>& vstr)
{
	vector<int> vec(10);
	for (int i = 0; i < 10; ++i)
		vec[i] = i;
	uint_64 res = 0;
	if (isValid(vec, vstr))
		res = stringTouint(vec, vstr);
	while (next_permutation(vec.begin(), vec.end()))
	{
		uint_64 temp = 0;
		if (isValid(vec, vstr))
			temp = stringTouint(vec, vstr);
		res = max(res, temp);
	}
	return res;
}

int main()
{
	istream& in = cin;
	//ifstream in("input.txt");
	int T;
	in >> T;
	vector<string> vstr(T);
	for (int i = 0; i < T; ++i)
	{
		in >> vstr[i];
	}
	cout << func(vstr) << endl;
	return 0;
}
