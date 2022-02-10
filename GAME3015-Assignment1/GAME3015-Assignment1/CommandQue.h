#pragma once
#include "CommandQue.h""
#include <queue>
#include "Command.h"
class CommandQue
{
public:
	void push(const Command& command);
	Command pop();
	bool isEmpty() const;

private:
	std::queue<Command> mQueue;
};


//
//#pragma once
//#include <Command.hpp>
//
//#include <queue>
//
//
//class CommandQueue
//{
//public:
//	void						push(const Command& command);
//	Command						pop();
//	bool						isEmpty() const;
//
//
//private:
//	std::queue<Command>			mQueue;
//};
//
//
