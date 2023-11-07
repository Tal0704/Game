#include "Fonts.hpp"
#include "States.hpp"
#include <PauseState.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <Helpers.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

PauseState::PauseState(StateStack& state, Context context)
	: State(state, context) 
{
	mPausedText.setFont(getContext().fonts->get(Fonts::Sansation));
	mInstructionText.setFont(getContext().fonts->get(Fonts::Sansation));

	centerOrigin(mPausedText);
	centerOrigin(mInstructionText);

	mPausedText.setString("Game is paused");
	mPausedText.setPosition(sf::Vector2f(getContext().window->getSize()) / 2.f);
	mInstructionText.setString("Press Esc again to continue or Backspace to return to main menu");
	mInstructionText.setPosition(sf::Vector2f(getContext().window->getSize()) / 2.f);
	
}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(sf::Vector2f(window.getSize()));

	window.draw(backgroundShape);
	window.draw(mPausedText);
	window.draw(mInstructionText);
}

bool PauseState::handleEvent(const sf::Event& event)
{
	using sf::Keyboard;
	if(event.key.code == Keyboard::Backspace)
	{
		requestStateClear();
		requestStackPush(States::Game);
	}

	if(event.key.code == Keyboard::Escape)
	{
		State::requestStackPop();
		State::requestStackPush(States::Menu);
	}

	return false;
}

bool PauseState::update(sf::Time ft)
{
	return false;	
}
