#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <Helpers.hpp>

Player::Player()
{
	mKeyBinding[sf::Keyboard::D] = moveRight;
	mKeyBinding[sf::Keyboard::A] = moveLeft;
	mKeyBinding[sf::Keyboard::S] = moveDown;
	mKeyBinding[sf::Keyboard::W] = moveUp;

	mActionBinding[moveRight].action = derivedAction<Character>([*this](Character& character, sf::Time dt) {
		character.move(mPlayerSpeed * dt.asSeconds(), 0.0f);
		});

	mActionBinding[moveLeft].action = derivedAction<Character>([*this](Character& character, sf::Time dt) {
		character.move(-mPlayerSpeed * dt.asSeconds(), 0.0f);
		});

	mActionBinding[moveUp].action = derivedAction<Character>([*this](Character& character, sf::Time dt) {
		character.move(0.0f, -mPlayerSpeed * dt.asSeconds());
		});


	mActionBinding[moveDown].action = derivedAction<Character>([*this](Character& character, sf::Time dt) {
		character.move(0.0f, mPlayerSpeed * dt.asSeconds());
		});

	for (auto& pair : mActionBinding)
	{
		pair.second.category = Category::Player;
	}
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
	{
		Command output;
		output.category = Category::Player;
		output.action = derivedAction<Character>([](Character& character, const sf::Time& dt) {
			std::cout << character.getPosition() << "\n";
			});
		commands.push(output);
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
	{
		Command jump;
		jump.category = Category::Player;
		jump.action = derivedAction<Character>([](Character& character, const sf::Time dt) {
			});
	}
}

void Player::handleRealTime(CommandQueue& commands)
{
	for (const auto& pair : mKeyBinding)
	{
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second))
		{
			commands.push(mActionBinding[pair.second]);
		}
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	auto foundAction = mKeyBinding.find(key);
	if (foundAction != mKeyBinding.end() && foundAction->second == action)
		mKeyBinding.insert({ key, action });
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	for (const auto& pair : mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}
	return sf::Keyboard::Escape;
}

bool Player::isRealTimeAction(Action action)
{
	return true;
}
