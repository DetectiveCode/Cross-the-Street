#pragma once
#include "SFML/Graphics.hpp"
#include "game_state.h"
#include "character.h"
#include "vehicle.h"
#include <vector>

/*This is the header file of the game state playing class and this containes 
the class declaration with variables and methods. It also inherits game state.*/
class game_state_playing : public game_state
{
public:
	/*declare public variabls and virtual voids to prevent */
	game_state_playing(game* _game);

	virtual void draw(const float elapsed);
	virtual void update(const float elapsed);
	virtual void handleInput();
	

private:
	sf::View view; //The render window view
	character player;
	std::vector<vehicle> vehicles;
	std::vector<sf::Text> texts;
	sf::Sprite fade;
	

	int laneCapacity = 1; //Max vehicles in one lane
	int currentLevel = 1;
	float vehicleSpeed = 5.0f;
	bool paused = false;
	sf::Uint8 fadeAmount = 255;
	bool fadeComplete = false;
	bool introComplete = false;
	bool fadeIn = false;

	void writeText();
	void resetGame();
	void updateText();
};