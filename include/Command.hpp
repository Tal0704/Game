#pragma once

#include <functional>
#include <SceneNode.hpp>

class SceneNode;

struct Command
{
	Command();
	std::function<void(SceneNode&, sf::Time)> action;
	unsigned int category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, const sf::Time&)> derivedAction(Function fn)
{
	return[=](SceneNode& node, const sf::Time& dt)
	{
		assert(dynamic_cast<GameObject*>(&node) != nullptr);
		fn(static_cast<GameObject&>(node), dt);
	};
}
