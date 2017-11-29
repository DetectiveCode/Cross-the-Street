#include "texture_manager.h"
#include "SFML/Graphics.hpp"

/*This class is the texture manager, it loads all the textures into memory and holds them until the game is closed.*/
void texture_manager::loadTexture(const std::string& name, const std::string& filename)
{
	sf::Texture texture; //Create new texture variable
	texture.loadFromFile(filename); //Load texture from file

	textures[name] = texture; //Set the value of map with id 'name' to texture
}

sf::Texture& texture_manager::getRef(const std::string& texture)
{
	return textures.at(texture); //Return value with key font from textures map
}