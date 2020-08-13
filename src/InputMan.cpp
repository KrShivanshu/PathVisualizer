#include "InputMan.hpp"

bool Engine::InputMan::IsSpriteClicked(Sprite object, Mouse::Button button, RenderWindow& window)
{
	if (Mouse::isButtonPressed(button))
	{
		IntRect buttonRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);
		if (buttonRect.contains(Mouse::getPosition(window)))
		{
			return true;
		}
	}
	return false;
}
bool Engine::InputMan::IsTextClicked(Text object, Mouse::Button button, RenderWindow& window)
{
	if (Mouse::isButtonPressed(button))
	{
		IntRect buttonRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);
		if (buttonRect.contains(Mouse::getPosition(window)))
		{
			return true;
		}
	}
	return false;
}


Vector2i Engine::InputMan::GetMousePosition(RenderWindow& window)
{
	return Mouse::getPosition(window);
}
