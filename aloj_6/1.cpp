#include <iostream>
#include<sstream>
#include<string>
#include<stack>
#include<vector>
#include<memory.h>
#include<algorithm>
using namespace  std;

#define white 0
#define gray 1
#define black -1
int* color;
int *scc;
stack<int>stk;
vector<int> pk;
vector< vector<int>> G;
vector<vector<int>>GT;
vector<int> header;
void DFSFindB(int v);
bool * rela;
struct son
{
    int leader;
    int impact;
    son(int lea,int imp)
    {
        leader=lea;
        impact =imp;
    }
};
struct Node{
    int leader;
    int num;
    vector<int> arr;
    vector<int> decend;
};
vector<Node>compressedG;
void DFS(int);
void dfsTsweep(int);
void DFSFindB(int);


int main() {
    vector<string>strs;
    string str;
    while(getline(cin,str))
    {
        strs.push_back(str);
    }
    pk.push_back(-1);
    int num=strs.size();
    color=new int[num];
    scc=new int[num];
    rela=new bool[num];
    memset(color, 0, sizeof(int) * num);
    memset(rela, 0, sizeof(bool) * num);

    G.resize(strs.size());
    GT.resize(strs.size());
    compressedG.resize(strs.size());
    for(int i=0;i<strs.size();i++){
        std::stringstream ss;
        ss<<strs[i];
        int num;
        while(ss>>num)
        {
            G[i].push_back(num);
            GT[num].push_back(i);
        }
    }
    for(int i=0;i<G.size();i++)
    {
        if(color[i]==white)
        {
            DFS(i);
            rela[i]=0;
        }    
        
    }
    memset(scc,-1,sizeof(int)*num);
    memset(color, 0, sizeof(int) * num);

   dfsTsweep(0);
    memset(color, 0, sizeof(int) * num);

    for(int i=0;i<header.size();i++)
    {
        if(color[i]==white)
            DFSFindB(header[i]);
    }
   
    int max=0;
    int tag=-1;
    for(int i=0;i<compressedG.size();i++)
    {
        int sum=0;
        vector<int> node=compressedG[i].decend;
        for(int j=0;j<node.size();j++)
        {
            sum+=compressedG[j].num;
        }
        if(sum>max)
        { max=sum;
            tag=i;
        }
    }
    cout<<"I have read the rules about plagiarism punishment"<<endl;
    cout<<max-1<<endl;
    Node node=compressedG[tag];
    
    sort(node.arr.begin(),node.arr.end());
    for(int i=0;i<node.arr.size();i++)
    {
      cout<<node.arr[i]<<' ';
    }
    return 0;
}

void DFS(int v) {

    vector<int> remAdj = G[v];
    int i = 0;
    color[v]=gray;
    while (remAdj.size() != i)
    {
        int w = remAdj[i];
        if (color[w] == white)
            //  <Exploratory processing for tree edge vw>
        {
            DFS(w);
        }
        w = remAdj[i++];
    }
    //<Postorderprocessing of vertex v, including final computation of ans>
    color[v] = black;
    stk.push(v);
   
    //  return ans
}
void dfsT(int v,Node& node,int leader )
{
    scc[v]=leader;
    vector<int> remAdj = GT[v];
    int i = 0;
    color[v]=gray;
    while (remAdj.size() != i)
    {
        int w = remAdj[i];
        if (color[w] == white)
            //  <Exploratory processing for tree edge vw>
        {
            dfsT(w,node,leader);
        }
        w = remAdj[i++];
    }
    //<Postorderprocessing of vertex v, including final computation of ans>
    color[v] = black;
    node.num++;
    node.arr.push_back(v);
    //  return ans
}
void dfsTsweep(int tmp)
{
    while(!stk.empty())
    {
        int v=stk.top();
        stk.pop();
        if(color[v]==white)
        {
            header.push_back(v);
            Node node;
            node.num=0;
            node.leader=v;
            dfsT(v,node,v);
            node.decend.push_back(v);
            compressedG[v]=node;
        }
    }
}

void DFSFindB(int v) {

    vector<int> remAdj = G[v];
    int i = 0;
    color[v]=gray;
    while (remAdj.size() != i)
    {
        int w = remAdj[i];
            //  <Exploratory processing for tree edge vw>
        {
            if(color[w]==gray)  break;
            DFSFindB(w);
            
            vector<int> dv=compressedG[v].decend;
            vector<int> dw=compressedG[w].decend;
            for(int i=0;i<dw.size();i++)
            {
                bool flag=1;
                vector<int>::iterator it=find(dv.begin(),dv.end(),dw[i]);
                if(it==dv.end())
                {
                    compressedG[v].decend.push_back(dw[i]);
                }
            }
            
        }
        w = remAdj[i++];
    }
    //<Postorderprocessing of vertex v, including final computation of ans>
    color[v] = black;
    //  return ans
}