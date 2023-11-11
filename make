#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <TitleState.hpp>
#include <Fonts.hpp>
#include <Textures.hpp>
#include <Helpers.hpp>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>


TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
{
	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	sf::Font& font = context.fonts->get(Fonts::Sansation);

//	sf::RenderWindow& window = *context.window;
//
	mBackground.setTexture(texture);
	centerOrigin(mBackground);
	mBackground.setPosition(0.f, 0.f);

	mText.setFont(font);
	mText.setString("Press any key to continue!");
	centerOrigin(mText);
	centerOrigin(s);
	s.setRadius(5.f);
	s.setPosition(mText.getOrigin());
	std::cout << mText.getPosition() << "\n";
}

bool TitleState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		requestStackPop();
		requestStackPush(States::Menu);
	}
	return true;
}

bool TitleState::update(sf::Time dt)
{
	mTextEffectTime += dt;

	if (mTextEffectTime >= sf::seconds(0.5f))
	{
		mShowText = !mShowText;
		mTextEffectTime = sf::Time::Zero;
	}
	return true;
}

void TitleState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackground);
	window.draw(mText);
	window.draw(s);
}

