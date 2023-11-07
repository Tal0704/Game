#include "CommandQueue.hpp"

bool CommandQueue::isEmpty() const
{
	return mQueue.empty();
}

Command CommandQueue::pop()
{
	auto popped = mQueue.front();
	mQueue.pop();
	return popped;
}

void CommandQueue::push(const Command& command)
{
	mQueue.push(command);
}

CommandQueue::CommandQueue()
{
	mQueue.empty();
}
