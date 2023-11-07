#pragma once
#include <SceneNode.hpp>

class Entity
	: public SceneNode
{
public:
	void setVelocity(float x, float y);
	void setVelocity(const sf::Vector2f& v);

	sf::Vector2f getVelocity() const;

private:
	sf::Vector2f mVelocity;
	virtual void updateCurrent(const sf::Time& dt);
};
