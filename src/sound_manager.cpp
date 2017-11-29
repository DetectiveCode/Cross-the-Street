#include "sound_manager.h"
#include "SFML/Audio.hpp"

/*This class is the sound manager, it loads all the sounds into memory and holds them until the game is closed.*/
void sound_manager::loadSound(const std::string& name, const std::string& filename)
{
	sf::SoundBuffer sound; //Create new sound variable
	sound.loadFromFile(filename); //Load sound from file

	sounds[name] = sound; //Set the value of map with id 'name' to sound
}

sf::SoundBuffer& sound_manager::getRef(const std::string& sound)
{
	return sounds.at(sound); //Return value with key font from sounds map
}