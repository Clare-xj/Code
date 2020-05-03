#include<iostream>
#include<memory.h>
#include<vector>
#include<algorithm>
using namespace std;
vector<vector<int>> G;
#define white 0
#define gray 1
#define black -1
vector<int> points;

struct edge
{
	int a;
	int b;
	edge(int x = 0, int y = 0)
	{
		a = x;
		b = y;
	}
};
int compare(edge a, edge b)
{
	return a.a < b.a;
}
vector<int> root;
vector<edge> edges;
vector<edge> root1;
int num;
int* discoverTime;
int* finishTime;
int* parent;
int* back;
int mytime;
int dfs(int*, int,int&);
int br_dfs(int*, int);
int main(){
	cin >> num;
	int* color;
	mytime = 0;
	color = new int[num];
	discoverTime = new int[num];
	finishTime = new int[num];
	parent = new int[num];
	back = new int[num];
	memset(color, 0, sizeof(int) * num);
	memset(discoverTime, 0, sizeof(int) * num);
	memset(finishTime, 0, sizeof(int) * num);
	memset(parent, -1, sizeof(int) * num);
	memset(back, 0, sizeof(int) * num);
	vector<int>T;
	for (int i = 0; i < num; i++)
	{
		G.push_back(T);
	}
	int x, y;
	while (cin >> x >> y)
	{
		G[x].push_back(y);
		G[y].push_back(x);
	}
	int count = 0;
	dfs(color, 0,count);
	if (root.size() != 1) {
		points.push_back(0);
	}
	sort(points.begin(), points.end());
	

	mytime=0;
	memset(color, 0, sizeof(int) * num);
	memset(discoverTime, 0, sizeof(int) * num);
	memset(finishTime, 0, sizeof(int) * num);
	memset(parent, -1, sizeof(int) * num);
	memset(back, 0, sizeof(int) * num);
	br_dfs(color, 0);
	sort(edges.begin(), edges.end(), compare);
	cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
	for (unsigned int i = 0; i < points.size(); i++)
	{
		cout << points[i] << endl;
	}
	for (unsigned int i = 0; i < edges.size(); i++)
		cout << edges[i].a << ' ' << edges[i].b << endl;
	return 0;
}

int br_dfs(int* color, int v)
{
	int w;
	int ans;
	color[v] = gray;
	mytime += 1;
	discoverTime[v] = mytime;
	back[v] = discoverTime[v];
	//<Preorder processing of vertex v>S
	vector<int> remAdj = G[v];
	unsigned int i = 0;
	while (remAdj.size()!=1&&remAdj.size() != i)
	{
		w = remAdj[i];
		if (color[w] == white)
			//  <Exploratory processing for tree edge vw>
		{
			
			parent[w] = v;
			back[w] = br_dfs(color, w);
			if (!v&& back[w] == discoverTime[v])
				root1.push_back(edge(0, w));
			if (back[w] >discoverTime[v])
			{
				int min = w < v ? w : v;
				int max = w > v ? w : v;
				edge x(min, max);
				edges.push_back(x);
			}
				
			back[v] = back[v] < back[w] ? back[v] : back[w];
		}
		//  < Backtrack processing for tree edge vw, Susing wAns>
		else
		{
			if (color[w] == gray && parent[v] != w && parent[w] != v)
				back[v] = back[v] < discoverTime[w] ? back[v] : discoverTime[w];
		}
		//  <Checking for nontreeedge vw>
		w = remAdj[i++];
	}
	//<Postorderprocessing of vertex v, including final computation of ans>
	color[v] = black;
	mytime++;
	finishTime[v] = mytime;
	return back[v];
}
int dfs(int* color, int v,int& count) {
	int w;
	int ans;
	color[v] = gray;
	mytime += 1;
	discoverTime[v] = mytime;
	back[v] = discoverTime[v];
	//<Preorder processing of vertex v>
	vector<int> remAdj = G[v];
	int i = 0;
	while (remAdj.size()!=1&&remAdj.size() != i)
	{
		w = remAdj[i];
		if (color[w] == white)
			//  <Exploratory processing for tree edge vw>
		{
			if (!v) count++;
			parent[w] = v;
			back[w] = dfs(color, w,count);
			if (back[w] >= discoverTime[v])
			{
				if (v)points.push_back(v);
				else root.push_back(v);
			}
			back[v] = back[v] < back[w] ? back[v] : back[w];
		}
		//  < Backtrack processing for tree edge vw, Susing wAns>
		else
		{
			if (color[w] == gray && parent[v] != w && parent[w] != v)
				back[v] = back[v] < discoverTime[w] ? back[v] : discoverTime[w];
		}
		//  <Checking for nontreeedge vw>
		w = remAdj[i++];
	}
		//<Postorderprocessing of vertex v, including final computation of ans>
		color[v] = black;
		mytime++;
		finishTime[v] = mytime;
		return back[v];
	//  return ans 
}
