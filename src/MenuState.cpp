#include "Fonts.hpp"
#include <MenuState.hpp>
#include <Helpers.hpp>

MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
, mOptionIndex(0)
{
	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	sf::Font& font = context.fonts->get(Fonts::Sansation);

	sf::RenderWindow& window = *context.window;

	mBackgroundSprite.setTexture(texture);
	centerOrigin(mBackgroundSprite);
	mBackgroundSprite.setPosition(sf::Vector2f(window.getSize()) / 2.f);

	sf::Text text;
	text.setFont(font);
	text.setString("Play");
	centerOrigin(text);
	text.setPosition(sf::Vector2f(window.getSize()) / 2.f);
	mOptions.push_back(text);

	text.setString("quit");
	centerOrigin(text);
	text.move(0, 50.f);
	mOptions.push_back(text);

	updateOptionText();
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
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	updateOptionText();
	for (const auto& option : mOptions)
	{
		window.draw(option);
	}
}

bool MenuState::update(sf::Time dt)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	using sf::Keyboard;
	if((event.type == sf::Event::KeyPressed) && (event.key.code == Keyboard::Up))
	{
		if(mOptionIndex > 0)
				mOptionIndex--;
		else
			mOptionIndex = mOptions.size() - 1;

		updateOptionText();

	}

	if((event.type == sf::Event::KeyPressed) && (event.key.code == Keyboard::Down))
	{
		if(mOptionIndex < mOptions.size() - 1)
			mOptionIndex++;
		else
			mOptionIndex = 0;

		updateOptionText();
	}

	if((event.type == sf::Event::KeyPressed) && (event.key.code == Keyboard::Enter))
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
#ifndef NDEBUG
			requestStateClear();
#endif
		}

	}
	return false;

}

