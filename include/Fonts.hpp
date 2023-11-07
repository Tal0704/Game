#pragma once
#include <ResourceHolder.hpp>
#include <SFML/Graphics/Font.hpp>

namespace Fonts
{
	enum ID
	{
		Sansation
	};
};

typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
