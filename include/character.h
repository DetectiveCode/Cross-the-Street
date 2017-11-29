#pragma once
#include <SFML/Graphics.hpp>

/*This is the header file of the character class and this containes the class declaration with variables and methods*/
class character
{
public:
	character();

	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();
	void SetBounds(sf::RenderWindow &window);

	sf::Sprite sprite;
	sf::FloatRect globalBounds;

	float movementSpeed;
	int lives = 3;
	bool alive = true;

private:
	float heightLimit;
	float widthLimit;
};