#include <iostream>
#include <vector>

struct UnionFind // disjoint sets
{
	UnionFind(int n) : sz(n)
	{
		r.resize(n, 0); // create n disjoint sets
		for(int i = 0; i < n; i++)
			p.push_back(i);
	}

	int find(int x) // return the leader of x (that is, the root of the set where x belongs)
	{
		return x != p[x] ? find(p[x]) : x;
	}

	void join(int x, int y) // union the set where x belongs with the set where y belongs
	{
		x = find(x), y = find(y); // x and y have been changed by their leaders

		if(x == y) // x and y point to the same leader (to the same set)
			return;
		sz--;

		if(r[x] > r[y]) {
			p[y] = x;
		} else {
			p[x] = y;
			if(r[x] == r[y])
				r[y]++;
		}
	}

	int count()
	{
		return sz;
	}

	int sz; // number of disjoint sets
	
	std::vector<int> p; // parent vector 
	std::vector<int> r; // rank vector
};

// Check number of connected components in a graph of n nodes
int connComponents(int n, std::vector<std::pair<int,int>> edges)
{
	UnionFind s(n);

	for(auto [u,v] : edges)
		s.join(u,v);
	return s.count();
}

bool hasCycle(int n, std::vector<std::pair<int,int>> edges)
{
	UnionFind s(n);

	for(auto [u,v] : edges)
	{
		if(s.find(u) == s.find(v))
			return true;
		s.join(u, v);
	}

	return false;
}

bool isTree(int n, std::vector<std::pair<int,int>> edges)
{
	return !hasCycle(n,edges) && connComponents(n,edges) == 1;
}

/*int main()
{
	UnionFind mySets(5);

	mySets.join(0,1);
	mySets.join(2,3);
	mySets.join(0,2);
	mySets.join(3,4);

	return 0;
}*/