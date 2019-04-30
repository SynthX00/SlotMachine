#pragma once
#include <SFML\Graphics.hpp>

class Light
{
public:
	Light();
	Light(float r, sf::Vector2f pos, sf::Color c);
	~Light();

	void ChangeLight(sf::Color c);
	void Draw(sf::RenderWindow& window);

private:
	float rad;
	sf::CircleShape body;
	sf::Color clr;
};