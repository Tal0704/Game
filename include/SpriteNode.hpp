#pragma once
#include <SceneNode.hpp>

class SpriteNode : public SceneNode
{
public:
	explicit SpriteNode(const sf::Texture& texture);
	SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);
	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f& position);

	sf::FloatRect getGlobalBounds() const;


	sf::Vector2f getPosition() const;

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	sf::Sprite mSprite;

};