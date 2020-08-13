#pragma once
//#include "State.h"
#include "SFML/Graphics.hpp"
using namespace sf;
namespace Engine
{
	class InputMan
	{
	private:

	public:
		InputMan() {}
		~InputMan() {}

		bool IsSpriteClicked(Sprite object, Mouse::Button button, RenderWindow& window);
		Vector2i GetMousePosition(RenderWindow& window);
	};
}

