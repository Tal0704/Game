#pragma once
#include <ResourceHolder.hpp>

namespace Textures
{
	enum ID
	{
		MainCharacter,
		Background
	};
};

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
