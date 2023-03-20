#include <vector>
#include <unordered_map>
#include <iostream>

#define INF 99999

using WeightedGraph = std::unordered_map<int,std::unordered_map<int,int>>;

using Matrix = std::vector<std::vector<int>>;

Matrix floydWarshall(WeightedGraph& g)
{
	int n = g.size();

	Matrix d(n , std::vector<int>(n, INF));

	for(int u = 0; u < n; u++) {
		for(int v = 0; v < n; v++) {
			if(u == v)
				d[u][v] = 0;
			else if(g[u].find(v) != g[u].end())
				d[u][v] = g[u][v]; // g[u][v] is the edge weight w (u)---w--->(v)
		}
	}

	for(int k = 0; k < n; k++)
		for(int u = 0; u < n; u++)
			for(int v = 0; v < n; v++)
				d[u][v] = std::min(d[u][v] , d[u][k] + d[k][v]);
	return d;
}

enum Nodes
{
	A,B,C,D,E
};

int main()
{

	WeightedGraph g = 
	{
		{A, { {B,1}, {C,1}, {D,6}, {E, 8} } },
		{B, { {D,3} } },
		{C, { {D,2} } },
		{D, { {E,3} } },
		{E, { 		} }
	};

    Matrix ans = floydWarshall(g);
    for(int i = 0; i < ans.size(); i++)
        for(int j = 0; j < ans.size(); j++)
            std::cout << ans[i][j] << (j == g.size() - 1 ? '\n' : '\t');

    return 0;
}