#include "BIDIRECTIONAL.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <cmath>

BIDIRECTIONAL::BIDIRECTIONAL(shared_ptr<Content>&content):_content(content) {

}

BIDIRECTIONAL::~BIDIRECTIONAL() {

}

void BIDIRECTIONAL::Init()
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
				nodes[y * COL + x].bConsideredE = false;
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

void BIDIRECTIONAL::Solve(int arr[COL][ROW])
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
				nodes[y * COL + x].bConsideredE = false;
				
            }

		

		Node *nodeCurrent = startNode;
		Node *nodeCurrentE = endNode;

		list<Node*> listNotTestedNodes;
		listNotTestedNodes.push_back(startNode);

        list<Node*> listNotTestedNodesE;
        listNotTestedNodesE.push_back(endNode);

		while ((!listNotTestedNodes.empty() && nodeCurrent != endNode) || (!listNotTestedNodesE.empty() && nodeCurrentE!=startNode))
		{

			while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited)
				listNotTestedNodes.pop_front();

            while(!listNotTestedNodesE.empty() && listNotTestedNodesE.front()->bVisited)
                listNotTestedNodesE.pop_front();

			if (listNotTestedNodes.empty() && listNotTestedNodesE.empty())
                break;

			nodeCurrent = listNotTestedNodes.front();
			nodeCurrent->bVisited = true;
            _content->_states->GetCurrentState()->DrawVisited(nodeCurrent->x,nodeCurrent->y);

            nodeCurrentE=listNotTestedNodesE.front();
            nodeCurrentE->bVisited=true;
            _content->_states->GetCurrentState()->DrawVisited(nodeCurrentE->x,nodeCurrentE->y);
            
			for (auto nodeNeighbour : nodeCurrent->vecNeighbours)
			{
				if (!nodeNeighbour->bVisited && nodeNeighbour->bObstacle == 0 && !nodeNeighbour->bConsideredE)
                {
                    
					listNotTestedNodes.push_back(nodeNeighbour);
					nodeNeighbour->parent = nodeCurrent;
                    nodeNeighbour->bConsidered = true;
                }
                else if(nodeNeighbour->bConsideredE)
                    {
                        //cout<<"startNode found the path first\n";
                        Node *temp=nodeNeighbour->parent;
                        Node *tempParent = nodeCurrent;
                        Node *tempCurrent = nodeNeighbour;
                        while(tempCurrent!=endNode)
                        {
                            tempCurrent->parent=tempParent;
                            tempParent=tempCurrent;
                            tempCurrent=temp;
                            temp=tempCurrent->parent;
                        }
                        tempCurrent->parent=tempParent;
                        listNotTestedNodes.clear();
                        listNotTestedNodesE.clear();
                        delete (temp);
                        delete (tempParent);
                        delete (tempCurrent);
                        break;
                    }
			}

            if (listNotTestedNodes.empty() && listNotTestedNodesE.empty())
            { 
                break;
            }       

                for (auto nodeNeighbour : nodeCurrentE->vecNeighbours)
                {
                    if (!nodeNeighbour->bVisited && nodeNeighbour->bObstacle == 0 && !nodeNeighbour->bConsidered)
                    {
                        listNotTestedNodesE.push_back(nodeNeighbour);
                        nodeNeighbour->parent = nodeCurrentE;
                        nodeNeighbour->bConsideredE=true;

                    }
                    else if(nodeNeighbour->bConsidered)
                    {   
                        //cout<<"endNode found the path first\n";
                        Node *temp=nodeCurrentE->parent;      
                        Node *tempParent = nodeNeighbour;
                        Node *tempCurrent = nodeCurrentE;
                        while(tempCurrent!=endNode)
                        {
                            tempCurrent->parent=tempParent;
                            tempParent=tempCurrent;
                            tempCurrent=temp;
                            temp=tempCurrent->parent;
                        }
                        endNode->parent=tempParent;
                        listNotTestedNodes.clear();
                        listNotTestedNodesE.clear();
                        delete (temp);
                        delete (tempParent);
                        delete (tempCurrent);
                        break;
                    }
                }
            
		}
}

void BIDIRECTIONAL::Path()
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