#pragma once
#include "game.h"

/*This is the header file of the game state class and this containes the class declaration with variables and methods*/
class game_state
{
public:
	game* _game;

	virtual void draw(const float elapsed) = 0;
	virtual void update(const float elapsed) = 0;
	virtual void handleInput() = 0;
};