#pragma once
#include "definItions.hpp"
#include "Algorithm.hpp"
#include "Game.hpp"
using namespace Engine;
class DFS: public Algorithm {

public:
    DFS(shared_ptr<Content>&content);
    ~DFS();
    virtual void Init() override;
	virtual void Solve(int arr[COL][ROW]) override;
	virtual void Path() override;

private:
    shared_ptr<Content>_content;
    Node *startNode=nullptr;
    Node *endNode=nullptr;
};