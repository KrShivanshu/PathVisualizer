#pragma once
#include "State.hpp"
#include <stack>
#include <memory> 

using namespace std;
namespace Engine {
	class StateMan
	{
	public:
		StateMan();
		~StateMan();

		void AddState(unique_ptr<State>stateToAdd, bool replace = false);
		void ProcessStateChange();
		void PopCurrentState();
		unique_ptr<State>& GetCurrentState();

	private:
		stack<unique_ptr<State>>_stateStack;
		unique_ptr<State>_newState;

		bool _add;
		bool _replace;
		bool _remove;

	};
}

