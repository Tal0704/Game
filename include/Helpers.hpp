#pragma once

#include <iostream>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

template <typename Ty>
std::ostream& operator<<(std::ostream& stream, const sf::Vector2<Ty>& v)
{
	stream << v.x << ", " << v.y;
	return stream;
}

void centerOrigin(sf::Sprite& shape);

void centerOrigin(sf::Text& text);
