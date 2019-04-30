#pragma once
#include <SFML\Graphics.hpp>
#include "Reel.h"
#include "Light.h"

//Slot Machine Object
class Machine
{
public:
	Machine(float w, float h);
	~Machine();

	int GetCredits();
	void AddCredits();
	void RemoveCredits();
	
	int Play(int& gameState);
	void CheckIfDone(int& gameState);

	//Animate the lights around the slot machine
	void AnimateLights(float deltaTime, float switchTime);

	void Draw(sf::RenderWindow& window);

public:
	Reel r1;
	Reel r2;
	Reel r3;
	Light lights[39];
	float elapsedTime;
	int currentLight;
	bool anim;

private:
	//Create Lights around the slot machine
	void CreateLights();

private:
	float width;
	float height;
	sf::RectangleShape body;
	sf::Texture tex;

	int credits;

};