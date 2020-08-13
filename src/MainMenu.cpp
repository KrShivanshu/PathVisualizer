#include "MainMenu.hpp"
#include "definItions.hpp"
#include <iostream>
#include <sstream>
//#include "GamePlay.h"
using namespace sf;
MainMenu::MainMenu(shared_ptr<Content>&content):_content(content)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
	_content->_assets->AddTextures("MAIN_MENU_BG", MAIN_MENU_BG);
	_backGround.setTexture(_content->_assets->GetTexture("MAIN_MENU_BG"));

	_content->_assets->AddFont("GAME_TITLE", FIRST_FONT);
	_gameTitle.setFont(_content->_assets->GetFont("GAME_TITLE"));
	_gameTitle.setCharacterSize(50.f);
	_gameTitle.setString("Path Visualizer");
	_gameTitle.setOrigin(_gameTitle.getGlobalBounds().width / 2, _gameTitle.getGlobalBounds().height / 2);
	_gameTitle.setPosition(_content->_window->getSize().x / 2, _content->_window->getSize().y / 10*1 );
	//_gameTitle.setCharacterSize(40.f);

	_content->_assets->AddTextures("PLAY_BUTTON",PLAY_BUTTON_PATH);
	_playButton.setTexture(_content->_assets->GetTexture("PLAY_BUTTON"));
	//_playButton.setOrigin(_playButton.getGlobalBounds().width / 2, _playButton.getGlobalBounds().height / 2);
	_playButton.setPosition(_content->_window->getSize().x / 2 - _playButton.getGlobalBounds().width / 2, _content->_window->getSize().y / 10*6 - _playButton.getGlobalBounds().height / 2);

	//_content->_assets->AddTextures("EXIT_BUTTON", EXIT_BUTTON_PATH);
	//_exitButton.setTexture(_content->_assets->GetTexture("EXIT_BUTTON"));
	//_exitButton.setScale(.65f, .65f);
	//_exitButton.setOrigin(,);
	//.setPosition(_content->_window->getSize().x / 2-(_exitButton.getGlobalBounds().width / 2), _content->_window->getSize().y / 10 * 6-(_exitButton.getGlobalBounds().height / 2));



}

void MainMenu::ProcessInput()
{
	Event event;
	while (_content->_window->pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			_content->_window->close();
		}
		else if (_content->_inputs->IsSpriteClicked(_playButton, Mouse::Left, *(_content->_window)))
		{
			//_content->_states->AddState(make_unique<GamePlay>(_content), true);
			//_content->_window->close();
		}
		//else if (_content->_inputs->IsSpriteClicked(_exitButton, Mouse::Left, *(_content->_window)))
		//{
		//	_content->_window->close();
		//}
	}
}

void MainMenu::Update(Time deltaTime)
{
}

void MainMenu::Draw()
{
	_content->_window->clear();
	_content->_window->draw(_backGround);
	_content->_window->draw(_gameTitle);
	_content->_window->draw(_playButton);
	//_content->_window->draw(_exitButton);
	_content->_window->display();
}

