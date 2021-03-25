#include "Game.h"

Game::Game() :
	m_window(new RenderWindow(VideoMode(1000, 1000, 32), "MultiThreaded AStar Ambush Sim", Style::Default))
{
	setup();
}

Game::~Game()
{
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
}

void Game::render()
{
	m_window->clear();

	vector<NodeData*> nodes = grid->getNodes();
	for (NodeData* n : nodes)
	{
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
	}
}

void Game::setup()
{
	grid = new Grid(GridSize::ThirtyX, SIZE);
	setupRender();
}

void Game::setupRender()
{
	//m_shape.setOutlineThickness(1.0f);
	//m_shape.setOutlineColor(Color::Black);
	m_shape.setFillColor(Color::Green);
	m_shape.setSize(SIZE);
}
