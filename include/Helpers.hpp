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
	auto localBounds = shape.getLocalBounds();
	sf::Vector2f newOrigion;
	newOrigion.x = localBounds.left + localBounds.width / 2;
	newOrigion.y = localBounds.top + localBounds.height / 2;
	shape.setOrigin(newOrigion);
}

