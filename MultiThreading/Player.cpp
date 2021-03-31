#include "Player.h"
#include <NodeData.h>

Player::Player(NodeData* t_node) : 
	m_occupyingTile(t_node)
{
}

Player::~Player()
{
}

void Player::setOccupyingTile(NodeData* t_node)
{
	m_occupyingTile = t_node;
}

NodeData* Player::getOccupiedNode()
{
	return m_occupyingTile;
}
