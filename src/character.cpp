#include "character.h"
#include <iostream>

/*This class handles the character, you can make a new character here and move it. 
The boundaries of the character is set here as well so you cannot move off of the screen.*/
character::character()
{
	//Set variable values when new instance is made.
	movementSpeed = 10.0f;
	lives = 3;
	std::cout << "A new player has been created" << std::endl;
}

void character::MoveUp()
{
	//Check to see if sprite is in bounds and change coords accordingly.
	if (sprite.getPosition().y > 0) sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - movementSpeed);
	std::cout << "The player has been moved up. New Position: " << sprite.getPosition().x << ", " << sprite.getPosition().y << std::endl;
}

void character::MoveDown()
{
	//Check to see if sprite is in bounds and change coords accordingly.
	if (sprite.getPosition().y < heightLimit) sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + movementSpeed);
	std::cout << "The player has been moved down. New Position: " << sprite.getPosition().x << ", " << sprite.getPosition().y << std::endl;
}

void character::MoveLeft()
{
	//Check to see if sprite is in bounds and change coords accordingly.
	if (sprite.getPosition().x > 0) sprite.setPosition(sprite.getPosition().x - movementSpeed, sprite.getPosition().y);
	std::cout << "The player has been moved left. New Position: " << sprite.getPosition().x << ", " << sprite.getPosition().y << std::endl;
}

void character::MoveRight()
{
	//Check to see if sprite is in bounds and change coords accordingly.
	if (sprite.getPosition().x < widthLimit) sprite.setPosition(sprite.getPosition().x + movementSpeed, sprite.getPosition().y);
	std::cout << "The player has been moved right. New Position: " << sprite.getPosition().x << ", " << sprite.getPosition().y << std::endl;
}

void character::SetBounds(sf::RenderWindow &window)
{
	//Set bounds. limit of how far the sprite can move.
	heightLimit = window.getView().getSize().y - sprite.getGlobalBounds().height;
	widthLimit = window.getView().getSize().x - sprite.getGlobalBounds().width;
}