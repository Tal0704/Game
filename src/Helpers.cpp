#include <Helpers.hpp>

template<typename type>
void centerOrigin(type shape)
{
	auto globalBounds = shape.getGlobalBounds();
	sf::Vector2f newOrigion;
	newOrigion.x = globalBounds.left + globalBounds.width / 2;
	newOrigion.y = globalBounds.top + globalBounds.height / 2;
	shape.setOrigin(newOrigion);
}
