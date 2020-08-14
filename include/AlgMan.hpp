#pragma once
#include "Algorithm.hpp"
#include "definItions.hpp"
#include <stack>
#include <memory> 


using namespace std;
namespace Engine {
class AlgMan {

public:
    AlgMan();
    ~AlgMan();

		void AddAlgorithm(unique_ptr<Algorithm>algorithmToAdd, bool replace = false);
		void ProcessAlgorithmChange();
		void PopCurrentAlgorithm();
		unique_ptr<Algorithm>& GetCurrentAlgorithm();

	private:
		stack<unique_ptr<Algorithm>>_algorithmStack;
		unique_ptr<Algorithm>_newAlgorithm;

		bool _add;
		bool _replace;
		bool _remove;
        //int _nodeStateAsInt[COL][ROW];

	};
}

