#pragma once
#include "Algorithm.hpp"
#include "definItions.hpp"
#include "Game.hpp"
using namespace Engine;
class ASTAR:public Algorithm 
{
public:
    ASTAR(shared_ptr<Content>&content);
    ~ASTAR();
    virtual void Init() override;
	virtual void Solve(int arr[COL][ROW]) override;
	virtual void Path() override;

private:
    shared_ptr<Content>_content;
    Node *startNode=nullptr;
    Node *endNode=nullptr;

};