# Readme

## Network.cpp

汇集了经典网络模型的生成函数，网络基本属性的计算函数。

## 使用例

生成一个WS小世界网络

```c++
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdio.h>
#include "network.cpp"
using namespace std;
int main(){
vector<vector<int> > WSGraph;
int n=10;
int k=4;
double p=0.2;
WSGraph=Init(n);
WSGraph=CreateNCCNetwork(WSGraph,n,k);
WSGraph=CreateWSNetwork(WSGraph,n,k,p);
Csa_printAdjList(WSGraph);
return 0;
}
```

结果：

最近邻耦合网络

<img src=".\img\1.png" alt="1" style="zoom:50%;" />

WS小世界网络

<img src=".\img\2.png" alt="2" style="zoom:50%;" />

