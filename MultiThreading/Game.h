#pragma once
#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Game
{
public:
	Game();
	~Game();
	void run();
	void update(Time t_deltaTime);
	void render();
	void processEvents();
private:
	void setup();

	RenderWindow* m_window;
};