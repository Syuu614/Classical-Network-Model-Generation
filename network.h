#define __NETWORK_H__


#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include<time.h>
#include <stdio.h>
using namespace std;
#define ERROR 0
#define OK 1
//邻接表的初始化
vector< vector<int> > Init(int n){
    vector< vector<int> > Adj_List(n);
    return Adj_List;
}
//邻接表的撤销
vector< vector<int> > Destroy(vector<vector<int> > Adj_List){
    Adj_List.clear();
    return Adj_List;
}
//搜索边(u,v)
int Exist(vector<vector<int> > Adj_List,int n,int u, int v){//n是邻接表的结点数
    if (u<0||v<0||u>n-1||v>n-1||u==v) {
      return ERROR;
    }
    auto p1=find(Adj_List[u].begin(),Adj_List[u].end(),v);
    auto p2=find(Adj_List[v].begin(),Adj_List[v].end(),u);
    if (p1==Adj_List[u].end()||p2==Adj_List[v].end()) {
      return ERROR;
    }else {
      return OK;
    }
}
//插入边(u,v) 
vector< vector<int> > Insert(vector< vector<int> > Adj_List,int n,int u, int v){//n是邻接表的结点数
    if (u<0||v<0||u>n-1||v>n-1||u==v) {
      return Adj_List;
    }else {
      if (Exist(Adj_List,n,u,v)==0) {
      Adj_List[u].push_back(v);
      Adj_List[v].push_back(u);
      return Adj_List;
      }      
    }
    return Adj_List;
}
//删除边(u,v) 
vector< vector<int> > Remove(vector< vector<int> > Adj_List, int n, int u, int v){
    if (u<0||v<0||u>n-1||v>n-1||u==v) {
      return Adj_List;
    }
    auto p1=find(Adj_List[u].begin(),Adj_List[u].end(),v);
    auto p2=find(Adj_List[v].begin(),Adj_List[v].end(),u);
    if (p1==Adj_List[u].end()||p2==Adj_List[v].end()) {
      return Adj_List;
    }else {
      Adj_List[u].erase(p1);
      Adj_List[v].erase(p2);
      return Adj_List;
    }    
}
//输出邻接表(https://csacademy.com/app/graph_editor/的格式)
void printAdjList(vector< vector<int> > Adj_List){
    int i,j;
    for(i=0;i<Adj_List.size();i++){
      cout<<i<<"\n";
    }
    for(i=0;i<Adj_List.size();i++){
      for(j=0;j<Adj_List[i].size();j++){
        cout<<i<<" "<<Adj_List[i][j]<<"\n";
      }
      //cout<<"\n";
    }
}
//输出邻接表（普通格式）
void Raw_printAdjList(vector< vector<int> > Adj_List){
    int i,j;
    for(i=0;i<Adj_List.size();i++){
      for(j=0;j<Adj_List[i].size();j++){
        cout<<Adj_List[i][j]<<" ";
      }
      cout<<"\n";
    }
}
//计算各个点的聚类系数
vector<double> Cal_Ck (vector<vector<int> > Adj_List,int n){//n是节点数
  int i,j,k;//循环变量
  int p,q;//临时变量
  int e=0;//Ei
  vector<double> C(n);//存放每个节点的聚类系数
  vector<int> :: iterator p1;
  for ( i = 0; i < n; i++)
  {
    for ( j = 0; j < Adj_List[i].size(); j++)
    {
      p=Adj_List[i][j];
      for ( k = j+1; k < Adj_List[i].size(); k++)
      {
        q=Adj_List[i][k];
        p1=find(Adj_List[p].begin(),Adj_List[p].end(),q);
        if (p1!=Adj_List[p].end())
        {
          e++;
        }
        
      }
      
    }
    C[i]=(double)e*2 / ( n*(n-1) );
    e=0;
  }
  return C;
}
//统计最大度
int MaxDegree (vector<vector<int> > Adj_List,int n){
  int i;//循环变量
  int maxDegree=Adj_List[0].size();//存储最大度
  for ( i = 0; i < n; i++)
  {
    if (Adj_List[i].size()>=maxDegree)
    {
      maxDegree = Adj_List[i].size();
    }
    
  }
  return maxDegree;
}
//统计各个节点的度
vector<int> CountDegree (vector<vector<int> > Adj_List,int n ){
  int i;//循环变量
  int maxDegree;//最大度
  maxDegree=MaxDegree(Adj_List,n);
  vector<int> Degree(maxDegree+1);//存储节点的度，0~k有k+1个数
  for ( i = 0; i < maxDegree; i++)
  {
    Degree[i]=0;
  }
  for ( i = 0; i < n; i++)
  {
    Degree[Adj_List[i].size()]++;
  }
  return Degree;
  
}
//度分布
vector<double> DegreeDistribution(vector<int> Degree, int n){
  int i;
  vector<double> DegreeD(Degree.size());
  for (i=0; i< Degree.size(); i++) {
    DegreeD[i]=(double) Degree[i] / n;
  }
  return DegreeD;
}
//累积度分布
vector<double> CumulaDDistribution(vector<int> Degree, int n){
  int i;
  vector<double> CDegree(Degree.size());
  for (i=0; i<Degree.size()-1; i++) {
    Degree[i+1]+=Degree[i];
  }
  for (i=0; i<Degree.size()-1; i++) {
   CDegree[i] = (double) (n-Degree[i-1]) / n;
  }
  return CDegree;
}
/*DFS*/
//生成ER图
vector<vector<int> > CreateERGraph(vector<vector<int> > Adj_List,int n,int k){//k是平均度
  int i,j;//循环变量
  double r;//生成的随机数
  double p;//连边概率
  p = (double)k / (n-1);
  srand((unsigned)time(NULL));
  for ( i = 0; i < n; i++)
  {
    
    for ( j = i; j < n; j++)
    {
        r = (double)rand()/ RAND_MAX;
        if (r<p)
        {
            Adj_List= Insert(Adj_List,n,i,j);
          
        }
    }
  }
  return Adj_List;
}
//生成最近邻耦合网络
vector< vector<int> > CreateNCCNetwork(vector< vector<int> > Adj_List,int n,int k){
  int i,j;
  for ( i = 0; i < n; i++)
  {
    for ( j = 1; j <= k/2; j++)
    {
      if (i+j<n)
      {
        if (find( Adj_List[i].begin(), Adj_List[i].end(), i+j) ==Adj_List[i].end())
        {
          Adj_List[i].push_back(i+j);
          Adj_List[i+j].push_back(i);
        }
        
      }else{
        if (find(Adj_List[i].begin(), Adj_List[i].end(), i+j-n)==Adj_List[i].end())
        {
          Adj_List[i].push_back(i+j-n);
          Adj_List[i+j-n].push_back(i);
        }
        
      }
      
    }

    for (j=-1; j>= -k/2; j--)
    {
      if(i+j>=0)
      {
        if (find( Adj_List[i].begin(), Adj_List[i].end(), i+j) ==Adj_List[i].end())
        {
          Adj_List[i].push_back(i+j);
          Adj_List[i+j].push_back(i);
        }
        
      }else{
        if (find(Adj_List[i].begin(), Adj_List[i].end(), i+j+n)==Adj_List[i].end())
        {
          Adj_List[i].push_back(i+j+n);
          Adj_List[i+j+n].push_back(i);
        }

      }
    }
    
    
  }
  
  return Adj_List;
}
//生成WS小世界网络（随机重连）
vector< vector<int> > CreateWSNetwork(vector< vector<int> > Adj_List,int n, int k,double p){
    srand((unsigned)time(NULL));   
    int i,j;//循环变量
    double R4Disconnect;//生成判断断边的概率
    double R4ReserveNood;//生成选择保留点的概率（小于0.5保留i，大于0.5保留j）
    int ChooseNode;//生成连接的结点号
    vector<vector<int> > WSGraph;
    WSGraph=Init(n);
        for (i=0; i< n; i++) {
      for (j=0; j<k; j++) {//j是NCCNetwork的指针！！！！！ NCCNetwork[i][j]才是j所指的值！
      if(Adj_List[i][j]>i)
        {
        R4Disconnect=(double)rand()/RAND_MAX;
        if (R4Disconnect<p) {
          R4ReserveNood=(double)rand()/RAND_MAX;
          if (R4ReserveNood<=0.5) {//保留i
            do {
            ChooseNode=rand() % n;
            }while (ChooseNode==i||ChooseNode==Adj_List[i][j]||find(WSGraph[i].begin(),WSGraph[i].end(),ChooseNode)!=WSGraph[i].end());//不允许出现自环,不允许连原来的边,不允许重边
            WSGraph=Insert(WSGraph, n, i, ChooseNode);
          }else {//保留j
            do {
            ChooseNode=rand() % n;
            }while (ChooseNode==i||ChooseNode==Adj_List[i][j]||find(WSGraph[i].begin(),WSGraph[i].end(),ChooseNode)!=WSGraph[i].end());//不允许出现自环,不允许连原来的边,不允许重边
            WSGraph=Insert(WSGraph, n, Adj_List[i][j], ChooseNode);           
          }
        }else {
          WSGraph=Insert(WSGraph, n, i, Adj_List[i][j]);
        }
       }
      }
    }
    return WSGraph;
}
//生成N个节点的完全图
vector< vector<int> > CreateCGraph(vector< vector<int> > Adj_List,int n){
  int i,j;
  for (i=0; i<n; i++) {
    for (j=0; j<n; j++) {
      Adj_List=Insert(Adj_List, n, i, j);
    }
  }
  return Adj_List;
}
//生成BA无标度网络（优先连接）
vector< vector<int> > CreateBANetwork(vector< vector<int> > Adj_List, int n,int m0, int t, int m){//m0：完全图的节点数，t：共增加t个节点，m：每次增加m条边
srand((unsigned)time(NULL));   
  int i,j,k;//循环变量
  int mCount=0;//增加的边数、
  int e=0;//总度数
  double r;//判断是否连边
  vector<double> pi(m0+t);//存储每个旧节点的连边概率
  Adj_List=CreateCGraph(Adj_List, m0);//前m0个顶点生成完全图
  for (i=m0; i<m0+t; i++) {
    for (j=0; j<i; j++) {//计算总度数
      e+=Adj_List[j].size();
    }
    for (j=0; j<i; j++) {//计算已有节点的连边概率
      pi[j]=(double)Adj_List[j].size() / e;
    }
    for (j=0; j<i-1; j++) {//生成轮盘
      pi[j+1]+=pi[j];
    }
    r=(double)rand() / RAND_MAX;
    for (j=0; j<i&&mCount<m; j++) {
      
      if (r<pi[j]) {//如果要和i连接（轮盘第i个区间）
        if (Exist(Adj_List,n,i,j)==0) {//如果ij之前没边，就增加一条边
          Adj_List=Insert(Adj_List, n, i, j);
          j=-1;
          mCount++;
          r=(double)rand() / RAND_MAX;
        }else {//如果已经有边了，就换一个不同的随机数，换到没连过的节点为止
          do {
            r=(double)rand() / RAND_MAX;
            for (k=0; k<i; k++) {
              if (r<pi[k]) {
              break;
              }
            }
          }while (Exist(Adj_List, n, i, k)==1);
          j=-1;//再重新从第一个区间（0号区间，-1是因为for循环最后要加1，这里-1+1=0）开始判定。
        }
      }
    }
    mCount=0;
    e=0;
  }
  return Adj_List;
}