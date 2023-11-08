#include "States.hpp"
#include <App.hpp>
#include <GameState.hpp>
#include <TitleState.hpp>
#include <MenuState.hpp>
#include <PauseState.hpp>
#include <Textures.hpp>

Application::Application()
	: mWindow(sf::VideoMode(640, 480), "Side Scroller")
	, mWorld(mWindow)
	, mPlayer()
	, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
{
	mFonts.load(Fonts::Sansation, "Media/fonts/Sansation.ttf");
	mTextures.load(Textures::TitleScreen, "Media/Textures/TitleScreen.png");
	mStateStack.pushState(States::Title);
	registerStates();
}

void Application::update(const sf::Time& dt)
{
	mStateStack.update(dt);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		timeSinceLastUpdate += clock.restart();
		processInput();
		while (timeSinceLastUpdate > mTimePerFrame)
		{
			processInput();

			if (!mIsPaused)
				update(mTimePerFrame);
			timeSinceLastUpdate -= mTimePerFrame;
		}
		render();
	}
}

void Application::render()
{
	mWindow.clear();
	mStateStack.draw();
	mWindow.display();
				
}

void Application::processInput()
{
	CommandQueue& commands = mWorld.getCommandQueue();

	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();

#ifndef NDEBUG
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			mWindow.close();
#endif
									
	}
	mPlayer.handleRealTime(commands);
				
}

void Application::registerStates()
{
	mStateStack.registerState<TitleState>(States::Title);
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<GameState>(States::Game);
	mStateStack.registerState<PauseState>(States::Pause);
					
}

