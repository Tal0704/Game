#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <StateStack.hpp>
#include <Player.hpp>
#include <World.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

class Application
{
public:
	explicit Application();

	void run();

private:
	void update(const sf::Time& dt);
	void render();
	void processInput();

	void registerStates();

	void loadResources();


	sf::RenderWindow mWindow;
	sf::Event mEvent;
	bool mIsPaused = false;

	sf::Time mTimePerFrame = sf::seconds(1.f / 60.f);

	FontHolder mFonts;
	TextureHolder mTextures;

	World mWorld;
	Player mPlayer;
	StateStack mStateStack;

#ifndef NDEBUG
	bool mDebug = false;
	sf::Text mStatisticsText;
	void updateStatistics(sf::Time dt);
#endif

};
