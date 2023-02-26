#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <stack>

using Graph = std::unordered_map<int, std::unordered_set<int>>;

// bfs algorithm 
void traverse(Graph& g, int start)
{
	std::vector<bool> visited(g.size(), false);

	std::queue<int> q; // change queue to stack for dfs
	q.push(start);

	while(!q.empty())
	{
		int x = q.front();
		q.pop();

		if(!visited[x])
		{
			std::cout << x << std::endl;
			visited[x] = true;

			for(int y : g[x]) // push each non visited neighbor y of x
				if(!visited[y])
					q.push(y);
		}
	}
}

int main()
{
	Graph graph;

	graph = {
		{ 1, {2} },
		{ 2, {3, 4}},
		{ 3, {1, 4}},
		{ 4, {2}}
	};

	traverse(graph, 1);

	return 0;
}