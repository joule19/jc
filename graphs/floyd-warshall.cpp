
#define INF 9999

using Graph = std::unordered_map<int,std::unordered_set<int>>;
using Weights = std::unordered_map<int,std::unordered_map<int,int>>;

using Matrix = std::vector<std::vector<int>>;

Matrix floydWarshall(Graph g, Weights w)
{
	int n = g.size();

	Matrix d(n , std::vector<int>(n, INF));

	for(int u = 0; u < n; u++) {
		for(int v = 0; v < n; v++) {
			if(u == v)
				d[u][v] = 0;
			else if(g[u].find(v) != g[u].end())
				d[u][v] = w[u][v];
		}
	}

	for(int k = 0; k < n; k++)
		for(int u = 0; u < n; u++)
			for(int v = 0; v < n; v++)
				d[u][v] = std::min(d[u][v] , d[u][k] + d[k][v]);
	return d;
}

int main()
{
	Graph g = 
	{
		{0, {1,2,3,4}},
		{1, {3}},
		{2, {3}},
		{3, {4}},
		{4, {}}
	};

	Weights w = 
	{
		{0, { {1,1}, {2,1}, {3,6}, {4, 8} } },
		{1, { {3,3} } },
		{2, { {3,2} } },
		{3, { {4,3} } }
	};

	Matrix d = floydWarshall(g, w);
	for(int i = 0; i < d.size(); i++)
		

	for(int d : distances)
		std::cout << d << std::endl;

	return 0;
}

nt main()
{
    Graph g = 
  {
    {0, {1,2,3,4}},
    {1, {3}},
    {2, {3}},
    {3, {4}},
    {4, {}}
  };

  Weights w = 
  {
    {0, { {1,1}, {2,1}, {3,6}, {4, 8} } },
    {1, { {3,3} } },
    {2, { {3,2} } },
    {3, { {4,3} } }
  };

  //std::vector<int> distances = dijkstra(g, w, 0);
//   for(int d : distances)
//     std::cout << d << std::endl
    vector<vector<int>> ans = floyd_warshall(g, w);
    for(int i = 0; i < g.size(); i++)
    {
        for(int j = 0; j < g.size(); j++)
        {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}