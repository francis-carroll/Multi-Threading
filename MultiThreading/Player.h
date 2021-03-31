#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Globals.h>

class NodeData;

using namespace std;
using namespace sf;

class Player
{
public:
	Player(NodeData* t_node = nullptr);
	~Player();

	void setOccupyingTile(NodeData* t_node);

	NodeData* getOccupiedNode();
private:
	NodeData* m_occupyingTile;
};

