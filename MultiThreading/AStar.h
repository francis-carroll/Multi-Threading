#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Globals.h>
#include <Grid.h>

using namespace std;
using namespace sf;

class AStar
{
public:
	AStar();
	~AStar();
	static void astar(Grid* t_grid);
private:
};