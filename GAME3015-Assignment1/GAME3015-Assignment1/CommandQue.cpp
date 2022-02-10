#include "CommandQue.h"
#include "SceneNode.h"

//#include <CommandQueue.hpp>
//#include <SceneNode.hpp>
//
//
//void CommandQueue::push(const Command& command)
//{
//	mQueue.push(command);
//}
//
//Command CommandQueue::pop()
//{
//	Command command = mQueue.front();
//	mQueue.pop();
//	return command;
//}
//
//bool CommandQueue::isEmpty() const
//{
//	return mQueue.empty();
//}

void CommandQue::push(const Command& command) {
	mQueue.push(command);
};

Command CommandQue::pop() {
	Command command = mQueue.front();
	mQueue.pop();
		return command;
};

bool CommandQue::isEmpty() const{
	return mQueue.empty();
};


