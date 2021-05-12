#include "Game.h"

Game::Game() :
	m_window(new RenderWindow(VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y, 32), "MultiThreaded AStar Ambush Sim", Style::Default)),
	m_player(new Player()),
	m_enemies(nullptr),
	m_mutex(new mutex),
	m_texture(new RenderTexture)
{
	setup(GridSize::HundredX);
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
	float fps = 0;
	Time time = seconds(0);

	while (m_window->isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.getElapsedTime();
		time += clock.getElapsedTime();

		if (timeSinceLastUpdate > timePerFrame)
		{
			processEvents();
			update(timePerFrame);
			timeSinceLastUpdate -= timePerFrame;
			clock.restart();
			fps++;
		}
		if (time.asSeconds() >= 1.0f)
		{
			cout << fps << endl;
			time -= seconds(1);
			fps = 0;
		}
		render();
	}
}

void Game::update(Time t_deltaTime)
{
	for(Enemy* e : *m_enemies)
		e->update(t_deltaTime);
}

void Game::render()
{
	srand((unsigned)time(nullptr));
	m_window->clear();
	//t_game->renderGrid(t_game);
	Sprite s(m_texture->getTexture());
	m_window->draw(s);

	for (Enemy* e : *m_enemies)
	{
		//m_shape.setFillColor(Color(rand()%255, rand() % 255, rand() % 255));
		m_shape.setFillColor(Color::Blue);
		m_shape.setPosition(e->getOccupiedNode()->getPosition());
		m_window->draw(m_shape);
	}

	m_window->display();
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
				setup(GridSize::ThirtyX);
			else if (event.key.code == Keyboard::Num2)
				setup(GridSize::HundredX);
			else if (event.key.code == Keyboard::Num3)
				setup(GridSize::ThousandX);

			if(event.key.code == Keyboard::Escape)
				m_window->close();
		}
	}
}

void Game::setup(GridSize t_size)
{
	if (m_grid != nullptr)
		delete m_grid;
	if (m_enemies != nullptr)
	{
		for (Enemy* e : *m_enemies)
			delete e;
		delete m_enemies;
	}

	m_grid = new Grid(t_size);
	m_enemies = new vector<Enemy*>();
	m_player->setOccupyingTile(m_grid->getNodes()->at(0));
	setupRender();
	setupRenderTexure();
	initEnemies();
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
		MAX_ENEMIES = 50;
		CELL_COUNT = HUNDRED_X;
		break;
	case GridSize::ThousandX:
		m_shape.setSize(Vector2f(SCREEN_SIZE.x / THOUSAND_X, SCREEN_SIZE.y / THOUSAND_X));
		m_shape.setOutlineThickness(0.0f);
		m_spawnIDStart = Vector2f(700, 700);
		m_spawnIDEnd = Vector2f(800, 800);
		MAX_ENEMIES = 200;
		CELL_COUNT = THOUSAND_X;
		break;
	default:
		break;
	}
}

void Game::renderGrid()
{
	vector<NodeData*>* nodes = m_grid->getNodes();
	for (NodeData* n : *nodes)
	{
		if (n->getCellState() == CellState::Wall)
			m_shape.setFillColor(Color::Black);
		else if (n->getCellState() == CellState::Occupied)
			m_shape.setFillColor(Color::Red);
		else if (n->getCellState() == CellState::Path)
			m_shape.setFillColor(Color::Yellow);
		else
			m_shape.setFillColor(Color(rand() % 255, rand() % 255, rand() % 255));
			//t_game->m_shape.setFillColor(Color::Green);
		
		m_shape.setPosition(n->getPosition());

		m_window->draw(m_shape);
	}
}

void Game::initEnemies()
{
	for (int i = 0; i < MAX_ENEMIES;)
	{
		Vector2i rowCol = Vector2i(randomInt(m_spawnIDStart.x, m_spawnIDEnd.x), randomInt(m_spawnIDStart.y, m_spawnIDEnd.y));
		if (m_grid->getNodes()->at(m_grid->getIndex(rowCol.x, rowCol.y, CELL_COUNT))->getCellState() != CellState::Wall)
		{
			m_enemies->push_back(createEnemy(m_grid->getIndex(rowCol.x, rowCol.y, CELL_COUNT), i));
			i++;
		}
		else
		{
			rowCol = Vector2i(randomInt(m_spawnIDStart.x,m_spawnIDEnd.x), randomInt(m_spawnIDStart.y, m_spawnIDEnd.y));
		}
	}
	for (Enemy* e : *m_enemies)
	{
		//m_tp.addTask([&] {Enemy::setPath(e, m_grid, m_player->getOccupiedNode()); });
		m_tp.addTask(bind(&Enemy::setPath,e, m_grid, m_player->getOccupiedNode()));
	}
	setupRenderTexure();
}

Enemy* Game::createEnemy(int t_tileID, int t_id)
{
	Enemy* e = new Enemy(t_id);
	e->setOccupyingTile(m_grid->getNodes()->at(t_tileID));
	return e;
}

void Game::setupRenderTexure()
{
	m_texture->create(SCREEN_SIZE.x, SCREEN_SIZE.y);

	m_texture->clear();

	vector<NodeData*>* nodes = m_grid->getNodes();
	for (NodeData* n : *nodes)
	{
		if (n->getCellState() == CellState::Wall)
			m_shape.setFillColor(Color::Black);
		else if (n->getCellState() == CellState::Occupied)
			m_shape.setFillColor(Color::Red);
		else if (n->getCellState() == CellState::Path)
			m_shape.setFillColor(Color::Yellow);
		else
			//t_game->m_shape.setFillColor(Color(rand() % 255, rand() % 255, rand() % 255));
			m_shape.setFillColor(Color::Green);

		m_shape.setPosition(n->getPosition());

		m_texture->draw(m_shape);
	}

	m_texture->display();
}
