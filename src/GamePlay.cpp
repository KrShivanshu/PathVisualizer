#include "GamePlay.hpp"
#include "definItions.hpp"
#include "ASTAR.hpp"
#include "DIJKSTRA.hpp"
#include "BFS.hpp"
#include "DFS.hpp"
#include "BIDIRECTIONAL.hpp"
#include <random>

GamePlay::GamePlay(shared_ptr<Content>& content):_content(content)
{
	_nodeSelected = WALL_S;
	_selectedAlgo = BI_D_BFS_S;
	srand(time(nullptr));
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
	_content->_assets->AddTextures("ASTAR1",ASTAR1);
	_content->_assets->AddTextures("ASTAR2",ASTAR2);
	_content->_assets->AddTextures("BFS1",BFS1);
	_content->_assets->AddTextures("BFS2",BFS2);
	_content->_assets->AddTextures("BID1",BID1);
	_content->_assets->AddTextures("BID2",BID2);
	_content->_assets->AddTextures("DFS1",DFS1);
	_content->_assets->AddTextures("DFS2",DFS2);
	_content->_assets->AddTextures("DIJ1",DIJ1);
	_content->_assets->AddTextures("DIJ2",DIJ2);

	for(int i=0;i<COL;i++)
		for(int j=0;j<ROW;j++)
		{
		_cells[i][j].setTexture(_content->_assets->GetTexture("NODE"));
		_cells[i][j].setPosition(i*25+25,j*25+175);
		_cellStateInInt[i][j]=100;
		}
		
	_unVisS.setTexture(_content->_assets->GetTexture("NODE"));
	_startS.setTexture(_content->_assets->GetTexture("START"));
	_endS.setTexture(_content->_assets->GetTexture("END"));
	_pathS.setTexture(_content->_assets->GetTexture("PATH"));
	_wallS.setTexture(_content->_assets->GetTexture("WALL"));
	_vis1S.setTexture(_content->_assets->GetTexture("VISITED1"));
	_vis2S.setTexture(_content->_assets->GetTexture("VISITED2"));
	_vis3S.setTexture(_content->_assets->GetTexture("VISITED3"));
	_astarS.setTexture(_content->_assets->GetTexture("ASTAR2"));
	_bfsS.setTexture(_content->_assets->GetTexture("BFS2"));
	_bidS.setTexture(_content->_assets->GetTexture("BID2"));
	_dfsS.setTexture(_content->_assets->GetTexture("DFS2"));
	_dijS.setTexture(_content->_assets->GetTexture("DIJ2"));
	
	_astarS.setPosition(60,110);
	_bfsS.setPosition(392,110);
	_bidS.setPosition(724,110);
	_dfsS.setPosition(1056,110);
	_dijS.setPosition(1388,110);
	
	_unVisS.setPosition(60,70);
	_unVisT.setFont(_content->_assets->GetFont("FIRST_FONT"));
	_unVisT.setString("Unvisited");
	_unVisT.setCharacterSize(25);
	_unVisT.setPosition(90,66);

	_wallS.setPosition(325,70);
	_wallT.setFont(_content->_assets->GetFont("FIRST_FONT"));
	_wallT.setString("Walls");
	_wallT.setCharacterSize(25);
	_wallT.setPosition(355,66);

	_vis1S.setPosition(590,70);
	_vis2S.setPosition(560,70);
	_visT.setFont(_content->_assets->GetFont("FIRST_FONT"));
	_visT.setString("Visited");
	_visT.setCharacterSize(25);
	_visT.setPosition(620,66);

	_pathS.setPosition(855,70);
	_pathT.setFont(_content->_assets->GetFont("FIRST_FONT"));
	_pathT.setString("Path");
	_pathT.setCharacterSize(25);
	_pathT.setPosition(885,66);


	_startS.setPosition(1120,70);
	_startT.setFont(_content->_assets->GetFont("FIRST_FONT"));
	_startT.setString("Start");
	_startT.setCharacterSize(25);
	_startT.setPosition(1150,66);
	
	_endS.setPosition(1385,70);
	_endT.setFont(_content->_assets->GetFont("FIRST_FONT"));
	_endT.setString("End");
	_endT.setCharacterSize(25);
	_endT.setPosition(1415,66);
	
	
	_messageT.setFont(_content->_assets->GetFont("FIRST_FONT"));
	_messageT.setString("Press Visualise to find path");
	_messageT.setCharacterSize(30);
	_messageT.setPosition(_content->_window->getSize().x/2 - _messageT.getGlobalBounds().width/2, 12 );

	_drawmap.setFont(_content->_assets->GetFont("FIRST_FONT"));
	_drawmap.setString("DrawMap");
	_drawmap.setCharacterSize(30);
	_drawmap.setPosition(92,12);

	_clear.setFont(_content->_assets->GetFont("FIRST_FONT"));
	_clear.setString("ClearMap");
	_clear.setCharacterSize(30);
	_clear.setPosition(252,12);

	_alg.setFont(_content->_assets->GetFont("FIRST_FONT"));
	_alg.setString("Reset");
	_alg.setCharacterSize(30);
	_alg.setPosition(1328,12);

	_visualize.setFont(_content->_assets->GetFont("FIRST_FONT"));
	_visualize.setString("Visualize");
	_visualize.setCharacterSize(30);
	_visualize.setPosition(1448,12);


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
	
	_cells[_startCo.x][_startCo.y].setTexture(_content->_assets->GetTexture("START"));
	_cellStateInInt[_startCo.x][_startCo.y]=101;
	_cells[_endCo.x][_endCo.y].setTexture(_content->_assets->GetTexture("END"));
	_cellStateInInt[_endCo.x][_endCo.y]=102;
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
		else if (_content->_inputs->IsSpriteClicked(_cellsBG, Mouse::Left, *(_content->_window)))
		{
				CheckAndPlaceNode();
		}
		else if(_content->_inputs->IsSpriteClicked(_optionBG, Mouse::Left, *(_content->_window)))
		{
			if(_content->_inputs->IsTextClicked(_startT, Mouse::Left, *(_content->_window)) || _content->_inputs->IsSpriteClicked(_startS, Mouse::Left, *(_content->_window)))
			{
				_nodeSelected = START_S;
				
			}
			else if(_content->_inputs->IsTextClicked(_endT, Mouse::Left, *(_content->_window)) || _content->_inputs->IsSpriteClicked(_endS, Mouse::Left, *(_content->_window)))
			{
				_nodeSelected = END_S;
				
			}
			else if(_content->_inputs->IsTextClicked(_unVisT, Mouse::Left, *(_content->_window)) || _content->_inputs->IsSpriteClicked(_unVisS, Mouse::Left, *(_content->_window)))
			{
				_nodeSelected = UNV_S;
				
			}
			else if(_content->_inputs->IsTextClicked(_wallT, Mouse::Left, *(_content->_window)) || _content->_inputs->IsSpriteClicked(_wallS, Mouse::Left, *(_content->_window)))
			{
				_nodeSelected = WALL_S;
				
			}
			else if(_content->_inputs->IsSpriteClicked(_astarS, Mouse::Left, *(_content->_window)))
			{
				_selectedAlgo = ASTAR_S;
			}
			else if(_content->_inputs->IsSpriteClicked(_bfsS, Mouse::Left, *(_content->_window)))
			{
				_selectedAlgo = BFS_S;
			}
			else if(_content->_inputs->IsSpriteClicked(_bidS, Mouse::Left, *(_content->_window)))
			{
				_selectedAlgo = BI_D_BFS_S;
			}
			else if(_content->_inputs->IsSpriteClicked(_dfsS, Mouse::Left, *(_content->_window)))
			{
				_selectedAlgo = DFS_S;
			}
			else if(_content->_inputs->IsSpriteClicked(_dijS, Mouse::Left, *(_content->_window)))
			{
				_selectedAlgo = DIJKSTRA_S;
			}
			
			


		}
		else if(_content->_inputs->IsSpriteClicked(_funcBG, Mouse::Left, *(_content->_window)))
		{
			_solvedOnceB=false;
			if(_content->_inputs->IsTextClicked(_drawmap, Mouse::Left, *(_content->_window)) )
			{
				_drawMapB=true;
			}
			else if(_content->_inputs->IsTextClicked(_clear, Mouse::Left, *(_content->_window)) )
			{
				_clearMapB=true;
			}
			else if(_content->_inputs->IsTextClicked(_visualize, Mouse::Left, *(_content->_window)) )
			{
				_visualizeB=true;
				ClearVisitedAndPath();
			}
			else if(_content->_inputs->IsTextClicked(_alg, Mouse::Left, *(_content->_window)) )
			{
				_nodeSelected = WALL_S;
				_selectedAlgo = ASTAR_S;
				_startCo = Vector2i(16,15);
				_endCo = Vector2i(48,15);
				Init();
			}
		}
		
	}
}

void GamePlay::Update(Time deltaTime)
{
	MarkAlgorithm();
	MarkSelectedNodeText();

	if(_solvedOnceB)
	{
		if(_pathFoundB){
			_messageT.setFillColor(Color::Green);
			_messageT.setString("Hurray! Path Found");
		}
		else
		{
			_messageT.setFillColor(Color::Cyan);
			_messageT.setString("Opps! No Path Found");
		}
		_messageT.setPosition(_content->_window->getSize().x/2 - _messageT.getGlobalBounds().width/2, 12 );
	}
	else
	{
		_messageT.setFillColor(Color::Yellow);
		_messageT.setString("Press Visualise to find path");
		_messageT.setPosition(_content->_window->getSize().x/2 - _messageT.getGlobalBounds().width/2, 12 );
	}
	

	TIME_PER_FRAME=deltaTime;
	if(_visualizeB)
	{	
		_pathFoundB=false;
		_solveStepByStepB=true;
		if(_selectedAlgo == ASTAR_S)
		_content->_alg->AddAlgorithm(make_unique<ASTAR>(_content),false);
		 else if(_selectedAlgo == DIJKSTRA_S)
		_content->_alg->AddAlgorithm(make_unique<DIJKSTRA>(_content),false);
		else if(_selectedAlgo == DFS_S)
		_content->_alg->AddAlgorithm(make_unique<DFS>(_content),false);
		else if(_selectedAlgo == BFS_S)
		_content->_alg->AddAlgorithm(make_unique<BFS>(_content),false);
		else if(_selectedAlgo == BI_D_BFS_S)
		_content->_alg->AddAlgorithm(make_unique<BIDIRECTIONAL>(_content),false);

		_content->_alg->ProcessAlgorithmChange();
		_content->_alg->GetCurrentAlgorithm()->Solve(_cellStateInInt);
		_content->_alg->GetCurrentAlgorithm()->Path();
		_content->_alg->PopCurrentAlgorithm();
		_solvedOnceB = true;
		_visualizeB=false;
	}
	
	if(_solveFastB && _solvedOnceB)
	{	
		_pathFoundB=false;
		ClearVisitedAndPath();
		_solveStepByStepB=false;
		if(_selectedAlgo == ASTAR_S)
		_content->_alg->AddAlgorithm(make_unique<ASTAR>(_content),false);
		else if(_selectedAlgo == DIJKSTRA_S)
		_content->_alg->AddAlgorithm(make_unique<DIJKSTRA>(_content),false);
		else if(_selectedAlgo == DFS_S)
		_content->_alg->AddAlgorithm(make_unique<DFS>(_content),false);
		else if(_selectedAlgo == BFS_S)
		_content->_alg->AddAlgorithm(make_unique<BFS>(_content),false);
		else if(_selectedAlgo == BI_D_BFS_S)
		_content->_alg->AddAlgorithm(make_unique<BIDIRECTIONAL>(_content),false);
		
		_content->_alg->ProcessAlgorithmChange();
		_content->_alg->GetCurrentAlgorithm()->Solve(_cellStateInInt);
		_content->_alg->GetCurrentAlgorithm()->Path();
		_content->_alg->PopCurrentAlgorithm();
		//_solvedOnce = true;
		_solveFastB=false;
	}
	if(_drawMapB)
	{
		for(int i=0;i<COL;i++)
		{
			for(int j=0;j<ROW;j++)
			{
				if(_cellStateInInt[i][j]==103)
				{
				_cellStateInInt[i][j]=100;
				_cells[i][j].setTexture(_content->_assets->GetTexture("NODE"));
				}
			}
		}
		int x = 0, y = 0,n=0;
				n=400+rand()%400;//distrn(gen);
				for(int i=0;i<n;i++)
				{
					x = rand()%COL;//distrx(gen);
					y = rand()%ROW;//distry(gen);
					if(x == _startCo.x  && y==_startCo.y) { }
					else if (x == _endCo.x  && y ==_endCo.y) { }
					else
					{
					_cellStateInInt[x][y]=103;
					_cells[x][y].setTexture(_content->_assets->GetTexture("WALL"));
					//_content->_window->draw(_cells[x][y]);
					}
				}
		_drawMapB=false;
	}
	if(_clearMapB)
	{
		for(int i=0;i<COL;i++)
		{
			for(int j=0;j<ROW;j++)
			{
				if(_cellStateInInt[i][j]!=101 && _cellStateInInt[i][j]!=102)
				{
				_cellStateInInt[i][j]=100;
				_cells[i][j].setTexture(_content->_assets->GetTexture("NODE"));
				}
			}
		}
		_clearMapB=false;
	}
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
	_content->_window->draw(_astarS);
	_content->_window->draw(_bfsS);
	_content->_window->draw(_bidS);
	_content->_window->draw(_dfsS);
	_content->_window->draw(_dijS);
	_content->_window->draw(_messageT);
	_content->_window->draw(_cellsBG);
	for(int i=0;i<COL;i++)
		for(int j=0;j<ROW;j++)
			_content->_window->draw(_cells[i][j]);
	_content->_window->display();
}

void GamePlay::CheckAndPlaceNode()
{
	Vector2i touchPoint = _content->_inputs->GetMousePosition(*(_content->_window));
	//FloatRect gridSize = _cellsBG.getGlobalBounds();
	Vector2f gapOutsideOfGrid = Vector2f(25.f,175.f);
	Vector2f gridLocalTouchPos = Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);
	

	int column, row;
	column=gridLocalTouchPos.x/25.f;
	row=gridLocalTouchPos.y/25.f;
	if(column == _startCo.x  && row==_startCo.y) { }
	else if (column == _endCo.x  && row ==_endCo.y) { }
	else
	{
		if(_nodeSelected == WALL_S){
		_cells[column][row].setTexture(_content->_assets->GetTexture("WALL"));
		_cellStateInInt[column][row]=103;
		}
		else if(_nodeSelected == START_S && _cellStateInInt[column][row]!=103)
		{
		_cells[_startCo.x][_startCo.y].setTexture(_content->_assets->GetTexture("NODE"));
			_cellStateInInt[_startCo.x][_startCo.y]=100;

		_cells[column][row].setTexture(_content->_assets->GetTexture("START"));
		_cellStateInInt[column][row]=101;
		_startCo=Vector2i(column,row);
		_solveFastB=true;
		}
		else if(_nodeSelected == END_S && _cellStateInInt[column][row]!=103)
		{
		_cells[_endCo.x][_endCo.y].setTexture(_content->_assets->GetTexture("NODE"));
			_cellStateInInt[_endCo.x][_endCo.y]=100;

		_cells[column][row].setTexture(_content->_assets->GetTexture("END"));
		_cellStateInInt[column][row]=102;
		_endCo=Vector2i(column,row);
		_solveFastB=true;
		}
		else if(_nodeSelected == UNV_S && _cellStateInInt[column][row]!=102 && _cellStateInInt[column][row]!=101)
		{
		_cells[column][row].setTexture(_content->_assets->GetTexture("NODE"));
		_cellStateInInt[column][row]=100;
		}
	}
}

void GamePlay::MarkSelectedNodeText()
{
	if(_nodeSelected == START_S)
	{
		_startT.setOutlineThickness(3.f);
		_endT.setOutlineThickness(0.f);
		_wallT.setOutlineThickness(0.f);
		_unVisT.setOutlineThickness(0.f);
		_startT.setOutlineColor(Color::Red);
	}
	else if(_nodeSelected == END_S)
	{
		_startT.setOutlineThickness(0.f);
		_endT.setOutlineThickness(3.f);
		_wallT.setOutlineThickness(0.f);
		_unVisT.setOutlineThickness(0.f);
		_endT.setOutlineColor(Color::Red);
	}
	else if(_nodeSelected == WALL_S)
	{
		_startT.setOutlineThickness(0.f);
		_endT.setOutlineThickness(0.f);
		_wallT.setOutlineThickness(3.f);
		_unVisT.setOutlineThickness(0.f);
		_wallT.setOutlineColor(Color::Red);
	}
	else if(_nodeSelected == UNV_S)
	{
		_startT.setOutlineThickness(0.f);
		_endT.setOutlineThickness(0.f);
		_wallT.setOutlineThickness(0.f);
		_unVisT.setOutlineThickness(3.f);
		_unVisT.setOutlineColor(Color::Red);
	}
}

void GamePlay::DrawVisited(int x,int y)
{
	if(_cellStateInInt[x][y]!=101 && _cellStateInInt[x][y]!=102)
	{
		if(b==0){
		_cells[x][y].setTexture(_content->_assets->GetTexture("VISITED2"));
		b=1;
		}
		else{
			_cells[x][y].setTexture(_content->_assets->GetTexture("VISITED1"));
		b=0;
		} 
		//_cellStateInInt[x][y]=104;
		if(_solveStepByStepB)
		{
			_elapsedTimeForVisited+=TIME_PER_FRAME;
			
			if(_elapsedTimeForVisited.asSeconds() >= .1)
			{
				//_content->_window->draw(_cells[x][y]);
				Draw();
				
				_elapsedTimeForVisited=Time::Zero;
			}
		}
	}
}

void GamePlay::DrawParent(int x,int y)
{
	_pathFoundB=true;
	_cells[x][y].setTexture(_content->_assets->GetTexture("PATH"));
	if(_solveStepByStepB)
		{
			//_content->_window->draw(_cells[x][y]);
			Draw();
			
		}
	
}

void GamePlay::ClearVisitedAndPath()
{
	for(int i=0;i<COL;i++)
		for(int j=0;j<ROW;j++)
		{
			if(_cellStateInInt[i][j]!=101 && _cellStateInInt[i][j]!=102 && _cellStateInInt[i][j]!=103  )
			{
				_cells[i][j].setTexture(_content->_assets->GetTexture("NODE"));
				_cellStateInInt[i][j]=100;
			}
		}
}

void GamePlay::MarkAlgorithm()
{
	if(_selectedAlgo==ASTAR_S)
	{
	_astarS.setTexture(_content->_assets->GetTexture("ASTAR1"));
	_bfsS.setTexture(_content->_assets->GetTexture("BFS2"));
	_bidS.setTexture(_content->_assets->GetTexture("BID2"));
	_dfsS.setTexture(_content->_assets->GetTexture("DFS2"));
	_dijS.setTexture(_content->_assets->GetTexture("DIJ2"));
	}
	else if(_selectedAlgo==BFS_S)
	{
	_astarS.setTexture(_content->_assets->GetTexture("ASTAR2"));
	_bfsS.setTexture(_content->_assets->GetTexture("BFS1"));
	_bidS.setTexture(_content->_assets->GetTexture("BID2"));
	_dfsS.setTexture(_content->_assets->GetTexture("DFS2"));
	_dijS.setTexture(_content->_assets->GetTexture("DIJ2"));
	}
	else if(_selectedAlgo==BI_D_BFS_S)
	{
	_astarS.setTexture(_content->_assets->GetTexture("ASTAR2"));
	_bfsS.setTexture(_content->_assets->GetTexture("BFS2"));
	_bidS.setTexture(_content->_assets->GetTexture("BID1"));
	_dfsS.setTexture(_content->_assets->GetTexture("DFS2"));
	_dijS.setTexture(_content->_assets->GetTexture("DIJ2"));
	}
	else if(_selectedAlgo==DFS_S)
	{
	_astarS.setTexture(_content->_assets->GetTexture("ASTAR2"));
	_bfsS.setTexture(_content->_assets->GetTexture("BFS2"));
	_bidS.setTexture(_content->_assets->GetTexture("BID2"));
	_dfsS.setTexture(_content->_assets->GetTexture("DFS1"));
	_dijS.setTexture(_content->_assets->GetTexture("DIJ2"));
	}
	else if(_selectedAlgo==DIJKSTRA_S)
	{
	_astarS.setTexture(_content->_assets->GetTexture("ASTAR2"));
	_bfsS.setTexture(_content->_assets->GetTexture("BFS2"));
	_bidS.setTexture(_content->_assets->GetTexture("BID2"));
	_dfsS.setTexture(_content->_assets->GetTexture("DFS2"));
	_dijS.setTexture(_content->_assets->GetTexture("DIJ1"));
	}
	
}