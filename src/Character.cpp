#include <Character.hpp>

Character::Character(const sf::Texture& texture)
	: SpriteNode(texture)
{
}

unsigned int Character::getCategory() const
{
	return Category::Player;
}
