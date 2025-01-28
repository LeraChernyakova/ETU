#pragma once
#include "StateGame.h"
#include "ComandReader.h"

class Mediator
{
private:
	StateGame state;
	ComandReader command;
public:
	void gameProcessing();
};
