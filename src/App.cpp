#include "Fonts.hpp"
#include "States.hpp"
#include <App.hpp>
#include <GameState.hpp>
#include <TitleState.hpp>
#include <MenuState.hpp>
#include <PauseState.hpp>
#include <Textures.hpp>
#include <string>

Application::Application()
	: mWindow(sf::VideoMode(640, 480), "Side Scroller")
	, mWorld(mWindow)
	, mPlayer()
	, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
{

	loadResources();
	mStatisticsText.setFont(mFonts.get(Fonts::Sansation));
	mStatisticsText.setCharacterSize(10);
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
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		processInput();
		while (timeSinceLastUpdate > mTimePerFrame)
		{
			timeSinceLastUpdate -= mTimePerFrame;
			processInput();

			if (!mIsPaused)
				update(mTimePerFrame);
			if(mStateStack.isEmpty())
				mWindow.close();
		}
		updateStatistics(dt);
		render();
	}
}

void Application::render()
{
	mWindow.clear();
	mStateStack.draw();
#ifndef NDEBUG
	if(!mDebug)
		mWindow.draw(mStatisticsText);
#endif
	mWindow.display();
				
}

void Application::processInput()
{
	CommandQueue& commands = mWorld.getCommandQueue();

	while (mWindow.pollEvent(mEvent))
	{
		mStateStack.handleEvent(mEvent);

		if (mEvent.type == sf::Event::Closed)
			mWindow.close();

#ifndef NDEBUG
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Home))
			mDebug = !mDebug;

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


void Application::loadResources()
{
	mFonts.load(Fonts::Sansation, "Media/fonts/Sansation.ttf");
	mTextures.load(Textures::TitleScreen, "Media/Textures/TitleScreen.png");
}

#ifndef NDEBUG
void Application::updateStatistics(sf::Time dt)
{
	static sf::Time statisticUpdateTime = sf::Time::Zero;
	static int numberOfFrames = 0;

	statisticUpdateTime += dt;
	numberOfFrames++;

	if(statisticUpdateTime >= sf::seconds(1))
	{
		mStatisticsText.setString(std::to_string(numberOfFrames) + "fps");
		statisticUpdateTime -= sf::seconds(1);
		numberOfFrames = 0;
	}
}
#endif
