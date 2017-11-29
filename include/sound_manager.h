#pragma once
#include <SFML/audio.hpp>
#include <string>
#include <map>

/*This is the header file of the sound manager class and this containes the class declaration with variables and methods*/
class sound_manager
{
public:
	void loadSound(const std::string& name, const std::string& filename); // Load font from file
	sf::SoundBuffer& getRef(const std::string& sound); // Get font reference ID from map

private:
	std::map<std::string, sf::SoundBuffer> sounds; // Array of fonts (Key, Value)

};