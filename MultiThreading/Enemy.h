#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Grid.h>
#include <Globals.h>
#include <AStar.h>

class NodeData;

using namespace std;
using namespace sf;

class Enemy
{
public:
	Enemy(int t_id, NodeData* t_node = nullptr);
	~Enemy();

	void setOccupyingTile(NodeData* t_node);
	static void setPath(Enemy* t_enemy, Grid* t_grid, NodeData* t_goal);

	void update(Time t_dt);

	NodeData* getOccupiedNode();
	int getID();
private:
	NodeData* m_occupyingTile;
	bool m_finished;
	int m_current;
	vector<NodeData*>* m_path;
	float m_timer;
	int m_id;
	bool m_start;
};