#include <Entity.h>

#include <cassert>

Entity::Entity(int hitpoints)
    : m_velocity(),
      m_hitPoints(hitpoints),
      m_positionCollision(-9999)
{
}


void Entity::setVelocity(sf::Vector2f velocity)
{
    m_velocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
    m_velocity.x = vx;
    m_velocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
    return m_velocity;
}

void Entity::accelerate(sf::Vector2f velocity)
{
    m_velocity += velocity;
}

void Entity::accelerate(float vx, float vy)
{
    m_velocity.x += vx;
    m_velocity.y += vy;
}

int Entity::getHitpoints() const
{
    return m_hitPoints;
}

void Entity::setHitpoints(int points)
{
    assert(points > 0);
    m_hitPoints = points;
}

void Entity::repair(int points)
{
    assert(points > 0);

    m_hitPoints += points;
}

void Entity::damage(int points)
{
    assert(points > 0);

    m_hitPoints -= points;
}

void Entity::destroy()
{
    m_hitPoints = 0;
}

void Entity::remove()
{
    destroy();
}

bool Entity::isDestroyed() const
{
    return m_hitPoints <= 0;
}

void Entity::updateCurrent(sf::Time dt, CommandQueue&)
{
    move(m_velocity * dt.asSeconds()); //move inherit of transformable class. is the shortcut for getPosition()+offset()
}

// Calcul le numéro de la grille de collision
void Entity::checkNodePosition(SceneNode& node, const std::vector<sf::FloatRect>& virtualRectCollision)
{
/*
        Recalcule la position dans la grille de
        colllision si l'objet a bougé ou n'est pas
        initialisé
*/
        if (m_positionCollision == -9999
            || (m_velocity.x != 0.0 || m_velocity.y != 0.0))
        {
            unsigned int op(0);

/*
            Vérifie si l'objet est dans la grille du
            dessous ou dessus.
            Optimisable en rajoutant l'ensemble des
            cases adjacentes (sur les côté) mais
            nécessite de conaitre le nombre de
            case en X et Y.
*/
            op = m_positionCollision-2;
            for (int it = m_positionCollision-1; it <= m_positionCollision+1 ; ++it)
            {
                op += 1;
                // Regarde si la grille de collision contient le point. Plus optimisé que la fonction intersect.
                if (virtualRectCollision[it].contains(getWorldPosition().x,getWorldPosition().y))
                {
//                std::cout << "node.getWorldPosition().x = " << node.getWorldPosition().x << std::endl ;
//                std::cout << "node.getWorldPosition().y = " << node.getWorldPosition().y << std::endl ;
                    m_positionCollision = op;
                    return;
                }
            }
/*
            Sinon on regarde les autres cases
*/
            op=0;
            for (auto it = virtualRectCollision.cbegin(); it != virtualRectCollision.cend(); ++it)
            {
                op += 1;
                // Regarde si la grille de collision contient le point. Plus optimisé que la fonction intersect.
                if (it->contains(getWorldPosition().x,getWorldPosition().y))
                {
//                std::cout << "node.getWorldPosition().x = " << node.getWorldPosition().x << std::endl ;
//                std::cout << "node.getWorldPosition().y = " << node.getWorldPosition().y << std::endl ;
                    m_positionCollision = op;
                    return;
                }
            }
        }


}

int Entity::getPositionCollision() const
{
    return m_positionCollision;
}
