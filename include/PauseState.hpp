#pragma once
#include <SFML/Window/Event.hpp>
#include <State.hpp>
#include <SFML/Graphics/Text.hpp>

class PauseState
	: public State
{
public:
	PauseState(StateStack& stack, Context context);

	void draw();
	bool handleEvent(const sf::Event& event);
	bool update(sf::Time time);
private:
	sf::Text mPausedText, mInstructionText;
};

