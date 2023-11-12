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

	sf::RenderWindow& window = *context.window;

	mPausedText.setString("Game is paused");
	centerOrigin(mPausedText);
	mPausedText.setPosition(sf::Vector2f(window.getSize()) / 2.f);
	mInstructionText.setString("Press Enter to continue or\nEscape to return to main menu");
	centerOrigin(mInstructionText);
	mInstructionText.setPosition(sf::Vector2f(window.getSize()) / 2.f);
	mInstructionText.move(0.f, 50.f);
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
	if (event.type != sf::Event::KeyPressed)
		return false;

	if(event.key.code == Keyboard::Enter)
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
