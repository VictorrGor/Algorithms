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

struct QueueNode
{
	int actualNode;
	int totalLen;
};

int BFS(map<int, vector<NodeEdge>> _stateMap, int _initialNode, int _endNode)
{
	if (_initialNode == _endNode) return 0;

	set<int> usedNodes;
	queue<QueueNode> nodesQueue;
	for (auto it = _stateMap[_initialNode].begin(); it < _stateMap[_initialNode].end(); ++it)
	{
		nodesQueue.push({ it->target,  it->length });
		usedNodes.insert(it->target);
	}


	while (!nodesQueue.empty())
	{
		auto node = nodesQueue.front();
		if (node.actualNode != _endNode)
		{
			for (auto it = _stateMap[node.actualNode].begin(); it < _stateMap[node.actualNode].end(); ++it)
			{
				auto searchRes = usedNodes.find(it->target);
				if (searchRes == usedNodes.end())
				{
					usedNodes.insert(it->target);
					nodesQueue.push({ it->target,  node.totalLen + it->length });
				}
			}
		}
		else
		{
			return node.totalLen;
		}
		nodesQueue.pop();
	}

	return -1;
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
	stateMap[9] = { {7, 1} };
	stateMap[10] = {};
	stateMap[11];

	auto res = BFS(stateMap, 1, 1);
	if (res >= 0)
	{
		std::cout << "Total Length is: " << res << "\n";
	}
	else
	{
		std::cout << "No way to this node!\n";
	}
	return 0;
}