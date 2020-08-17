#pragma once
#include <memory>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <SFML/System/Time.hpp>
#include "definItions.hpp"
//#include "Game.hpp"
using namespace std;
namespace Engine {

struct Node
	{
		bool isParent = false;
		bool bObstacle = false;
		bool bVisited = false;
		bool bConsidered = false;
		bool bConsideredE = false;
		float fGlobalGoal;
		float fLocalGoal;
		int x;
		int y;
		vector<Node*> vecNeighbours;
		Node* parent;

	};

	class Algorithm
	{
    

	public:
		Algorithm() {};
		~Algorithm() {};

		virtual void Init() = 0;
		virtual void Solve(int arr[COL][ROW]) = 0;
		virtual void Path() = 0;
		

		virtual void Start() {}
		virtual void Pause() {}

		Node *nodes=nullptr;
	};
}
