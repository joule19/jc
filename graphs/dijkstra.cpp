#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <iostream>
#include <climits>

#include "priorityqueue.h"

using Graph = std::unordered_map<int,std::unordered_set<int>>;
using Weights = std::unordered_map<int,std::unordered_map<int,int>>;

std::vector<int> dijkstra(Graph& g, Weights& w, int start)
{
	std::vector<int> d(g.size(), INT_MAX);

	PriorityQueue pq;
	for(int i = 0; i < g.size(); i++)
		pq.push(i, d[i]);

	d[start] = 0;
	pq.update(start, 0);

	while(!pq.empty())
	{
		int x = pq.top(); // take and remove the next node in the priority queue
		for(int y : g[x])
			if(d[x] + w[x][y] < d[y])
				d[y] = d[x] + w[x][y], pq.update(y, d[y]);
	}
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

	std::vector<int> distances = dijkstra(g, w, 0);
	for(int d : distances)
		std::cout << d << std::endl;

	return 0;
}