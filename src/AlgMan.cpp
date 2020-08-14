#include "AlgMan.hpp"
using namespace Engine;

AlgMan::AlgMan():_add(false), _replace(false),_remove(false) 
{

}
AlgMan::~AlgMan() 
{

}
void AlgMan::AddAlgorithm(unique_ptr<Algorithm>algorithmToAdd, bool replace)
{
    _add = true;
    _newAlgorithm=move(algorithmToAdd);
    //_nodeStateAsInt=arr;
    _replace = replace;
}
void AlgMan::ProcessAlgorithmChange()
{
    if (_remove && !(_algorithmStack.empty()))
	{
		_algorithmStack.pop();
		if (!(_algorithmStack.empty()))
		{
			_algorithmStack.top()->Start();
		}
		_remove = false;
	}
	if (_add)
	{
		if (_replace && !(_algorithmStack.empty()))
		{
			_algorithmStack.pop();
			_replace = false;
		}
		if (!(_algorithmStack.empty()))
		{
			_algorithmStack.top()->Pause();
		}
		_algorithmStack.push(move(_newAlgorithm));
		_algorithmStack.top()->Init();
		_algorithmStack.top()->Start();
		_add = false;
	}
}

void AlgMan::PopCurrentAlgorithm()
{
_remove = true;
}

unique_ptr<Algorithm>& AlgMan::GetCurrentAlgorithm()
{
    return _algorithmStack.top();
}
