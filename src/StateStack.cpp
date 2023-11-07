#include "StateStack.hpp"
#include <cassert>

StateStack::StateStack(State::Context context)
	: mContext(context)
{

}

State::Ptr StateStack::createState(States::ID stateID)
{
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());

	return found->second();
}

void StateStack::handleEvent(const sf::Event& event)
{
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->handleEvent(event))
			return;
	}
	applyPendingChanges();
}

void StateStack::update(sf::Time dt)
{
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->update(dt))
			return;
	}
	applyPendingChanges();
}

void StateStack::draw() const
{
	for (auto& state : mStack)
	{
		state->draw();
	}
}

void StateStack::applyPendingChanges()
{
	for (PendingChange change : mPendingList)
	{
		switch (change.action)
		{
		case Action::Push:
			mStack.push_back(createState(change.stateID));
			break;
		case Action::Pop:
			mStack.pop_back();
			break;
		case Action::Clear:
			mStack.clear();

		default:
			break;
		}
	}
	mPendingList.clear();
}

void StateStack::pushState(States::ID stateID)
{
	mPendingList.push_back(PendingChange(Action::Push, stateID));
}

void StateStack::clearStates()
{
	mPendingList.push_back(PendingChange(Action::Clear));
}

void StateStack::popState()
{
	mPendingList.push_back(PendingChange(Action::Pop));
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
	: action(action)
	, stateID(stateID)
{

}
