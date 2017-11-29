#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

/*This is the header file of the font manager class and this containes the class declaration with variables and methods*/
class font_manager
{
public:
	void loadFont(const std::string& name, const std::string& filename); // Load font from file
	sf::Font& getRef(const std::string& font); // Get font reference ID from map

private:
	std::map<std::string, sf::Font> fonts; // Array of fonts (Key, Value)

};