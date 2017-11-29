#include "game.h"
#include "game_state_playing.h"

/*This is the main function. Every c++ application has this, 
and this is where the game initialisses.*/
int main()
{
	game game; //New instance of game class

	/*Create new sound, set it's buffer and play*/
	sf::Sound bgmusic;
	bgmusic.setBuffer(game.soundManager.getRef("bgmusic"));
	bgmusic.setLoop(true);
	bgmusic.play();

	game.states.push(new game_state_playing(&game)); //Push new game state to game state stack
	game.gameLoop(); //Start game loop

	return 0;
}