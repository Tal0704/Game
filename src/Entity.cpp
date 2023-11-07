#include <Entity.hpp>

void Entity::setVelocity(const sf::Vector2f& speed)
{
	this->mVelocity = speed;
}

void Entity::setVelocity(float x, float y)
{
	this->setVelocity(sf::Vector2f(x, y));
}

sf::Vector2f Entity::getVelocity() const
{
	return this->mVelocity;
}

void Entity::updateCurrent(const sf::Time& deltaTime)
{
}