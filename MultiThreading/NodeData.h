#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <mutex>
#include <Globals.h>

using namespace std;
using namespace sf;

enum class CellState
{
	None,
	Wall,
	Path
};

class NodeData
{
public:
	NodeData(int t_index, Vector2f t_position, int t_enemyCount);
	~NodeData();

	void setCellState(CellState t_state);
	void addNeighbour(NodeData* t_node);
	void setTileWeight(int t_tileWeight);
	void setMarked(bool t_marked, int t_id);
	void setPrevious(NodeData* t_data, int t_id);
	void setOccupied(bool t_bool);
	void setPathCost(int t_pathCost, int t_id);
	void setHeuristic(float t_heuristic);

	Vector2f getPosition();
	CellState getCellState();
	vector<NodeData*>* getNeighbours();
	int getIndex();
	int getTileWeight();
	bool getMarked(int t_marked);
	NodeData* getPrevious(int t_id);
	bool getOccupied();
	int getPathCost(int t_id);
	vector<pair<int, int>>* getPathCosts();
	float getHeuristic();
	vector<pair<int, NodeData*>>* getPreviouss();
	vector<pair<int, bool>>* getMarkeds();
private:
	int m_index;
	Vector2f m_position;
	CellState m_cellState;
	vector<NodeData*>* m_neighbours;
	bool m_occupied;
	mutex m_mutex;
	vector<pair<int, int>>* m_pathCost;
	float m_heuristic;
	int m_tileWeight;
	vector<pair<int, NodeData*>>* m_previous;
	vector<pair<int, bool>>* m_marked;
};

struct CompareFn
{
	CompareFn(int t_id = -1) :
		m_id (t_id) {}

	float operator()(NodeData* node1, NodeData* node2)
	{
		return (node1->getPathCost(m_id) + node1->getHeuristic() + (node1->getTileWeight() * 5)) > (node2->getPathCost(m_id) + node2->getHeuristic() + (node2->getTileWeight() * 5));
	}
private:
	int m_id;
};