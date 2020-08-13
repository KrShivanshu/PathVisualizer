#pragma once
#include <memory>
#include "State.hpp"
#include "Game.hpp"
#include "SFML/Graphics.hpp"

//using namespace Engine;
using namespace std;
using namespace sf;
using namespace Engine;



class SplashScreen :
	public State
{
public:
	SplashScreen(shared_ptr<Content>& context);
	~SplashScreen();

	void Init() override;
	void ProcessInput() override;
	void Update(Time deltaTime) override;
	void Draw() override;

private:
	shared_ptr<Content>_content;
	Clock _clock;
	Sprite _backGround;
	Text _title;
};

