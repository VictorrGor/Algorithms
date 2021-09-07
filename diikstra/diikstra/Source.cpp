#include <iostream>
#include <queue>
#include <deque>
#include <map>
#include <string>
#include <set>

using namespace std;

struct NodeEdge
{
	int target;
	int length;
};

int findMinCostNode(const map<int, int>* _actualDistance, const set<int>* _usedNodes)
{
	int min = INT_MAX;
	int index = -1;

	for (auto it = _actualDistance->begin(); it != _actualDistance->end(); ++it)
	{
		if ((min > it->second) && (_usedNodes->find(it->first) == _usedNodes->end()) )
		{
			min = it->second;
			index = it->first;
		}
	}
	return index;
}

int Diikstra(map<int, vector<NodeEdge>> _stateMap, int _initialPt, int _targetPt)
{
	if (_initialPt == _targetPt) return 0;

	set<int> usedNodes;
	map<int, int> actualDistance; //node_num | distance
	map<int, int> parentNode; //child_node | parent_node

	for (auto it = _stateMap.begin(); it != _stateMap.end(); ++it)
	{
		actualDistance[it->first] = INT_MAX;
	}

	for (auto it = _stateMap[_initialPt].begin(); it < _stateMap[_initialPt].end(); ++it)
	{
		actualDistance[it->target] = it->length;
		parentNode[it->target] = _initialPt;
	}
	usedNodes.insert(_initialPt);
	
	auto node = findMinCostNode(&actualDistance, &usedNodes);
	while ( node != -1)
	{
		for (auto it = _stateMap[node].begin(); it < _stateMap[node].end(); ++it)
		{
			if (actualDistance[it->target] > actualDistance[node] + it->length)
			{
				actualDistance[it->target] = actualDistance[node] + it->length;
				parentNode[it->target] = node;

			}
		}
		usedNodes.insert(node);
		node = findMinCostNode(&actualDistance, &usedNodes);
	}

	node = _targetPt;
	std::cout << node << " ";
	while (node != _initialPt)
	{
		node = parentNode[node];
		std::cout << node << " ";
	}
	std::cout << "\n";

	return actualDistance[_targetPt];
	
}


int main()
{
	map<int, vector<NodeEdge>> stateMap;
	stateMap[1] = { {2, 3}, {6, 5}, {9, 2} };
	stateMap[2] = { {3, 4}, {10, 1} };
	stateMap[3] = { {4, 5} };
	stateMap[4] = {};
	stateMap[5] = { {4,2} };
	stateMap[6] = { {5,3}, {8,1} };
	stateMap[7] = { {6, 1} };
	stateMap[8] = { {9, 1} };
	stateMap[9] = { {7, 10} };
	stateMap[10] = {};
	stateMap[11];
	std::cout << "Total distance: " << Diikstra(stateMap, 1, 4) << "\n";
}