#pragma once

#include <queue>
#include <Command.hpp>

class CommandQueue
{
public:

	CommandQueue();
	void push(const Command& command);
	Command pop();
	bool isEmpty() const;
private:
	std::queue<Command> mQueue;
};

