#pragma once
#include <stack>
#include "SFML/Graphics.hpp"
#include "texture_manager.h"
#include "font_manager.h"
#include "sound_manager.h"

/*nested class*/
class game_state;

/*This is the header file of the game class and this containes the class declaration with variables and methods*/
class game
{
public:
	game(); //Constructor
	~game(); //Destructor

	void gameLoop(); //method

	game_state* state(); //game_state pointer variable
	std::stack<game_state*> states; //stack with type game state pointer
	
	sf::RenderWindow window;
	sf::Sprite background;
	sf::Sprite fade;

	/*new instances of classes*/
	texture_manager textureManager;
	font_manager fontManager;
	sound_manager soundManager;

private:
	void loadTextures();
	void loadFonts();
	void loadSounds();
};