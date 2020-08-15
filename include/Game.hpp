#pragma once
#include <memory>
#include "SFML/Graphics.hpp"
#include "AssetMan.hpp"
#include "InputMan.hpp"
#include "StateMan.hpp"
#include "AlgMan.hpp"
using namespace std;
using namespace sf;
namespace Engine {
	struct Content
	{
		unique_ptr<AssetMan>_assets;
		unique_ptr<InputMan>_inputs;
		unique_ptr<StateMan>_states;
		unique_ptr<AlgMan>_alg;
		unique_ptr<RenderWindow>_window;

		Content()
		{
			_assets = make_unique<AssetMan>();
			_states = make_unique<StateMan>();
			_inputs = make_unique<InputMan>();
			_alg 	= make_unique<AlgMan>();
			_window = make_unique<RenderWindow>();

		}
	};
	class Game
	{
	private:
		shared_ptr<Content>_content;
		const Time TIME_PER_FRAME = seconds(1.f / 60.f);

	public:
		Game();
		~Game();
		void Run();
	};
}

