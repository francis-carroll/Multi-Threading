#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Globals.h>

class NodeData;

using namespace std;
using namespace sf;

class Enemy
{
public:
	Enemy(NodeData* t_node = nullptr);
	~Enemy();

	void setOccupyingTile(NodeData* t_node);
	void setPath(vector<NodeData*>* t_path);

	void update(Time t_dt);

	NodeData* getOccupiedNode();
private:
	NodeData* m_occupyingTile;
	bool m_finished;
	int m_current;
	vector<NodeData*>* m_path;
	float m_timer;
};