#include "State.hpp"
#include <StateStack.hpp>

void State::requestStackPop()
{

}

void State::requestStateClear()
{

}

void State::requestStackPush(States::ID stateID)
{
	mStack->pushState(stateID);
}

State::State(StateStack& stack, Context context)
	: mStack(&stack)
	, mContext(context)
{

}

State::Context State::getContext() const
{
	return mContext;
}

State::~State()
{}

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player)
	: window(&window) , textures(&textures) , fonts(&fonts) , player(&player) {}
