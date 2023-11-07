#include <SpriteNode.hpp>
#include <iostream>

SpriteNode::SpriteNode(const sf::Texture& texture)
	: mSprite(texture)
{
}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& rect)
	: mSprite(texture, rect)
{
}

void SpriteNode::setPosition(float x, float y)
{
	mSprite.setPosition(x, y);
}

void SpriteNode::setPosition(const sf::Vector2f& position)
{
	mSprite.setPosition(position);
}

sf::FloatRect SpriteNode::getGlobalBounds() const
{
	return mSprite.getGlobalBounds();
}

sf::Vector2f SpriteNode::getPosition() const
{
	return mSprite.getPosition();
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->mSprite);
}
