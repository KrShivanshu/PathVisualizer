#pragma once
#include <memory>
#include "State.hpp"
#include "Game.hpp"
#include "SFML/Graphics.hpp"
#include "definItions.hpp"

using namespace Engine;
using namespace sf;
using namespace std;
class GamePlay: public State {

public:
    GamePlay(shared_ptr<Content>&content);
    ~GamePlay();
    void Init() override;
	void ProcessInput() override;
	void Update(Time deltaTime) override;
	void Draw() override;
    	void DrawVisited(int x,int y) override;
		void DrawParent(int x,int y) override;

    private:
    string _nodeSelected;

	shared_ptr<Content>_content;
    Sprite _background;
    Sprite _cellsBG;
    Sprite _cells[COL][ROW];
    Sprite _funcBG;
    Text _drawmap;
    Text _clear;
    Text _alg;
    Text _visualize;
    Sprite _startS;
    Sprite _endS;
    Sprite _pathS;
    Sprite _vis1S;
    Sprite _vis2S;
    Sprite _vis3S;
    Sprite _wallS;
    Sprite _unVisS;
    Sprite _optionBG;
    Text _startT;
    Text _endT;
    Text _pathT;
    Text _visT;
    Text _unVisT;
    Text _wallT;
    Vector2i _startCo = Vector2i(16,15);
    Vector2i _endCo = Vector2i(48,15);
    int _cellStateInInt[66][30];
    void CheckAndPlaceNode();
    void MarkSelectedNodeText();
    void ClearVisitedAndPath();
    bool _drawMapB=false;
    bool _clearMapB=false;
    bool _visualizeB=false;
    Time TIME_PER_FRAME;
    Time _elapsedTimeForVisited=Time::Zero;
    bool _solveStepByStepB=true;
    bool _solveFastB=false;
    bool _solvedOnceB=false;
    string _selectedAlgo;
    //void DrawVisited(int x,int y);
    

};