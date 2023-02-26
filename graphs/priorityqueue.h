#include <unordered_map>
#include <set>

struct PriorityQueue
{
	PriorityQueue(){}

	void push(int node, int val)
	{
		byNodes.insert({node, val});
		byWeights.insert({val, node});
	}

	void update(int node, int newVal)
	{
		int oldVal = byNodes[node];
		byWeights.erase({oldVal, node});
		byWeights.insert({newVal, node});
		byNodes[node] = newVal;
	}

	int top()
	{
		int topNode = byWeights.begin()->second; 
		byNodes.erase(topNode);
		byWeights.erase(byWeights.begin());
		return topNode;
	}

	bool empty()
	{
		return byNodes.size() == 0;
	}

	std::unordered_map<int,int> byNodes; // <node,weight>
	std::multiset<std::pair<int,int>> byWeights; // <weight,node>
};