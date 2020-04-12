#include<iostream>  
#include<memory.h>
using namespace std;
#include<random>
#include<vector>
#define NUM 20
int arr[NUM];
int  myrandom()
{
	int num = rand() % 17;
	for (int i = 0; i < num; i++)
	{
		int flag = 1;
		int x;
		while (1) {
			x = rand() % NUM;
			int j;
			for (j = 0; j < i; j++)
			{
				if (x == arr[j] || x == 0)
					break;
			}
			if (j == i && x != 0)  break;
		}
		arr[i] = x;
	}
	return num;
}
vector<vector<int>> xnodes;
vector<vector<int>>ynodes;
int xNum; int* xm;
int yNum; int* ym;
int* dealt;
int path(int begin)
{
	if (!xnodes[begin].size()) return 0;
	for (int i = xnodes[begin][0], j = 0; j < xnodes[begin].size(); j++)
	{
		i = xnodes[begin][j];
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
	//cin >> xNum >> yNum;
	xNum = NUM;
	yNum = NUM;
	cout << xNum << ' ' << yNum << endl;
	int flag = (xNum <= yNum);
	if (!flag)
	{
		int temp1 = xNum;
		xNum = yNum;
		yNum = temp1;
	}
	xm = new int[xNum];
	ym = new int[yNum];
	memset(xm, -1, sizeof(int) * xNum);
	memset(ym, -1, sizeof(int) * yNum);

	int result = 0;
	dealt = new int[xNum];
	vector<int> T;
	for (int i = 0; i < yNum; i++)
		xnodes.push_back(T);
	for (int i = 0; i < xNum; i++)
		ynodes.push_back(T);
	for (int i = 0; i < xNum; i++)
	{
		int num;
		//cin >> num;	
		memset(arr, -1, 100 * sizeof(int));
		num = myrandom();
		cout << num << endl;;;
		for (int j = 0; j < num; j++)
		{
			int temp;

			//cin >> temp;
			temp = arr[j];
			cout<<temp<<' ';
			if (!flag)
			{

				ynodes[i].push_back(temp - 1);
				xnodes[temp - 1].push_back(i);
				if (ym[i] == -1 && xm[temp - 1] == -1)
				{
					ym[i] = temp - 1;
					xm[temp - 1] = i;
					result++;
					xm[i] = temp - 1;
					ym[temp - 1] = i;
				}


			}
			else {
				xnodes[i].push_back(temp - 1);
				if (temp == 0)
					cout << "temp==0" << endl;
				ynodes[temp - 1].push_back(i);
				if (xm[i] == -1 && ym[temp - 1] == -1) {
					result++;
					xm[i] = temp - 1;
					ym[temp - 1] = i;
				}
			}
		}
		cout<<endl;

	}



	for (int i = 0; i < xNum; ++i) {
		if (xm[i] == -1)
		{
			memset(dealt, 0, sizeof(dealt) * xNum);
			result += path(i);
		}
	}
	cout << "result:" << result;
	getchar();
	getchar();
	getchar();
	return 1;
}