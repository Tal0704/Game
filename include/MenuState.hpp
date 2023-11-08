#pragma once
#include <State.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class MenuState
	:public State
{
public:
	enum OptionNames
	{
		Play,
		Exit,
	};

	MenuState(StateStack& stack, Context context);

	void updateOptionText();
	
	void draw();
	bool update(sf::Time ft);
	bool handleEvent(const sf::Event& event);
private:
	std::vector<sf::Text> mOptions;
	size_t mOptionIndex;

	sf::Sprite mBackgroundSprite;
};
