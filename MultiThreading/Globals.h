#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <NodeData.h>

using namespace std;
using namespace sf;

const Vector2f SCREEN_SIZE = Vector2f(1000.0f, 1000.0f);
const int THIRTY_X = 30;
const int HUNDRED_X = 100;
const int THOUSAND_X = 1000;
const int THIRTY_GRID_ENEMIES = 5;
const int HUNDRED_GRID_ENEMIES = 50;
const int THOUSAND_GRID_ENEMIES = 10;

static float directDistance(sf::Vector2f t_vector1, sf::Vector2f t_vector2)
{
	return (t_vector2.x - t_vector1.x) + (t_vector2.y - t_vector1.y);
}

static int randomInt(int t_min, int t_max)
{
	if (t_max > t_min) {
		return (rand() % (t_max - t_min + 1)) + t_min;
	}
	return 1;
}