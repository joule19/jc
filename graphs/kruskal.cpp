#include <algorithm>
#include <set>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <tuple>

#include "unionfind.h"

using Graph = std::unordered_map<int,std::unordered_set<int>>;
using Weights = std::unordered_map<int,std::unordered_map<int,int>>;

// Returns edges sorted
std::set<std::tuple<int,int,int>> sortEdges(Graph& g, Weights& w)
{
	std::set<std::tuple<int,int,int>> edges;

	for(auto it = g.begin(); it != g.end(); it++)
	{
		int x = it->first;
		for(int y : g[x])
			edges.insert( { w[x][y] , x , y } );
	}

	return edges;
}

// Returns MST
std::vector<std::pair<int,int>> kruskal(Graph& g, Weights& w)
{
	std::set<std::tuple<int,int,int>> edges = sortEdges(g, w);

	std::vector<std::pair<int,int>> mst;

	UnionFind ss(g.size());

	for(auto [w,u,v] : edges)
		if(ss.find(u) != ss.find(v))
			mst.push_back({u,v}), ss.join(u,v);

	return mst;
}

enum Nodes{A,B,C,D,E,F,G,H,I};

int main()
{
	Graph g =
	{  
		{A, {B,H} },
		{B, {A,H,C} },
		{C, {B,I,D,F}},
		{D, {C,F,E}},
		{E, {D,F}},
		{F, {C,D,E,G}},
		{G, {F,I,H}},
		{H, {A,B,I,G}},
		{I, {C,H,G}}
	};

	Weights w = 
	{
		{A, {{B,4}, {H,8}} },
		{B, {{A,4}, {H,11}, {C,8}} },
		{C, {{B,8},{I,2},{D,7},{F,4}} },
		{D, {{C,7},{F,14},{E,9}} },
		{E, {{D,9},{F,10}} },
		{F, {{C,4},{D,14},{E,10},{G,2}} },
		{G, {{F,2},{I,6},{H,1}} },
		{H, {{A,8}, {B,11}, {I,7}, {G,1}} },
		{I, {{C,2}, {H,7}, {G,6}} }
	};

	std::vector<std::pair<int,int>> mst = kruskal(g, w);

	int sum = 0;

	for(auto [u,v] : mst)
		sum += w[u][v], std::cout << char(u + 'A')  << "," << char(v + 'A') << " " << w[u][v] << std::endl;

	std::cout << "total: " << sum << std::endl;

	return 0;
}

