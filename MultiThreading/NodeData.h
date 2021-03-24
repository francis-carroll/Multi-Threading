#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;


class NodeData
{
public:
	NodeData(int t_index, Vector2f t_position);
	~NodeData();
private:
	int m_index;
	Vector2f m_position;
	bool m_occupied;
	bool m_marked;

};