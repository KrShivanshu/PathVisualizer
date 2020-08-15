#include "ASTAR.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <cmath>
ASTAR::ASTAR(shared_ptr<Content>&content):_content(content) {

}

ASTAR::~ASTAR() {

}
void ASTAR::Init()
{
    nodes=new Node[COL*ROW];

    for (int x = 0; x < COL; x++)
            for (int y = 0; y < ROW; y++)
			{
				nodes[y * COL + x].x = x;
				nodes[y * COL + x].y = y;
				nodes[y * COL + x].bObstacle = false;
				nodes[y * COL + x].parent = nullptr;
				nodes[y * COL + x].bVisited = false;
            }

    for (int x = 0; x < COL; x++)
			for (int y = 0; y < ROW; y++)
			{
				if (y > 0)
					nodes[y*COL + x].vecNeighbours.push_back(&nodes[(y - 1) * COL + (x + 0)]);
				if (y < ROW - 1)
					nodes[y*COL + x].vecNeighbours.push_back(&nodes[(y + 1) * COL + (x + 0)]);
				if (x > 0)
					nodes[y*COL + x].vecNeighbours.push_back(&nodes[(y + 0) * COL + (x - 1)]);
				if (x < COL - 1)
					nodes[y*COL + x].vecNeighbours.push_back(&nodes[(y + 0) * COL + (x + 1)]);
				/*
				if (y>0 && x>0)
					nodes[y*COL + x].vecNeighbours.push_back(&nodes[(y - 1) * COL + (x - 1)]);
				if (y<ROW-1 && x>0)
					nodes[y*COL + x].vecNeighbours.push_back(&nodes[(y + 1) * COL + (x - 1)]);
				if (y>0 && x<COL-1)
					nodes[y*COL + x].vecNeighbours.push_back(&nodes[(y - 1) * COL + (x + 1)]);
				if (y<ROW - 1 && x<COL-1)
					nodes[y*COL + x].vecNeighbours.push_back(&nodes[(y + 1) * COL + (x + 1)]);
				*/
			}
}

void ASTAR::Solve(int arr[COL][ROW])
{
    for (int x = 0; x < COL; x++)
            for (int y = 0; y < ROW; y++)
			{
                if(arr[x][y]==101)
                startNode=&nodes[y*COL + x];
                if(arr[x][y]==102)
                endNode=&nodes[y*COL + x];
                

                if(arr[x][y]!=103)
				nodes[y * COL + x].bObstacle = false;
                else
                nodes[y * COL + x].bObstacle = true;
                
				nodes[y * COL + x].parent = nullptr;
				nodes[y * COL + x].bVisited = false;
                nodes[y * COL + x].isParent = false;
				nodes[y * COL + x].bVisited = false;
				nodes[y * COL + x].fGlobalGoal = INFINITY;
				nodes[y * COL + x].fLocalGoal = INFINITY;
				
            }

    auto _distance = [](Node* a, Node* b)
		{
			return sqrtf((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
		};

		auto heuristic = [_distance](Node* a, Node* b)
		{
			return _distance(a, b);
		};

		Node *nodeCurrent = startNode;
		startNode->fLocalGoal = 0.0f;
		startNode->fGlobalGoal = heuristic(startNode, endNode);

		list<Node*> listNotTestedNodes;
		listNotTestedNodes.push_back(startNode);

		while (!listNotTestedNodes.empty() && nodeCurrent != endNode)
		{

			listNotTestedNodes.sort([](const Node* lhs, const Node* rhs) { return lhs->fGlobalGoal < rhs->fGlobalGoal; });

			while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited)
				listNotTestedNodes.pop_front();

			if (listNotTestedNodes.empty())
				break;

			nodeCurrent = listNotTestedNodes.front();
			nodeCurrent->bVisited = true;

            _content->_states->GetCurrentState()->DrawVisited(nodeCurrent->x,nodeCurrent->y);

			for (auto nodeNeighbour : nodeCurrent->vecNeighbours)
			{
				if (!nodeNeighbour->bVisited && nodeNeighbour->bObstacle == 0)
					listNotTestedNodes.push_back(nodeNeighbour);

				float fPossiblyLowerGoal = nodeCurrent->fLocalGoal + _distance(nodeCurrent, nodeNeighbour);

				if (fPossiblyLowerGoal < nodeNeighbour->fLocalGoal)
				{
					nodeNeighbour->parent = nodeCurrent;
					nodeNeighbour->fLocalGoal = fPossiblyLowerGoal;

					nodeNeighbour->fGlobalGoal = nodeNeighbour->fLocalGoal + heuristic(nodeNeighbour, endNode);
				}
			}
		}
}

void ASTAR::Path()
{
    if (endNode != nullptr)
		{
			Node *p = endNode;
			while (p->parent != nullptr)
			{

				nodes[p->y*COL + p->x].isParent = true;
				p = p->parent;
                if(p!=startNode)
                _content->_states->GetCurrentState()->DrawParent(p->x,p->y);
			}
		}
}