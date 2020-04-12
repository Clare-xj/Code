#include<iostream>  
#include<memory.h>
using namespace std;
#include<vector>
vector<vector<int>> xnodes;
vector<vector<int>>ynodes;
int xNum; int* xm;
int yNum; int* ym;
int* dealt;
int path(int begin)
{
	for (int i = 0; i < ynodes.size(); i++)
	{
		if (!dealt[i]) {
			dealt[i] = 1;
			if (ym[i] == -1 || path(ym[i]))
			{
				xm[begin] = i;
				ym[i] = begin;
				return 1;
			}
		}
	}
	return 0;
}


int main() {

	cin >> xNum >> yNum;
	int temp = xNum < yNum;
	if (!temp)
	{
		xm = new int[yNum];
		ym = new int[xNum];
		dealt = new int[yNum];
		vector<int> T;
		for (int i = 0; i < yNum; i++)
			xnodes.push_back(T);
		for (int i = 0; i < xNum; i++)
			ynodes.push_back(T);
		for (int i = 0; i < xNum; i++)
		{
			int num;
			cin >> num;
			for (int j = 0; j < num; j++)
			{
				int temp;
				cin >> temp;
				ynodes[i].push_back(temp - 1);
				xnodes[temp - 1].push_back(i);
			}

		}
		int temp1 = xNum;
		xNum = yNum;
		yNum = temp1;
	}
	else {
		xm = new int[xNum];
		ym = new int[yNum];
		dealt = new int[xNum];
		vector<int> T;
		for (int i = 0; i < xNum; i++)
			xnodes.push_back(T);
		for (int i = 0; i < yNum; i++)
			ynodes.push_back(T);
		for (int i = 0; i < xNum; i++)
		{
			int num;
			cin >> num;
			for (int j = 0; j < num; j++)
			{
				int temp;
				cin >> temp;
				xnodes[i].push_back(temp - 1);
				ynodes[temp - 1].push_back(i);
			}

		}
	}
	memset(xm, -1, sizeof(xm)*xNum);
	memset(ym, -1, sizeof(ym)*yNum);
	int num = 0;
	for (int i = 0; i < xNum; ++i) {
		if (xm[i] == -1)
		{
			memset(dealt, 0, sizeof(dealt)*xNum);
			num += path(i);
		}
	}
	cout << num;
	return 1;
}