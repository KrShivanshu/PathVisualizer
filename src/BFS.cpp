#include "BFS.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <cmath>
BFS::BFS(shared_ptr<Content>&content):_content(content){

}

BFS::~BFS() {

}

void BFS::Init()
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

void BFS::Solve(int arr[COL][ROW])
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

		

		Node *nodeCurrent = startNode;
		

		list<Node*> listNotTestedNodes;
		listNotTestedNodes.push_back(startNode);

		while (!listNotTestedNodes.empty() && nodeCurrent != endNode)
		{

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
                {
					listNotTestedNodes.push_back(nodeNeighbour);
					nodeNeighbour->parent = nodeCurrent;
                }
					
			}
		}
}

void BFS::Path()
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