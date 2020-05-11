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
vector< vector<int>> G;
vector<vector<int>>GT;
vector<int> header;
void DFSFindB(int v);
struct Node{
    vector<int> arr;
    vector<int> decend;
    int sum;
    Node()
    {
        sum=0;
    }
};
vector<Node>compressedG;
void DFS(int);
void dfsTsweep(int);
void DFSFindB(int);
//int MAX=0;
//int TAG=-1;
int main() {
    vector<string>strs;
    string str;
    while(getline(cin,str))
    {
        strs.push_back(str);
    }
    int num=strs.size();
    color=new int[num];
    scc=new int[num];
    memset(color, 0, sizeof(int) * num);

    G.resize(num);
    GT.resize(num);
    compressedG.resize(num);
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
    for(int i=0;i<header.size();i++)
    {
        int sum=0;
        vector<int> node=compressedG[i].decend;
        for(int j=0;j<node.size();j++)
        {
            sum+=compressedG[j].arr.size();
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
            dfsT(v,node,v);
            node.decend.push_back(v);
            node.sum=node.arr.size();
            compressedG[v]=node;
        }
    }
}

void DFSFindB(int v) {

    vector<int> remAdj =G[v];
    int i = 0;
    color[v]=gray;
    while (remAdj.size() != i)
    {
        int w = remAdj[i];
            //  <Exploratory processing for tree edge vw>
        {
            if(color[w]==gray)  break;
            else if(scc[w]==scc[v]&&color[w]==white) 
                DFSFindB(w);
            else if(scc[w]==scc[v]&&color[w]==black)
                break;
            else 
            {
                if(color[w]==white)
                    DFSFindB(w);
           
                vector<int> dv=compressedG[scc[v]].decend;
                vector<int> dw=compressedG[scc[w]].decend;
                for(int i=0;i<dw.size();i++)
                {
                    vector<int>::iterator it=find(dv.begin(),dv.end(),dw[i]);
                    if(it==dv.end())
                    {
                        compressedG[scc[v]].decend.push_back(dw[i]);
                        compressedG[scc[v]].sum+=compressedG[dw[i]].sum;
                    }
                }
            }
            
        }
        w = remAdj[i++];
    }
    //<Postorderprocessing of vertex v, including final computation of ans>
    color[v] = black;
    //  return ans
}