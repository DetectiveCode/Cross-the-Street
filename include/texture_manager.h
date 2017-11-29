#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

/*This is the header file of the texture manager class and this containes the class declaration with variables and methods*/
class texture_manager
{
public:
	void loadTexture(const std::string& name, const std::string& filename); // Load texture from file
	sf::Texture& getRef(const std::string& texture); // Get Texture reference ID from map

private:
	std::map<std::string, sf::Texture> textures; // Array of Textures (Key, Value)

};