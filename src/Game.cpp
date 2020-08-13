#include "Game.hpp"
#include "definitions.hpp"
#include "SFML/Graphics.hpp"
#include "SplashScreen.hpp"

using namespace std;
using namespace Engine;
using namespace sf;

Engine::Game::Game() :_content(make_shared<Content>())
{
	_content->_window->create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "PATH VISUALIZER", Style::Close);
	//add splash screen state here
	_content->_states->AddState(make_unique<SplashScreen>(_content), true);
}

Engine::Game::~Game()
{
}

void Engine::Game::Run()
{
	Clock clock;
	Time timeSinceLastFrame = Time::Zero;
	while (_content->_window->isOpen())
	{
		timeSinceLastFrame += clock.restart();
		while (timeSinceLastFrame > TIME_PER_FRAME)
		{
			timeSinceLastFrame -= TIME_PER_FRAME;
			_content->_states->ProcessStateChange();
			_content->_states->GetCurrentState()->ProcessInput();
			_content->_states->GetCurrentState()->Update(TIME_PER_FRAME);
			_content->_states->GetCurrentState()->Draw();
		}
	}
}
