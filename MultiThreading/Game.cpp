#include "Game.h"

Game::Game() :
	m_window(new RenderWindow(VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y, 32), "MultiThreaded AStar Ambush Sim", Style::Default)),
	m_player(new Player()),
	m_enemy(new Enemy())
{
	setup(GridSize::HundredX);
	m_player->setOccupyingTile(m_grid->getNodes()->at(0));
	m_enemy->setOccupyingTile(m_grid->getNodes()->at(10));
	m_enemy->setPath(AStar::astar(m_grid, m_player->getOccupiedNode(), m_enemy->getOccupiedNode()));
}

Game::~Game()
{
	delete m_grid;
	delete m_player;
	delete m_enemy;
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
		render();
	}
}

void Game::update(Time t_deltaTime)
{
	m_enemy->update(t_deltaTime);
}

void Game::render()
{
	m_window->clear();

	vector<NodeData*>* nodes = m_grid->getNodes();
	for (NodeData* n : *nodes)
	{
		if (n->getCellState() == CellState::Wall)
			m_shape.setFillColor(Color::Black);
		else if (n->getCellState() == CellState::Occupied)
			m_shape.setFillColor(Color::Red);
		else if (n->getCellState() == CellState::Path)
			m_shape.setFillColor(Color::Blue);
		else
			m_shape.setFillColor(Color::Green);

		m_shape.setPosition(n->getPosition());

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

	m_grid = new Grid(t_size);
	setupRender();
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
		break;
	case GridSize::HundredX:
		m_shape.setSize(Vector2f(SCREEN_SIZE.x / HUNDRED_X, SCREEN_SIZE.y / HUNDRED_X));
		m_shape.setOutlineThickness(1.0f);
		m_shape.setOutlineColor(Color::Black);
		break;
	case GridSize::ThousandX:
		m_shape.setSize(Vector2f(SCREEN_SIZE.x / THOUSAND_X, SCREEN_SIZE.y / THOUSAND_X));
		m_shape.setOutlineThickness(0.0f);
		break;
	default:
		break;
	}
}
