#include "Game.h"

Game::Game() :
	m_window(new RenderWindow(VideoMode(800, 800, 32), "MultiThreaded AStar Ambush Sim", Style::Default))
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
	Time timePerFrame = seconds(1.f / 60.f); // 60 fps

	while (m_window->isOpen())
	{
		processEvents();                                //As many as possible
		timeSinceLastUpdate += clock.getElapsedTime();

		if (timeSinceLastUpdate > timePerFrame)
		{
			processEvents();                            //At least 60 fps
			update(timePerFrame);                        //60 fps
			timeSinceLastUpdate -= timePerFrame;
			clock.restart();
		}
		render();                                        //As many as possible
	}
}

void Game::update(Time t_deltaTime)
{
}

void Game::render()
{
	m_window->clear();

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
	grid = new Grid(GridSize::ThirtyX);
}