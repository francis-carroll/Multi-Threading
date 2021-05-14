#include "Enemy.h"
#include <NodeData.h>

Enemy::Enemy(int t_id, NodeData* t_node) :
    m_occupyingTile(t_node),
    m_path(new vector<NodeData*>()),
    m_finished(false),
    m_current(0),
    m_timer(0.0f),
    m_id(t_id),
    m_start(false)
{
}

Enemy::~Enemy()
{
    delete m_path;
}

void Enemy::setOccupyingTile(NodeData* t_node)
{
    m_occupyingTile = t_node;
    t_node->setOccupied(true);
}

void Enemy::setPath(Enemy* t_enemy, Grid* t_grid, NodeData* t_goal)
{
    AStar::astar(t_grid, t_goal, t_enemy->m_occupyingTile, t_enemy->getID(), t_enemy->m_path);
    t_enemy->m_current = t_enemy->m_path->size() - 1;
    t_enemy->m_start = true;
}

void Enemy::update(Time t_dt)
{
    m_timer += t_dt.asSeconds();
    moveEnemy();
}

NodeData* Enemy::getOccupiedNode()
{
    return m_occupyingTile;
}

int Enemy::getID()
{
    return m_id;
}

vector<NodeData*>* Enemy::getPath()
{
    return m_path;
}

bool Enemy::getStart()
{
    return m_start;
}

bool Enemy::checkIfFinished()
{
    if (m_path->size() == 1 && m_start)
    {
        m_occupyingTile->setOccupied(false);
        return true;
    }
    return false;
}

/// <summary>
/// Moves the enemy along a path, when a path becomes availble
/// </summary>
void Enemy::moveEnemy()
{
    if (m_current <= 0 && m_start)
    {
        m_finished = true;
    }

    if (!m_finished && m_start)
    {
        if (m_timer > 1.0f)
        {
            m_path->at(m_current)->setOccupied(false);
        }
        if (m_timer >= 0.5f)
        {
            if (!m_path->at(m_current - 1)->getOccupied())
            {
                m_path->at(m_current)->setOccupied(false);
                m_current--;
                m_path->at(m_current)->setOccupied(true);
                m_occupyingTile = m_path->at(m_current);
                m_path->pop_back();
                m_timer = 0.0f;
            }
        }
    }
}
