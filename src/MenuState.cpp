#include "Fonts.hpp"
#include <MenuState.hpp>
#include <Helpers.hpp>

MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context)
{
	auto font = context.fonts->get(Fonts::Sansation);
	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Play");
	centerOrigin(playOption);
	
	playOption.setPosition(context.window->getView().getSize() / 2.f);
	mOptions.push_back(playOption);
}


void MenuState::updateOptionText()
{
	if(mOptions.empty())
		return;
	for(auto& text: mOptions)
		text.setFillColor(sf::Color::White);

	mOptions[mOptionIndex].setFillColor(sf::Color::Red);
}

void MenuState::draw()
{
	updateOptionText();
	for(const auto& option: mOptions)
		getContext().window->draw(option);
}

bool MenuState::update(sf::Time dt)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	using sf::Keyboard;
	if(event.key.code == Keyboard::Up)
	{
		if(mOptionIndex > 0)
			mOptionIndex--;
		else
			mOptionIndex = mOptions.size() - 1;

		updateOptionText();
	}

	if(event.key.code == Keyboard::Down)
	{
		if(mOptionIndex < mOptions.size() - 1)
			mOptionIndex++;
		else
			mOptionIndex = 0;

		updateOptionText();
	}
	
	if(event.key.code == Keyboard::Enter)
	{
		if(mOptionIndex == Play)
		{
			requestStackPop();
#ifndef NDEBUG
			requestStateClear();
#endif
			requestStackPush(States::Game);
		}
		if(mOptionIndex == Exit)
		{
			requestStackPop();
		}
	}
	return false;
}
