#include "Game.h"

Game::Game() :
	m_window(new RenderWindow(VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y, 32), "MultiThreaded AStar Ambush Sim", Style::Default)),
	m_player(new Player()),
	m_enemies(nullptr),
	m_view(View(Vector2f(SCREEN_SIZE.x / 2.0f, SCREEN_SIZE.x / 2.0f), SCREEN_SIZE)),
	m_tp(new ThreadPool)
{
	m_window->setView(m_view);
	setupFont();
	setup(GridSize::HundredX);
}

Game::~Game()
{
	delete m_tp;
	delete m_player;
	for (Enemy* e : *m_enemies)
		delete e;
	delete m_enemies;
	delete m_grid;
}

void Game::run()
{
	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;
	m_timePerFrame = seconds(SIXTY_GAMETICK);
	float fps = 0;
	Time time = seconds(0);

	while (m_window->isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.getElapsedTime();
		time += clock.getElapsedTime();

		if (timeSinceLastUpdate > m_timePerFrame && fps < MAX_FPS)
		{
			processEvents();
			update(m_timePerFrame);
			timeSinceLastUpdate -= m_timePerFrame;
			clock.restart();
			fps++;
		}
		if (time.asSeconds() >= 1.0f)
		{
			time -= seconds(1);
			m_gameTicks.setString("GameTick: " + to_string(fps));
			fps = 0;
		}
		render();
	}
}

void Game::update(Time t_deltaTime)
{
	for(Enemy* e : *m_enemies)
		e->update(t_deltaTime);

	m_enemies->erase(remove_if(m_enemies->begin(),
		m_enemies->end(),
		[&](Enemy* e)->bool {return (e->checkIfFinished()); }),
		m_enemies->end());

	limitZoom();
	limitMovement();
	m_window->setView(m_view);
}

void Game::render()
{
	srand((unsigned)time(nullptr));
	m_window->clear();

	Sprite s(m_grid->getTexture()->getTexture());
	m_window->draw(s);

	for (Enemy* e : *m_enemies)
	{
		m_shape.setFillColor(Color::Blue);
		m_shape.setPosition(e->getOccupiedNode()->getPosition());
		m_window->draw(m_shape);
	}

	m_shape.setFillColor(Color::Red);
	m_shape.setPosition(m_player->getOccupiedNode()->getPosition());
	m_window->draw(m_shape);

	m_window->draw(m_gameTicks);

	m_window->display();
}

void Game::processEvents()
{
	Event event;
	while (m_window->pollEvent(event))
	{
		if (event.type == event.KeyPressed)
		{
			if (event.key.code == Keyboard::Num1 && !m_tp->getTasks().size() != 0)
				setup(GridSize::ThirtyX);
			else if (event.key.code == Keyboard::Num2 && !m_tp->getTasks().size() != 0)
				setup(GridSize::HundredX);
			else if (event.key.code == Keyboard::Num3 && !m_tp->getTasks().size() != 0)
				setup(GridSize::ThousandX);

			if (event.key.code == Keyboard::Num4)
				m_timePerFrame = seconds(THIRTY_GAMETICK);
			else if(event.key.code == Keyboard::Num5)
				m_timePerFrame = seconds(SIXTY_GAMETICK);
			else if(event.key.code == Keyboard::Num6)
				m_timePerFrame = seconds(ONE_TWENTY_GAMETICK);
			else if (event.key.code == Keyboard::Num7)
				m_timePerFrame = seconds(NO_GAMETICK);
			else if (event.key.code == Keyboard::Num8)
				m_timePerFrame = seconds(ONE_GAMETICK);

			if (event.key.code == Keyboard::Up)
				m_view.move(0.0f, -MOVE_SPEED);
			else if(event.key.code == Keyboard::Down)
				m_view.move(0.0f, MOVE_SPEED);
			else if(event.key.code == Keyboard::Left)
				m_view.move(-MOVE_SPEED, 0.0f);
			else if(event.key.code == Keyboard::Right)
				m_view.move(MOVE_SPEED, 0.0f);

			if (event.key.code == Keyboard::R)
			{
				m_grid->setupRenderTexure(m_shape);
			}

			if (event.key.code == Keyboard::Escape)
			{
				m_window->close();
			}
		}

		if (event.type == Event::MouseWheelMoved)
		{
			m_view.zoom(1 - (ZOOM_SPEED / event.mouseWheel.delta));
		}
	}
}

void Game::setupFont()
{
	if (!m_font.loadFromFile("resources/fonts/default.ttf"))
		cout << "Coulnt load font" << endl;
	m_gameTicks.setFont(m_font);
	m_gameTicks.setCharacterSize(40);
	m_gameTicks.setOutlineColor(Color::Black);
	m_gameTicks.setOutlineThickness(2.0f);
	m_gameTicks.setFillColor(Color::White);
	m_gameTicks.setPosition(Vector2f(300.0f, 10.0f));
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
	setupRender();
	initPlayer();
	m_grid->setupRenderTexure(m_shape);
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
		MAX_ENEMIES = THIRTY_GRID_ENEMIES;
		CELL_COUNT = THIRTY_X;
		m_enemySpawnIDStart = Vector2i(20, 20);
		m_enemySpawnIDEnd = Vector2i(25, 25);
		m_playerSpawnIDStart = Vector2i(5, 5);
		m_playerSpawnIDEnd = Vector2i(10, 10);
		break;
	case GridSize::HundredX:
		m_shape.setSize(Vector2f(SCREEN_SIZE.x / HUNDRED_X, SCREEN_SIZE.y / HUNDRED_X));
		m_shape.setOutlineThickness(1.0f);
		m_shape.setOutlineColor(Color::Black);
		MAX_ENEMIES = HUNDRED_GRID_ENEMIES;
		CELL_COUNT = HUNDRED_X;
		m_enemySpawnIDStart = Vector2i(65, 65);
		m_enemySpawnIDEnd = Vector2i(80, 80);
		m_playerSpawnIDStart = Vector2i(10, 10);
		m_playerSpawnIDEnd = Vector2i(15, 15);
		break;
	case GridSize::ThousandX:
		m_shape.setSize(Vector2f(SCREEN_SIZE.x / THOUSAND_X, SCREEN_SIZE.y / THOUSAND_X));
		m_shape.setOutlineThickness(0.0f);
		MAX_ENEMIES = THOUSAND_GRID_ENEMIES;
		CELL_COUNT = THOUSAND_X;
		m_enemySpawnIDStart = Vector2i(700, 700);
		m_enemySpawnIDEnd = Vector2i(800, 800);
		m_playerSpawnIDStart = Vector2i(10, 10);
		m_playerSpawnIDEnd = Vector2i(15, 15);
		break;
	default:
		break;
	}
}

void Game::initEnemies()
{
	for (int i = 0; i < MAX_ENEMIES;)
	{
		Vector2i rowCol = Vector2i(randomInt(m_enemySpawnIDStart.x, m_enemySpawnIDEnd.x), randomInt(m_enemySpawnIDStart.y, m_enemySpawnIDEnd.y));
		if (m_grid->getNodes()->at(m_grid->getIndex(rowCol.x, rowCol.y, CELL_COUNT))->getCellState() != CellState::Wall)
		{
			m_enemies->push_back(createEnemy(m_grid->getIndex(rowCol.x, rowCol.y, CELL_COUNT), i));
			i++;
		}
		else
		{
			rowCol = Vector2i(randomInt(m_enemySpawnIDStart.x,m_enemySpawnIDEnd.x), randomInt(m_enemySpawnIDStart.y, m_enemySpawnIDEnd.y));
		}
	}

	for (Enemy* e : *m_enemies)
	{
		m_tp->addTask(bind(&Enemy::setPath,e, m_grid, m_player->getOccupiedNode()));
	}
}

void Game::initPlayer()
{
	for (int i = 0; i < 1;)
	{
		Vector2i rowCol = Vector2i(randomInt(m_playerSpawnIDStart.x, m_playerSpawnIDEnd.x), randomInt(m_playerSpawnIDStart.y, m_playerSpawnIDEnd.y));
		if (m_grid->getNodes()->at(m_grid->getIndex(rowCol.x, rowCol.y, CELL_COUNT))->getCellState() != CellState::Wall)
		{
			m_player->setOccupyingTile(m_grid->getNodes()->at(m_grid->getIndex(rowCol.x, rowCol.y, CELL_COUNT)));
			i++;
		}
		else
		{
			rowCol = Vector2i(randomInt(m_playerSpawnIDStart.x, m_playerSpawnIDEnd.x), randomInt(m_playerSpawnIDStart.y, m_playerSpawnIDEnd.y));
		}
	}
}

Enemy* Game::createEnemy(int t_tileID, int t_id)
{
	Enemy* e = new Enemy(t_id);
	e->setOccupyingTile(m_grid->getNodes()->at(t_tileID));
	return e;
}

void Game::limitMovement()
{
	if (m_view.getCenter().x < ((SCREEN_SIZE.x / 2.0f) * (m_view.getSize().x / SCREEN_SIZE.x)))
		m_view.setCenter(Vector2f((SCREEN_SIZE.x / 2.0f) * (m_view.getSize().x / SCREEN_SIZE.x), m_view.getCenter().y));
	else if (m_view.getCenter().y < ((SCREEN_SIZE.y / 2.0f) * (m_view.getSize().y / SCREEN_SIZE.y)))
		m_view.setCenter(Vector2f(m_view.getCenter().x, ((SCREEN_SIZE.y / 2.0f) * (m_view.getSize().y / SCREEN_SIZE.y))));
	else if (m_view.getCenter().x > SCREEN_SIZE.x - ((SCREEN_SIZE.x / 2.0f) * (m_view.getSize().x / SCREEN_SIZE.x)))
		m_view.setCenter(Vector2f(SCREEN_SIZE.x - ((SCREEN_SIZE.x / 2.0f) * (m_view.getSize().x / SCREEN_SIZE.x)), m_view.getCenter().y));
	else if (m_view.getCenter().y > SCREEN_SIZE.y - ((SCREEN_SIZE.y / 2.0f) * (m_view.getSize().y / SCREEN_SIZE.y)))
		m_view.setCenter(Vector2f(m_view.getCenter().x, SCREEN_SIZE.y - ((SCREEN_SIZE.y / 2.0f) * (m_view.getSize().y / SCREEN_SIZE.y))));
}

void Game::limitZoom()
{
	if (m_view.getSize().x <= MAX_ZOOM_IN)
		m_view.setSize(Vector2f(MAX_ZOOM_IN, m_view.getSize().y));
	else if (m_view.getSize().x >= SCREEN_SIZE.x)
		m_view.setSize(Vector2f(SCREEN_SIZE.x, m_view.getSize().y));
	if (m_view.getSize().y <= MAX_ZOOM_IN)
		m_view.setSize(Vector2f(m_view.getSize().x, MAX_ZOOM_IN));
	else if (m_view.getSize().y >= SCREEN_SIZE.y)
		m_view.setSize(Vector2f(m_view.getSize().x, SCREEN_SIZE.y));
}
