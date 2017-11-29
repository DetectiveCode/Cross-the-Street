#include "vehicle.h"
#include <SFML/Graphics.hpp>
#include <iostream>

/*This class handles the vehicle, you can make a new vehicle here and move it.
The boundaries of the vehicle is set here as well.*/
vehicle::vehicle()
{
	//Set variable value new instance is created.
	movementSpeed = 10.0f;
	std::cout << "A new vehicle has been created" << std::endl;
}

vehicle::vehicle(float vehicleSpeed)
{
	//override set value to the one specified
	movementSpeed = vehicleSpeed;
	std::cout << "A new vehicle has been created with speed " << std::to_string(vehicleSpeed) << std::endl;
}

void vehicle::Move(const float elapsed)
{
	if (movingLeft)
	{
		//set scale so it looks like the vehicle is facing the other way
		if (sprite.getScale().x == -1)
		{ 
			sprite.setScale(1, 1);
		}
		MoveLeft(elapsed); //call method to vehicle left
	}
	else
	{
		if (sprite.getScale().x == 1)
		{
			sprite.setScale(-1, 1);
		}

		MoveRight(elapsed); //call method to vehicle right
	}

}

void vehicle::MoveLeft(const float elapsed)
{
	//Check to see if sprite is in bounds and change coords accordingly.
	if (sprite.getPosition().x > -sprite.getGlobalBounds().width)
	{
		sprite.setPosition(sprite.getPosition().x - movementSpeed, sprite.getPosition().y);
	}

	/*if (sprite.getPosition().x == -sprite.getGlobalBounds().width || sprite.getPosition().x < -sprite.getGlobalBounds().width)
	{
		movingLeft = false;
	}
	else
	{
		movingLeft = true;
	}*/
}

void vehicle::MoveRight(const float elapsed)
{
	//Check to see if sprite is in bounds and change coords accordingly.
	if (sprite.getPosition().x < widthLimit)
	{
		sprite.setPosition(sprite.getPosition().x + movementSpeed, sprite.getPosition().y);
	}

	/*if (sprite.getPosition().x == widthLimit || sprite.getPosition().x > widthLimit)
	{
		movingLeft = true;
	}
	else
	{
		movingLeft = false;
	}*/
}

void vehicle::SetBounds(sf::RenderWindow &window)
{
	//Set bounds. limit of how far the sprite can move.
	heightLimit = window.getView().getSize().y - sprite.getGlobalBounds().height;
	widthLimit = window.getView().getSize().x + sprite.getGlobalBounds().width; // + allows it to go off of the screen
}