#include<iostream>
#include<cstring>
#include<algorithm>
#include<fstream>
#include<math.h>
#include<algorithm>
#include<stack>
#include<queue>
using namespace std;
ifstream fin("./MPP_edgelist.txt");
ofstream outfile("./MPP_result_network.txt");

const float inf = 99999;
const int MAXN = 5000;

struct Node
{
    int s;
    int to;
    int next;
    int capacity;
    float value;
};

//n corresponding to the the actual number of nodes in a network
int n=161;
int index;
Node node[MAXM];
int head[MAXN];
int pre[MAXN];
float dis[MAXN];
bool vis[MAXN];
int degree[MAXN];
//the result matrix, dim of matrix equals to n
float rel[161][161]={0};

void init()
{
    index = 0;
    memset(head, -1, sizeof(head));
    memset(node, 0, sizeof(node));
    memset(degree,0,sizeof(degree));
}
void addedge(int a, int b, float v, int c)
{
    node[index].to = b;
    node[index].s = a;
    node[index].value = v;
    node[index].capacity = c;
    node[index].next = head[a];
    head[a] = index++;

    node[index].to = a;
    node[index].s = b;
    node[index].value = -v;
    node[index].capacity = 0;
    node[index].next = head[b];
    head[b] = index++;
}

bool spfa(int s, int t, int nnum)
{
    memset(vis, 0, sizeof(vis));
    memset(pre, -1, sizeof(pre));
    for (int i = 0; i <= nnum; i++)
    {
        dis[i] = inf;
    }
    queue<int> que;
    que.push(s);
    dis[s] = 0;
    vis[s] = true;
    while (!que.empty())
    {
        int temp = que.front();
        que.pop();
        vis[temp] = false;
        for (int i = head[temp]; i != -1; i = node[i].next)
        {
            if (node[i].capacity)
            {
                int ne = node[i].to;
                bool result = dis[temp] + node[i].value < dis[ne];
                if (result)
                {
                    dis[ne] = dis[temp] + node[i].value;
                    pre[ne] = i;
                    if (!vis[ne])
                    {
                        vis[ne] = true;
                        que.push(ne);
                    }
                }
            }
        }
    }
    if (dis[t] == inf)
        return false;
    return true;
}

float getMincost(int s, int t, int nnum)
{
    int ans_flow = 0;
    float ans_cost = 0;
    int temp, minc;
    while (spfa(s, t, nnum))
    {
    	//cout<<s<<" * "<<t<<endl;
        temp = t;
        minc = inf;
        while (pre[temp] != -1)
        {
            minc = min(node[pre[temp]].capacity, minc);
            temp = node[pre[temp]].s;
        }
        temp = t;
        while (pre[temp] != -1)
        {
            node[pre[temp]].capacity -= minc;
            int ss = pre[temp] ^ 1;
            node[ss].capacity += minc;
            temp = node[pre[temp]].s;
        }
        ans_cost += dis[t] * minc;
    }
    return ans_cost;
}

int main()
{
    int a, b;
    int s, t;
    float result,v,de;

    for(int i=1;i<=n;i++)
    	for(int j=i+1;j<=n;j++)
    	{
			init();
		    while(fin>>a>>b>>v>>de)
		    {
		    	float temp = int(1000*v*log2(1/v));
		        addedge(a, b, temp, 1);
		        addedge(b, a, temp, 1);
		        degree[a]++;
		        degree[b]++;
		    }
		    fin.clear();
		    fin.seekg(0,ios::beg);
    		s = n + 1;
    		t = s + 1;
    		addedge(s, i, 0, degree[i]);
    		addedge(j, t, 0, degree[j]);
    		result = getMincost(s,t,t);
    		cout<<i<<":"<<j<<" "<<result<<endl;
    		rel[i-1][j-1] = result;
    		rel[j-1][i-1] = result;
    	}

    //输出
    for(int i = 0;i < n;i++)
    {
    	for(int j = 0;j < n;j++)
    	{
    		outfile<<rel[i][j]<<' ';
    	}
    	outfile<<endl;
    }

    return 0;
}
