#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Globals.h>
#include <queue>
#include <Grid.h>
#include <math.h>

using namespace std;
using namespace sf;

class AStar
{
public:
	static vector<NodeData*>* astar(Grid* t_grid, NodeData* t_player, NodeData* t_enemy);
	static float calculateHeuristic(NodeData* t_goal, NodeData* t_current, int t_cellCount);
	static vector<NodeData*>* constructPath(NodeData* t_goal);
};