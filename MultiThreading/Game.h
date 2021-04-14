#pragma once

#include <SFML/Graphics.hpp>
#include <Grid.h>
#include <Globals.h>
#include <Player.h>
#include <AStar.h>
#include <Enemy.h>

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
	void initEnemies();
	Enemy* createEnemy(int t_tileID);

	RenderWindow* m_window;
	Grid* m_grid;
	RectangleShape m_shape;
	Player* m_player;
	vector<Enemy*>* m_enemies;
};