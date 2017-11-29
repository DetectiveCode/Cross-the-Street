#pragma once
#include "SFML/Graphics.hpp"

/*This is the header file of the vehicle class and this containes the class declaration with variables and methods*/
class vehicle
{
public:
	vehicle();
	vehicle(float vehicleSpeed); //override

	/*methods*/
	void Move(const float elapsed);
	void MoveRight(const float elapsed);
	void MoveLeft(const float elapsed);
	void SetBounds(sf::RenderWindow &window);

	/*variables*/
	sf::Sprite sprite;
	sf::FloatRect globalBounds;
	sf::Texture texture;

	bool movingLeft = false;

	int vehicleType = 0;
	int lane = 0;

	float movementSpeed;
	float heightLimit;
	float widthLimit;
};