#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SpriteNode.hpp>

class Character
	: public SpriteNode
{
public:
	Character(const sf::Texture& texture);

	void move(float x, float y) { mSprite.move(x, y); }
	void move(const sf::Vector2f& offset) { mSprite.move(offset); }

	unsigned int getCategory() const;

private:

};
