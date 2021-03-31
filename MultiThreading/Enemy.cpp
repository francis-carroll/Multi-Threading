#include "Enemy.h"
#include <NodeData.h>

Enemy::Enemy(NodeData* t_node) :
    m_occupyingTile(t_node),
    m_path(new vector<NodeData*>()),
    m_finished(false),
    m_current(0),
    m_timer(0.0f)
{
}

Enemy::~Enemy()
{
}

void Enemy::setOccupyingTile(NodeData* t_node)
{
    m_occupyingTile = t_node;
    m_occupyingTile->setCellState(CellState::Occupied);
}

void Enemy::setPath(vector<NodeData*>* t_path)
{
    m_path = t_path;
    m_current = m_path->size() - 1;
}

void Enemy::update(Time t_dt)
{
    m_timer += t_dt.asSeconds();
    if (m_current <= 0)
    {
        m_finished = true;
    }

    if (!m_finished)
    {
        if (m_timer >= 0.01f)
        {
            m_path->at(m_current)->setCellState(CellState::None);
            m_current--;
            m_path->at(m_current)->setCellState(CellState::Occupied);
            m_occupyingTile = m_path->at(m_current);
            m_timer = 0.0f;
        }
    }
}

NodeData* Enemy::getOccupiedNode()
{
    return m_occupyingTile;
}
