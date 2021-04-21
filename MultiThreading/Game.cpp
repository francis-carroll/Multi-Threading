#include "Game.h"

Game::Game() :
	m_window(new RenderWindow(VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y, 32), "MultiThreaded AStar Ambush Sim", Style::Default)),
	m_player(new Player()),
	m_enemies(nullptr),
	m_mutex(new mutex),
	m_texture(new RenderTexture)
{
	Game::setup(this, GridSize::HundredX);
	/*m_setup = new thread(&Game::setup, this, GridSize::ThousandX);
	m_setup->join();*/
	m_window->setActive(false);
}

Game::~Game()
{
	delete m_grid;
	delete m_player;
	delete m_enemies;
	delete m_window;
}

void Game::run()
{
	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;
	Time timePerFrame = seconds(1.f / 60.f);

	while (m_window->isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.getElapsedTime();

		if (timeSinceLastUpdate > timePerFrame)
		{
			processEvents();
			update(timePerFrame);
			timeSinceLastUpdate -= timePerFrame;
			clock.restart();
		}
		render(this);
	}
}

void Game::update(Time t_deltaTime)
{
	for(Enemy* e : *m_enemies)
		e->update(t_deltaTime);
}

void Game::render(Game* t_game)
{
	srand((unsigned)time(nullptr));
	t_game->m_window->clear();

	//t_game->renderGrid(t_game);
	Sprite s(t_game->m_texture->getTexture());
	t_game->m_window->draw(s);

	for (Enemy* e : *t_game->m_enemies)
	{
		//m_shape.setFillColor(Color(rand()%255, rand() % 255, rand() % 255));
		t_game->m_shape.setFillColor(Color::Blue);
		t_game->m_shape.setPosition(e->getOccupiedNode()->getPosition());
		t_game->m_window->draw(t_game->m_shape);
	}

	t_game->m_window->display();
}

void Game::processEvents()
{
	Event event;
	while (m_window->pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			m_window->close();
		}

		if (event.type == event.KeyPressed)
		{
			if (event.key.code == Keyboard::Num1)
				setup(this, GridSize::ThirtyX);
			else if (event.key.code == Keyboard::Num2)
				setup(this, GridSize::HundredX);
			else if (event.key.code == Keyboard::Num3)
				setup(this, GridSize::ThousandX);

			if(event.key.code == Keyboard::Escape)
				m_window->close();
		}
	}
}

void Game::setup(Game* t_game, GridSize t_size)
{
	if (t_game->m_grid != nullptr)
		delete t_game->m_grid;
	if (t_game->m_enemies != nullptr)
	{
		for (Enemy* e : *t_game->m_enemies)
			delete e;
		delete t_game->m_enemies;
	}

	t_game->m_grid = new Grid(t_size);
	t_game->m_enemies = new vector<Enemy*>();
	t_game->m_player->setOccupyingTile(t_game->m_grid->getNodes()->at(0));
	t_game->setupRender();
	t_game->setupRenderTexure(t_game);
	std::thread t(&Game::initEnemies, t_game);
	t.join();
}

void Game::setupRender()
{
	m_shape.setFillColor(Color::Green);
	switch (m_grid->getGridSize())
	{
	case GridSize::ThirtyX:
		m_shape.setSize(Vector2f(SCREEN_SIZE.x / THIRTY_X, SCREEN_SIZE.y / THIRTY_X));
		m_shape.setOutlineThickness(1.0f);
		m_shape.setOutlineColor(Color::Black);
		m_spawnIDStart = Vector2f(20, 20);
		m_spawnIDEnd = Vector2f(25, 25);
		MAX_ENEMIES = 5;
		CELL_COUNT = THIRTY_X;
		break;
	case GridSize::HundredX:
		m_shape.setSize(Vector2f(SCREEN_SIZE.x / HUNDRED_X, SCREEN_SIZE.y / HUNDRED_X));
		m_shape.setOutlineThickness(1.0f);
		m_shape.setOutlineColor(Color::Black);
		m_spawnIDStart = Vector2f(65, 65);
		m_spawnIDEnd = Vector2f(80, 80);
		MAX_ENEMIES = 200;
		CELL_COUNT = HUNDRED_X;
		break;
	case GridSize::ThousandX:
		m_shape.setSize(Vector2f(SCREEN_SIZE.x / THOUSAND_X, SCREEN_SIZE.y / THOUSAND_X));
		m_shape.setOutlineThickness(0.0f);
		m_spawnIDStart = Vector2f(700, 700);
		m_spawnIDEnd = Vector2f(800, 800);
		MAX_ENEMIES = 10;
		CELL_COUNT = THOUSAND_X;
		break;
	default:
		break;
	}
}

void Game::renderGrid(Game* t_game)
{
	//vector<NodeData*>* nodes = t_game->m_grid->getNodes();
	//for (NodeData* n : *nodes)
	//{
	//	t_game->m_mutex->lock();
	//	if (n->getCellState() == CellState::Wall)
	//		t_game->m_shape.setFillColor(Color::Black);
	//	else if (n->getCellState() == CellState::Occupied)
	//		t_game->m_shape.setFillColor(Color::Red);
	//	else if (n->getCellState() == CellState::Path)
	//		t_game->m_shape.setFillColor(Color::Yellow);
	//	else
	//		t_game->m_shape.setFillColor(Color(rand() % 255, rand() % 255, rand() % 255));
	//		//t_game->m_shape.setFillColor(Color::Green);
	//	
	//	t_game->m_shape.setPosition(n->getPosition());

	//	t_game->m_window->draw(t_game->m_shape);
	//	t_game->m_mutex->unlock();
	//}
}

void Game::initEnemies(Game* t_game)
{
	for (int i = 0; i < t_game->MAX_ENEMIES;)
	{
		Vector2i rowCol = Vector2i(randomInt(t_game->m_spawnIDStart.x, t_game->m_spawnIDEnd.x), randomInt(t_game->m_spawnIDStart.y, t_game->m_spawnIDEnd.y));
		if (t_game->m_grid->getNodes()->at(t_game->m_grid->getIndex(rowCol.x, rowCol.y, t_game->CELL_COUNT))->getCellState() != CellState::Wall)
		{
			t_game->m_enemies->push_back(t_game->createEnemy(t_game->m_grid->getIndex(rowCol.x, rowCol.y, t_game->CELL_COUNT)));
			i++;
		}
		else
		{
			rowCol = Vector2i(randomInt(t_game->m_spawnIDStart.x, t_game->m_spawnIDEnd.x), randomInt(t_game->m_spawnIDStart.y, t_game->m_spawnIDEnd.y));
		}
	}
	setupRenderTexure(t_game);
}

Enemy* Game::createEnemy(int t_tileID)
{
	Enemy* e = new Enemy();
	e->setOccupyingTile(m_grid->getNodes()->at(t_tileID));
	e->setPath(AStar::astar(m_grid, m_player->getOccupiedNode(), e->getOccupiedNode()));
	return e;
}

void Game::setupRenderTexure(Game* t_game)
{
	t_game->m_texture->create(SCREEN_SIZE.x, SCREEN_SIZE.y);

	t_game->m_texture->clear();

	vector<NodeData*>* nodes = t_game->m_grid->getNodes();
	for (NodeData* n : *nodes)
	{
		if (n->getCellState() == CellState::Wall)
			t_game->m_shape.setFillColor(Color::Black);
		else if (n->getCellState() == CellState::Occupied)
			t_game->m_shape.setFillColor(Color::Red);
		else if (n->getCellState() == CellState::Path)
			t_game->m_shape.setFillColor(Color::Yellow);
		else
			//t_game->m_shape.setFillColor(Color(rand() % 255, rand() % 255, rand() % 255));
			t_game->m_shape.setFillColor(Color::Green);

		t_game->m_shape.setPosition(n->getPosition());

		t_game->m_texture->draw(t_game->m_shape);
	}

	t_game->m_texture->display();
}
