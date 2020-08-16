#include "DFS.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <cmath>

DFS::DFS(shared_ptr<Content>&content):_content(content){

}

DFS::~DFS() {

}

void DFS::Init()
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
				nodes[y * COL + x].bConsidered = false;
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

void DFS::Solve(int arr[COL][ROW])
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
				nodes[y * COL + x].bConsidered = false;
				nodes[y * COL + x].fGlobalGoal = INFINITY;
				nodes[y * COL + x].fLocalGoal = INFINITY;
				
            }

		

		Node *nodeCurrent = startNode;
		
		stack<Node*> stackNotTestedNodes;
		stackNotTestedNodes.push(startNode);

		while (!stackNotTestedNodes.empty() && nodeCurrent != endNode)
		{

			

			while (!stackNotTestedNodes.empty() && stackNotTestedNodes.top()->bVisited)
				stackNotTestedNodes.pop();

			if (stackNotTestedNodes.empty())
				break;

			nodeCurrent = stackNotTestedNodes.top();
			nodeCurrent->bConsidered = true;

            _content->_states->GetCurrentState()->DrawVisited(nodeCurrent->x,nodeCurrent->y);

			for (auto nodeNeighbour : nodeCurrent->vecNeighbours)
			{
                int size=nodeCurrent->vecNeighbours.size();
                if(nodeNeighbour == nodeCurrent->vecNeighbours[size-1])
                    {
                        nodeCurrent->bVisited = true;
                    }

                if(nodeNeighbour==startNode)
                nodeCurrent->parent=startNode;

				if (!nodeNeighbour->bVisited && !nodeNeighbour->bConsidered && nodeNeighbour->bObstacle == 0)
                {
					stackNotTestedNodes.push(nodeNeighbour);
					nodeNeighbour->parent = nodeCurrent;
                    nodeNeighbour->bConsidered=true;
                    break;
                }

                
			}
		}
}

void DFS::Path()
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

                if(p==startNode)
                break;
			}
		}
}