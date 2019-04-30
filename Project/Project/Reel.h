#pragma once
#include <SFML\Graphics.hpp>
#include <stdlib.h>
#include <iostream>

class Reel
{
public:
	Reel();
	Reel(float w, float h, sf::Vector2f pos);
	~Reel();

	int GetValue();
	//Generate reel value from 1 to 3 
	void GenerateValue();
	void Draw(sf::RenderWindow& window);

	void LoadTextures();

	//Change texture to a randomized symbol
	void ChangeTexture();
	void Animate(float switchTime, float deltaTime);

	void SetAnim(bool value);
	bool GetAnim();

private:
	float width;
	float height;
	sf::RectangleShape body;
	sf::Texture tex[3];

	int value; //1 - cherries 2 - lucky 7 3 - dollar sign
	bool anim;
	float animLength;
	float elapsedTime;
};