#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

const Vector2f SCREEN_SIZE = Vector2f(1000.0f, 1000.0f);
const int THIRTY_X = 30;
const int HUNDRED_X = 100;
const int THOUSAND_X = 1000;

static float directDistance(sf::Vector2f t_vector1, sf::Vector2f t_vector2)
{
	return (t_vector2.x - t_vector1.x) + (t_vector2.y - t_vector1.y);
}