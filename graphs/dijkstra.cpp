#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <iostream>
#include <climits>

#include "priorityqueue.h"

using WeightedGraph = std::unordered_map<int,std::unordered_map<int,int>>;

std::vector<int> dijkstra(WeightedGraph& g, int start)
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
		for(auto [y,w] : g[x]) // visiting each neighbor y of x with edge weight w: (x)---w--->(y)
			if(d[x] + w < d[y])
				d[y] = d[x] + w, pq.update(y, d[y]);
	}
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

	std::vector<int> distances = dijkstra(g, 0);
	for(int d : distances)
		std::cout << d << std::endl;

	return 0;
}