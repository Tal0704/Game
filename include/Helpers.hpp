#pragma once
#include <SFML/Graphics/Shape.hpp>
#include <iostream>
#include <SFML/System/Vector2.hpp>

template <typename Ty>
std::ostream& operator<<(std::ostream& stream, const sf::Vector2<Ty>& v)
{
	stream << v.x << ", " << v.y;
	return stream;
}

template<typename type>
void centerOrigin(type shape)
{
	auto globalBounds = shape.getGlobalBounds();
	sf::Vector2f newOrigion;
	newOrigion.x = globalBounds.left + globalBounds.width / 2;
	newOrigion.y = globalBounds.top + globalBounds.height / 2;
	shape.setOrigin(newOrigion);
}

