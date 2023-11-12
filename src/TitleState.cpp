#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <TitleState.hpp>
#include <Fonts.hpp>
#include <Textures.hpp>
#include <Helpers.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
{
	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	sf::Font& font = context.fonts->get(Fonts::Sansation);

	sf::RenderWindow& window = *context.window;

	mBackground.setTexture(texture);
	centerOrigin(mBackground);
	mBackground.setPosition(sf::Vector2f(window.getSize()) / 2.f);

	mText.setString("Press any key to continue!");
	mText.setFont(font);
	centerOrigin(mText);
	mText.setPosition(sf::Vector2f(window.getSize()) / 2.f);
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
}

