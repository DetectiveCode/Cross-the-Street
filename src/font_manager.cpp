#include "font_manager.h"
#include "SFML/Graphics.hpp"

/*This class is the font manager, it loads all the fonts into memory and holds them until the game is closed.*/
void font_manager::loadFont(const std::string& name, const std::string& filename)
{
	sf::Font font; //Create new font variable
	font.loadFromFile(filename); //Load font from file

	fonts[name] = font; //Set the value of map with id 'name' to font
}

sf::Font& font_manager::getRef(const std::string& font)
{
	return fonts.at(font); //Return value with key font from fonts map
}