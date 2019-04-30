#include "Machine.h"

Machine::Machine(float w, float h)
{

	width = w;
	height = h;

	body = sf::RectangleShape(sf::Vector2f(w, h));
	body.setPosition(30.0f, 10.0f);

	tex.loadFromFile("Resources/slots.png");
	body.setTexture(&tex);

	credits = 0;

	r1 = Reel(38.0f, 38.0f, sf::Vector2f(77.5f, 165.0f));
	r2 = Reel(38.0f, 38.0f, sf::Vector2f(136.0f, 165.0f));
	r3 = Reel(38.0f, 38.0f, sf::Vector2f(194.0f, 165.0f));

	r1.LoadTextures();
	r2.LoadTextures();
	r3.LoadTextures();

	CreateLights();
	elapsedTime = 0.0f;
	currentLight = 0;
	anim = false;
}

Machine::~Machine()
{
}

int Machine::GetCredits()
{
	return credits;
}

void Machine::AddCredits()
{
	if (credits + 1 < 999) {
		credits++;
	}
}

void Machine::RemoveCredits()
{
	if (credits - 1 >= 0)
	{
		credits--;
	}
}

int Machine::Play(int& gameState)
{
	int val = 0;

	//check if there are available credits to play
	if (credits > 0)
	{

		gameState = 1;

		RemoveCredits();

		//reset lights
		anim = true;
		for (int i = 0; i < 39; i++)
		{
			lights[i].ChangeLight(sf::Color::Black);
		}

		//generate reel values and begin animations
		r1.GenerateValue();
		r2.GenerateValue();
		r3.GenerateValue();

		r1.SetAnim(true);
		r2.SetAnim(true);
		r3.SetAnim(true);

		val = 1;
	}

	//return 1 if the player was able to play
	return val;
}

void Machine::CheckIfDone(int& gameState)
{
	//check if all reels are done with the animation and check if the player won
	if (!r1.GetAnim() && !r2.GetAnim() && !r3.GetAnim())
	{
		if (gameState == 1)
		{
			anim = false;
			elapsedTime = 0.0f;
			currentLight = 0;

			for (int i = 0; i < 39; i++)
			{
				lights[i].ChangeLight(sf::Color::Black);
			}

			//if the player won, he will be rewarded extra credits and the lights will turn yellow
			if (r1.GetValue() == r2.GetValue() && r2.GetValue() == r3.GetValue())
			{
				credits += 100;

				for (int i = 0; i < 39; i++)
				{
					lights[i].ChangeLight(sf::Color::Yellow);
				}
			}
		}

		//reset gamestate so the player can play again
		gameState = 0;
	}
}

//animate the lights using the deltatime
void Machine::AnimateLights(float deltaTime, float switchTime)
{
	if (anim)
	{
		elapsedTime += deltaTime;

		if (elapsedTime > switchTime)
		{
			elapsedTime -= switchTime;

			if (currentLight >= 1)
			{
				lights[currentLight - 1].ChangeLight(sf::Color::Black);
			}
			lights[currentLight].ChangeLight(sf::Color::Red);

			currentLight++;
		}

		if (currentLight >= 39)
		{
			currentLight = 0;
		}
	}
}

void Machine::Draw(sf::RenderWindow& window)
{
	r1.Draw(window);
	r2.Draw(window);
	r3.Draw(window);

	window.draw(body);

	for (int i = 0; i < 39; i++)
	{
		lights[i].Draw(window);
	}
}

void Machine::CreateLights()
{
	int i = 0;

	float x = 35.0f;
	for (i = 0; i < 9; i++)
	{
		x += 23.0f;
		lights[i] = Light(5.0f, sf::Vector2f(x, 35.0f), sf::Color::Black);
	}

	float y = 35.0f;
	int j = 0;
	for (j = 0; j < 11; j++)
	{
		y += 23.0f;
		lights[j + i] = Light(5.0f, sf::Vector2f(x, y), sf::Color::Black);
	}

	i += j;

	for (j = 0; j < 8; j++)
	{
		x -= 23.0f;
		lights[j + i] = Light(5.0f, sf::Vector2f(x, y), sf::Color::Black);
	}

	i += j;

	for (j = 0; j < 11; j++)
	{
		y -= 23.0f;
		lights[j + i] = Light(5.0f, sf::Vector2f(x, y), sf::Color::Black);
	}
}
