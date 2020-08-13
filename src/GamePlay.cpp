#include "GamePlay.hpp"
#include "definItions.hpp"


GamePlay::GamePlay(shared_ptr<Content>& content):_content(content)
{
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{
	_content->_assets->AddTextures("NODE",NODE);
	_content->_assets->AddTextures("GAME_PLAY_BG",GAME_PLAY_BG);
	_content->_assets->AddTextures("FUNCTION_BG",FUNCTION_BG);
	_content->_assets->AddTextures("CELLS_BG",CELLS_BG);
	_content->_assets->AddTextures("OPTION_BG",OPTION_BG);
	_content->_assets->AddTextures("START",START);
	_content->_assets->AddTextures("END",END);
	_content->_assets->AddTextures("PATH",PATH);
	_content->_assets->AddTextures("VISITED1",VISITED1);
	_content->_assets->AddTextures("VISITED2",VISITED2);
	_content->_assets->AddTextures("VISITED3",VISITED3);
	_content->_assets->AddTextures("WALL",WALL);
	_content->_assets->AddFont("FIRST_FONT",FIRST_FONT);
	for(int i=0;i<COL;i++)
		for(int j=0;j<ROW;j++)
		{
		_cells[i][j].setTexture(_content->_assets->GetTexture("NODE"));
		_cells[i][j].setPosition(i*25+25,j*25+175);
		}
		
	_unVisS.setTexture(_content->_assets->GetTexture("NODE"));
	_startS.setTexture(_content->_assets->GetTexture("START"));
	_endS.setTexture(_content->_assets->GetTexture("END"));
	_pathS.setTexture(_content->_assets->GetTexture("PATH"));
	_wallS.setTexture(_content->_assets->GetTexture("WALL"));
	_vis1S.setTexture(_content->_assets->GetTexture("VISITED1"));
	_vis2S.setTexture(_content->_assets->GetTexture("VISITED2"));
	_vis3S.setTexture(_content->_assets->GetTexture("VISITED3"));
	
	
	_unVisS.setPosition(60,70);
	_unVisT.setFont(_content->_assets->GetFont("FIRST_FONT"));
	_unVisT.setString("Unvisited");
	_unVisT.setCharacterSize(25);
	_unVisT.setPosition(95,66);

	_wallS.setPosition(460,70);
	_wallT.setFont(_content->_assets->GetFont("FIRST_FONT"));
	_wallT.setString("Walls");
	_wallT.setCharacterSize(25);
	_wallT.setPosition(495,66);

	_vis1S.setPosition(860,70);
	_vis2S.setPosition(825,70);
	_visT.setFont(_content->_assets->GetFont("FIRST_FONT"));
	_visT.setString("Visited");
	_visT.setCharacterSize(25);
	_visT.setPosition(895,66);

	_pathS.setPosition(1260,70);
	_pathT.setFont(_content->_assets->GetFont("FIRST_FONT"));
	_pathT.setString("Path");
	_pathT.setCharacterSize(25);
	_pathT.setPosition(1295,66);


	_startS.setPosition(1260,110);
	_startT.setFont(_content->_assets->GetFont("FIRST_FONT"));
	_startT.setString("Start");
	_startT.setCharacterSize(25);
	_startT.setPosition(1295,106);
	
	_endS.setPosition(60,110);
	_endT.setFont(_content->_assets->GetFont("FIRST_FONT"));
	_endT.setString("End");
	_endT.setCharacterSize(25);
	_endT.setPosition(95,106);
	

	_drawmap.setFont(_content->_assets->GetFont("FIRST_FONT"));
	_drawmap.setString("DrawMap");
	_drawmap.setCharacterSize(30);
	_drawmap.setPosition(92,12);

	_clear.setFont(_content->_assets->GetFont("FIRST_FONT"));
	_clear.setString("ClearMap");
	_clear.setCharacterSize(30);
	_clear.setPosition(476,12);

	_alg.setFont(_content->_assets->GetFont("FIRST_FONT"));
	_alg.setString("Algorithm");
	_alg.setCharacterSize(30);
	_alg.setPosition(860,12);

	_visualize.setFont(_content->_assets->GetFont("FIRST_FONT"));
	_visualize.setString("Visualize");
	_visualize.setCharacterSize(30);
	_visualize.setPosition(1244,12);


	_background.setTexture(_content->_assets->GetTexture("GAME_PLAY_BG"));
	_cellsBG.setTexture(_content->_assets->GetTexture("CELLS_BG"));
	_optionBG.setTexture(_content->_assets->GetTexture("OPTION_BG"));
	//IntRect buttonRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT-150);
	//_cellsBG.setTextureRect(buttonRect);
	_funcBG.setTexture(_content->_assets->GetTexture("FUNCTION_BG"));
	_funcBG.setPosition(82,10);
	_cellsBG.setPosition(25,175);
	_optionBG.setPosition(50,65);
	_background.setOrigin(_background.getGlobalBounds().width / 2, _background.getGlobalBounds().height / 2);
	_background.setPosition(_content->_window->getSize().x / 2, _content->_window->getSize().y / 2);
	
	
}

void GamePlay::ProcessInput()
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

void GamePlay::Update(Time deltaTime)
{
	
}

void GamePlay::Draw()
{
	_content->_window->clear();
	_content->_window->draw(_background);
	_content->_window->draw(_funcBG);
	_content->_window->draw(_drawmap);
	_content->_window->draw(_clear);
	_content->_window->draw(_alg);
	_content->_window->draw(_visualize);
	_content->_window->draw(_optionBG);
	_content->_window->draw(_wallS);
	_content->_window->draw(_wallT);
	_content->_window->draw(_vis2S);
	_content->_window->draw(_vis1S);
	_content->_window->draw(_visT);
	_content->_window->draw(_unVisS);
	_content->_window->draw(_unVisT);
	_content->_window->draw(_startS);
	_content->_window->draw(_startT);
	_content->_window->draw(_endS);
	_content->_window->draw(_endT);
	_content->_window->draw(_pathS);
	_content->_window->draw(_pathT);
	_content->_window->draw(_cellsBG);
	for(int i=0;i<COL;i++)
		for(int j=0;j<ROW;j++)
			_content->_window->draw(_cells[i][j]);
	_content->_window->display();
}


