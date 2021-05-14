#pragma once

#include <SFML/Graphics.hpp>
#include <Globals.h>
#include <Grid.h>
#include <Player.h>
#include <AStar.h>
#include <Enemy.h>
#include <thread>
#include <mutex>
#include <ThreadPool.h>

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

	void setupFont();
	void setup(GridSize t_size);
	void setupRender();
	void initEnemies();
	void initPlayer();
	Enemy* createEnemy(int t_tileID, int t_id);
	void limitMovement();
	void limitZoom();

	RenderWindow* m_window;
	Grid* m_grid;
	RectangleShape m_shape;
	Player* m_player;
	vector<Enemy*>* m_enemies;
	Vector2i m_enemySpawnIDStart;
	Vector2i m_enemySpawnIDEnd;
	Vector2i m_playerSpawnIDStart;
	Vector2i m_playerSpawnIDEnd;
	int MAX_ENEMIES;
	int CELL_COUNT;
	ThreadPool* m_tp;
	View m_view;
	Text m_fps;
	Font m_font;
	Time m_timePerFrame;
};