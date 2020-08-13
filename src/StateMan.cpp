#include "StateMan.hpp"


Engine::StateMan::StateMan() : _add(false), _replace(false),_remove(false)
{
}
Engine::StateMan::~StateMan()
{
}

void Engine::StateMan::AddState(unique_ptr<State> stateToAdd, bool replace)
{
	_add = true;
	_newState = move(stateToAdd);
	_replace = replace;
}

void Engine::StateMan::ProcessStateChange()
{
	if (_remove && !(_stateStack.empty()))
	{
		_stateStack.pop();
		if (!(_stateStack.empty()))
		{
			_stateStack.top()->Start();
		}
		_remove = false;
	}
	if (_add)
	{
		if (_replace && !(_stateStack.empty()))
		{
			_stateStack.pop();
			_replace = false;
		}
		if (!(_stateStack.empty()))
		{
			_stateStack.top()->Pause();
		}
		_stateStack.push(move(_newState));
		_stateStack.top()->Init();
		_stateStack.top()->Start();
		_add = false;
	}
}

void Engine::StateMan::PopCurrentState()
{
	_remove = true;
}

unique_ptr<Engine::State>& Engine::StateMan::GetCurrentState()
{
	// TODO: insert return statement here
	return _stateStack.top();
}








