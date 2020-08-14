#pragma once
#include <SFML/System/Time.hpp>
using namespace sf;
namespace Engine {
	class State
	{
	public:
		State() {};
		~State() {};

		virtual void Init() = 0;
		virtual void ProcessInput() = 0;
		virtual void Update(Time deltaATime) = 0;
		virtual void Draw() = 0;

		virtual void Start() {}
		virtual void Pause() {}
		virtual void DrawVisited(int x,int y) {}
		virtual void DrawParent(int x,int y) {}
	};
}
