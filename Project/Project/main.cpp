/*
	13-03-2019

	SlotMachine Game
*/
#include <SFML\Graphics.hpp>
#include "Game.h"

int main() {

	sf::RenderWindow window(sf::VideoMode(300, 350), "Slots", sf::Style::Close | sf::Style::Titlebar);

	Game newGame(window);

	return 0;
}
