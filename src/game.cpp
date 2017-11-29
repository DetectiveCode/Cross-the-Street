#include <stack>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "game.h"
#include "game_state.h"

/*This class is the main game class. You are able to make an instance of this to run the actually game. 
The game loop is in here and it will update all of the game states.*/
game::game() //Game class constructor
{
	//Call these methods to load assets.
	loadTextures();
	loadFonts();
	loadSounds();

	//Variables for window height and width.
	unsigned int windowWidth = 800;
	unsigned int windowHeight = 800;

	//Create new window. Set frame limit and window poisiotn.
	window.create(sf::VideoMode(windowWidth, windowHeight), "Cross the Street");
	window.setFramerateLimit(60);
	window.setPosition(sf::Vector2i(50, 50));

	//Set background sprite texture and position
	background.setTexture(textureManager.getRef("background"));
	background.setPosition(0, 0);
}

game::~game() //Game class deconstructor
{
	while (!states.empty()) // While the stack is not empty
	{
		states.pop(); // Removes the newest element in the stack
	}
}

game_state* game::state() //game state type method
{
	if (states.empty()) //Check if stack is empty
	{
		return nullptr;
	}
	else
	{
		return states.top(); //Return reference to top element in stack
	}
}

void game::gameLoop() //game loop method. this is where the magic happens
{
	sf::Clock clock; //new clock variable

	while (window.isOpen()) //While the window is open continue the magic
	{
		float elapsed = clock.restart().asSeconds(); //seconds elapsed

		if (state() == nullptr) continue; // if the state is null

		//Access function via pointer
		state()->handleInput(); //handle the input from the override void
		state()->update(elapsed); //update from the override void
		window.clear(sf::Color::Black); //cear window with black colour
		state()->draw(elapsed); //draw from the override void
		window.display(); //display to screen
	}
}

/*Loading textures from files to memory*/
void game::loadTextures()
{
	std::string assetPath = "assets\\textures\\";
	textureManager.loadTexture("background", assetPath + "backgroundv4.png");
	textureManager.loadTexture("fade", assetPath + "fade.png");
	textureManager.loadTexture("player", assetPath + "player1.png");
	textureManager.loadTexture("car_1", assetPath + "blue-car.png");
	textureManager.loadTexture("car_2", assetPath + "cyan-car.png");
	textureManager.loadTexture("car_3", assetPath + "lime-car.png");
	textureManager.loadTexture("car_4", assetPath + "police-car.png");
	textureManager.loadTexture("car_5", assetPath + "red-car.png");
	textureManager.loadTexture("car_6", assetPath + "taxi-car.png");
}

/*Loading fonts to memory from file*/
void game::loadFonts()
{
	std::string assetPath = "assets\\fonts\\";
	fontManager.loadFont("arial", assetPath + "arial.ttf");
	fontManager.loadFont("grobold", assetPath + "GROBOLD.ttf");
}

/*Loading audio to memory from file*/
void game::loadSounds()
{
	std::string assetPath = "assets\\sounds\\";
	soundManager.loadSound("bgmusic", assetPath + "music.ogg");
}