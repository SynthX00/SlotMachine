#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

class Game
{
public:
	Game(sf::RenderWindow& wnd);
	~Game();

public:
	unsigned int width;
	unsigned int height;
	sf::RenderWindow* window;

	float elapsedTime;
	float deltaTime;

	int gameState; // -1 not running, 0 ready, 1 playing;

private:
	void RunGame();

private:
	int timesPlayed;
};

