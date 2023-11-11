#pragma once

#include <CommandQueue.hpp>
#include <Character.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>

class Player
{
public:
	Player();
	enum Action
	{
		moveLeft,
		moveRight,
		moveUp,
		moveDown
	};

	void assignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key getAssignedKey(Action action) const;

	void handleEvent(const sf::Event& event, CommandQueue& commands);

	void handleRealTime(CommandQueue& commands);

private:
	static bool isRealTimeAction(Action action);

	std::map<sf::Keyboard::Key, Action> mKeyBinding;
	std::map<Action, Command> mActionBinding;

	float mPlayerSpeed = 100;
};

struct PlayerMover
{
	PlayerMover(float x, float y)
	{
		PlayerMover(sf::Vector2f(x, y));
	}
	PlayerMover(const sf::Vector2f& v)
		: velocity(v.x, v.y)
	{

	}

	void operator()(Character& character, const sf::Time& time) const
	{
		character.move(velocity);
	}

	sf::Vector2f velocity;
};
