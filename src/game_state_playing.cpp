#include "SFML/Audio.hpp"
#include <string>
#include <iostream>
#include "game_state.h"
#include "game_state_playing.h"
#include "character.h"
#include "vehicle.h"
#include "texture_manager.h"

/*This is the state in the game will be in when it is being played. 
All of the actual playing code is in here. Handles spawning cars, input and moving*/
game_state_playing::game_state_playing(game* game)
{
	_game = game; //set game variable
	/*set view*/
	sf::Vector2f pos = sf::Vector2f(_game->window.getSize());
	view.setSize(pos);
	view.setCenter(pos * 0.5f);
	_game->window.setSize(sf::Vector2u(600, 600));

	/*set sprite with texture and position*/
	fade.setTexture(_game->textureManager.getRef("fade"));
	fade.setPosition(0, 0);

	/*set player sprite texture and position and bounds*/
	player.sprite.setTexture(_game->textureManager.getRef("player"));
	player.sprite.setPosition(400, 770);
	player.SetBounds(_game->window);

	//call write text method
	writeText();
}

void game_state_playing::draw(const float elapsed)
{
	_game->window.setView(view); //set window view
	_game->window.clear(sf::Color::Black); //clear window with colour black
	_game->window.draw(_game->background); //draw background to window
	_game->window.draw(player.sprite); //draw player sprite to window

	/*loop to draw each vehicle sprite to window*/
	for (size_t i = 0; i < vehicles.size(); i++)
	{
		_game->window.draw(vehicles[i].sprite);
	}

	/*loop to draw each text to window*/
	for (size_t i = 0; i < texts.size(); i++)
	{
		_game->window.draw(texts[i]);
	}

	/*loop sprite to window*/
	if (!fadeComplete || !player.alive)
	{
		_game->window.draw(fade);
	}

	/*if condition make new text, set font, set string, set size, set colour, set position and draw to winow*/
	if (!introComplete)
	{
		sf::Text startText;
		startText.setFont(_game->fontManager.getRef("arial"));
		startText.setString("\tCross the Street\n\t\tBy Farbod\n\n Press 'space' to play");
		startText.setCharacterSize(30);
		startText.setFillColor(sf::Color::White);
		startText.setPosition(sf::Vector2f(view.getSize().x / 2 - 140, view.getSize().y / 2 - 140));
		_game->window.draw(startText);
	}

	/*if condition make new text, set font, set string, set size, set colour, set position and draw to winow*/
	if (paused) 
	{
		sf::Text pauseText;
		pauseText.setFont(_game->fontManager.getRef("arial"));
		pauseText.setString("Paused. Press 'p' to resume");
		pauseText.setCharacterSize(20);
		pauseText.setFillColor(sf::Color::White);
		pauseText.setPosition(sf::Vector2f(view.getSize().x / 2 - 120, view.getSize().y / 2 - 12));
		_game->window.draw(pauseText);
	}

	/*if condition make new text, set font, set string, set size, set colour, set position and draw to winow*/
	if (!player.alive)
	{
		sf::Text aliveText;
		aliveText.setFont(_game->fontManager.getRef("arial"));
		aliveText.setString("Game over. Press 'space' to restart");
		aliveText.setCharacterSize(20);
		aliveText.setFillColor(sf::Color::White);
		aliveText.setPosition(sf::Vector2f(view.getSize().x / 2 - 150, view.getSize().y / 2 - 12));
		_game->window.draw(aliveText);
	}
}

/*update method*/
void game_state_playing::update(const float elapsed)
{
	if (!fadeComplete)
	{
		if (introComplete)
		{
			if (fadeIn) { fadeAmount++; }
			else { fadeAmount--; }

			//change sprite colour
			fade.setColor(sf::Color(255, 255, 255, fadeAmount));

			if (fadeAmount == 0 || fadeAmount == 255)
			{
				introComplete = true;
				fadeComplete = true;
			}
		}
		else { return; }
	}

	if (paused || !player.alive) return;

	/*generate some random numbers*/
	int lane = rand() % (6 - 1 + 1) + 1;
	int vehicleType = rand() % (6 - 1 + 1) + 1;
	int laneCount = 0;
	std::vector<vehicle> vehiclesInLane; //new vector with type vehicle

	/*check sprite position*/
	if (player.sprite.getPosition().y <= 20)
	{
		std::cout << "The player has reached the other side." << std::endl;
		player.sprite.setPosition(400, 770);
		std::cout << "Player position reset to " << player.sprite.getPosition().x << ", " << player.sprite.getPosition().y << std::endl;
		
		currentLevel++;
		updateText();
		std::cout << "Level increased to " << std::to_string(currentLevel) << std::endl;

		if (laneCapacity < 4 && currentLevel % 5 == 0)
		{
			laneCapacity++;
			std::cout << "Lane capacity increased to " << std::to_string(laneCapacity) << std::endl;
		}

		if (vehicleSpeed < 30)
		{
			vehicleSpeed++; //increae vehicle speed
		}
	
	}

	/*loop to loop over each vehicle*/
	for (size_t i = 0; i < vehicles.size(); i++)
	{
		/*move the vehicles and set speed as appropriate*/
		if (vehicles[i].movementSpeed != vehicleSpeed) { vehicles[i].movementSpeed = vehicleSpeed; }
		vehicles[i].Move(elapsed);

		/*check to see if player has been hit*/
		if (player.sprite.getGlobalBounds().intersects(vehicles[i].sprite.getGlobalBounds()))
		{
			player.lives--;
			player.sprite.setPosition(400, 770);
			std::cout << "The player has been hit and sent back to the start." << std::endl;
			updateText();

			if (player.lives < 1)
			{
				player.alive = false;
				return;
			}
		}

		for (size_t j = 0; j < vehicles.size(); j++)
		{
			if (vehicles[i].sprite.getGlobalBounds().intersects(vehicles[j].sprite.getGlobalBounds()))
			{
				if (i == j) { continue; }

				if (vehicles[i].lane < 4)
				{
					vehicles[i].sprite.setPosition(vehicles[i].sprite.getPosition().x - 200, vehicles[i].sprite.getPosition().y);
				}
				else
				{
					vehicles[i].sprite.setPosition(vehicles[i].sprite.getPosition().x + 200, vehicles[i].sprite.getPosition().y);
				}
				
				std::cout << "The cars were overlapping, position was recalculated. !1111 " << std::endl;
			}
		}
	}

	if (vehicles.size() != 0)
	{
		/*loop to check to see if vehicle has gone off the window and if so remove it from the vector*/
		for (size_t i = 0; i < vehicles.size(); i++)
		{
			if (vehicles[i].sprite.getPosition().x == vehicles[i].widthLimit || vehicles[i].sprite.getPosition().x > vehicles[i].widthLimit)
			{
				vehicles.erase(vehicles.begin() + i);
				continue;
			}

			if (vehicles[i].sprite.getPosition().x == -vehicles[i].sprite.getGlobalBounds().width || vehicles[i].sprite.getPosition().x < -vehicles[i].sprite.getGlobalBounds().width)
			{
				vehicles.erase(vehicles.begin() + i);
				continue;
			}

			if (vehicles[i].lane == lane)
			{
				laneCount++;
				vehiclesInLane.push_back(vehicles[i]);
			}

			if (laneCount >= laneCapacity)
			{
				break;
			}
		}
	}

	if (laneCount < laneCapacity)
	{
		/*add a new vehicle to the lane if lane capacity has exceeded*/
		vehicle car(vehicleSpeed);
		
		car.sprite.setTexture(_game->textureManager.getRef("car_" + std::to_string(vehicleType)));
		car.sprite.setOrigin(car.sprite.getGlobalBounds().width / 2, car.sprite.getGlobalBounds().height / 2);
		car.SetBounds(_game->window);
		
		float positionx = 800.0f;
		float positiony = 800.0f;

		switch (lane)
		{
		case 1: 
			positiony = 100.0f;
			break;
		case 2:
			positiony = 210.0f;
			break;
		case 3:
			positiony = 320.0f;
			break;
		case 4:
			positiony = 480.0f;
			break;
		case 5:
			positiony = 590.0f;
			break;
		case 6:
			positiony = 700.0f;
			break;
		}
		
		if (lane < 4)
		{
			positionx = -car.sprite.getGlobalBounds().width;
			car.movingLeft = false;
		}
		else
		{
			positionx = view.getSize().x + car.sprite.getGlobalBounds().width;
			car.movingLeft = true;
		}

		car.sprite.setPosition(positionx, positiony);
		car.lane = lane;
		
		if (vehiclesInLane.size() > 0)
		{
			/*loop to check and see if each vehicle is interesecting any other vehicle*/
			for (size_t i = 0; i < vehiclesInLane.size(); i++)
			{
				if (vehiclesInLane[i].sprite.getGlobalBounds().intersects(car.sprite.getGlobalBounds()))
				{
					int spacing = rand() % (400 - 10 + 1) + 10;

					if (lane < 4)
					{
						positionx -= vehiclesInLane[i].sprite.getGlobalBounds().width + spacing;
					}
					else
					{
						positionx += vehiclesInLane[i].sprite.getGlobalBounds().width + spacing;
					}

					car.sprite.setPosition(positionx, positiony);

					std::cout << "The cars were overlapping, position was recalculated." << std::endl;
				}
			}
		}

		/*push vehicle to vector*/
		vehicles.push_back(car);

		laneCount = 0;
	}
}

/*method to handle keyboard input*/
void game_state_playing::handleInput()
{
	sf::Event event;

	/*while window is being polled*/
	while (_game->window.pollEvent(event))
	{
		/*switch the event type*/
		switch (event.type)
		{
			case sf::Event::Closed: //if the event is close
			{
				_game->window.close();
				break;
			}

			case sf::Event::Resized: //if resized then properly set the size to keep aspect ratio
			{
				unsigned int x = _game->window.getSize().x;

				if (x < sf::VideoMode::getDesktopMode().width && x < sf::VideoMode::getDesktopMode().height)
				{
					_game->window.setSize(sf::Vector2u(x, x));
				}

				break;
			}

			case sf::Event::KeyPressed: //if key is pressed
			{
				if (!paused && player.alive && introComplete) {
					if (event.key.code == sf::Keyboard::Down)
					{
						player.MoveDown();
					}

					if (event.key.code == sf::Keyboard::Up)
					{
						player.MoveUp();
					}

					if (event.key.code == sf::Keyboard::Left)
					{
						player.MoveLeft();
					}

					if (event.key.code == sf::Keyboard::Right)
					{
						player.MoveRight();
					}
				}

				if (event.key.code == sf::Keyboard::P && player.alive)
				{
					std::cout << "Game was paused" << std::endl;
					paused = !paused;
				}

				if (!introComplete)
				{
					if (event.key.code == sf::Keyboard::Space)
					{
						introComplete = true;;
					}
				}
				else
				{
					if (event.key.code == sf::Keyboard::Space && !player.alive)
					{
						resetGame();
					}
				}
				break;
			}

		default: break;
		}
	}
}

void game_state_playing::writeText()
{
	sf::Text livesText;
	livesText.setFont(_game->fontManager.getRef("arial"));
	livesText.setString("Lives: " + std::to_string(player.lives));
	livesText.setCharacterSize(20);
	livesText.setFillColor(sf::Color::White);
	livesText.setPosition(sf::Vector2f(5, 5));
	texts.push_back(livesText);

	sf::Text levelText;
	levelText.setFont(_game->fontManager.getRef("arial"));
	levelText.setString("Level: " + std::to_string(currentLevel));
	levelText.setCharacterSize(20);
	levelText.setFillColor(sf::Color::White);
	levelText.setPosition(sf::Vector2f(view.getSize().x - 80, 5));
	texts.push_back(levelText);
}

void game_state_playing::resetGame()
{
	player.alive = true;
	laneCapacity = 1;
	vehicleSpeed = 5.0f;
	currentLevel = 1;
	player.lives = 3;
	player.sprite.setPosition(400, 770);
	updateText();
	std::cout << "Game was reset" << std::endl;
}

void game_state_playing::updateText()
{
	texts[1].setString("Level: " + std::to_string(currentLevel));
	texts[0].setString("Lives: " + std::to_string(player.lives));
}