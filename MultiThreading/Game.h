#pragma once

#include <SFML/Graphics.hpp>
#include <Grid.h>
#include <Globals.h>

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
	const Vector2f SIZE = Vector2f(1.0f, 1.0f);

	void setup(GridSize t_size);
	void setupRender();

	RenderWindow* m_window;
	Grid* grid;
	RectangleShape m_shape;
};