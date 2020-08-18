#include "SplashScreen.hpp"
#include "MainMenu.hpp"
#include "GamePlay.hpp"
#include "definItions.hpp"
#include <SFML/Window/Event.hpp>
#include <sstream>
#include <iostream>

SplashScreen::SplashScreen(shared_ptr<Content>& content) :_content(content)
{
}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::Init()
{
	_content->_assets->AddTextures("SPLASH_SCREEN_BG", SPLASH_SCREEN_BG);
	_content->_assets->AddFont("TITLE_FONT", FIRST_FONT);

	_backGround.setTexture(_content->_assets->GetTexture("SPLASH_SCREEN_BG"));
	_title.setFont(_content->_assets->GetFont("TITLE_FONT"));

	_title.setString("Nerd Gaming");
	_title.setCharacterSize(50);

	_backGround.setOrigin(_backGround.getGlobalBounds().width / 2, _backGround.getGlobalBounds().height / 2);
	_title.setOrigin(_title.getGlobalBounds().width / 2, _title.getGlobalBounds().height / 2);

	_backGround.setPosition(_content->_window->getSize().x / 2, _content->_window->getSize().y / 2);
	_title.setPosition(_content->_window->getSize().x / 2, _content->_window->getSize().y / 2);

	
}

void SplashScreen::ProcessInput()
{
	Event event;
	while (_content->_window->pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			_content->_window->close();
		}
	}
}

void SplashScreen::Update(Time deltaTime)
{
	if (_clock.getElapsedTime().asSeconds() > SPALSH_SCREEN_TIME)
	{
		_content->_states->AddState(make_unique<MainMenu>(_content), true);
	}
}

void SplashScreen::Draw()
{
	_content->_window->clear();
	_content->_window->draw(_backGround);
	_content->_window->draw(_title);
	_content->_window->display();

}
