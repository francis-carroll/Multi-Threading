#pragma once

#include <SFML/Graphics.hpp>
#include <Grid.h>
#include <Globals.h>
#include <Player.h>
#include <AStar.h>
#include <Enemy.h>
#include <thread>
#include <mutex>

using namespace std;
using namespace sf;

class Game
{
public:
	Game();
	~Game();
	void run();
	void update(Time t_deltaTime);
	static void render(Game* t_game);
	void processEvents();
private:
	const Vector2f SIZE = Vector2f(1.0f, 1.0f);

	static void setup(Game* t_game, GridSize t_size);
	void setupRender();
	static void renderGrid(Game* t_game);
	static void initEnemies(Game* t_game);
	Enemy* createEnemy(int t_tileID);
	static void setupRenderTexure(Game* t_game);

	RenderWindow* m_window;
	Grid* m_grid;
	RectangleShape m_shape;
	Player* m_player;
	vector<Enemy*>* m_enemies;
	Vector2f m_spawnIDStart;
	Vector2f m_spawnIDEnd;
	int MAX_ENEMIES;
	int CELL_COUNT;
	mutex* m_mutex;
	thread* m_setup;
	RenderTexture* m_texture;
};