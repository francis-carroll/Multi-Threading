#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

enum class CellState
{
	None,
	Occupied,
	Wall,
	Path
};

class NodeData
{
public:
	NodeData(int t_index, Vector2f t_position);
	~NodeData();

	void setCellState(CellState t_state);
	void addNeighbour(NodeData* t_node);
	void setTileWeight(int t_tileWeight);
	void setMarked(bool t_marked);
	void setPrevious(NodeData* t_data);

	Vector2f getPosition();
	CellState getCellState();
	vector<NodeData*>* getNeighbours();
	int getIndex();
	int getTileWeight();
	bool getMarked();
	NodeData* getPrevious();

	int m_pathCost;
	int m_heuristic;
	int m_tileWeight;
private:
	int m_index;
	Vector2f m_position;
	CellState m_cellState;
	vector<NodeData*>* m_neighbours;
	NodeData* m_previous;
	bool m_marked;
};

struct CompareFn
{
	float operator()(NodeData const* node1, NodeData const* node2)
	{
		return (node1->m_pathCost + node1->m_heuristic + (node1->m_tileWeight * 5)) > (node2->m_pathCost + node2->m_heuristic + (node2->m_tileWeight * 5));
	}
};