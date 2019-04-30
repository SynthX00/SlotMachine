#include "Reel.h"

Reel::Reel()
{
}

Reel::Reel(float w, float h, sf::Vector2f pos)
{
	width = w;
	height = h;

	body = sf::RectangleShape(sf::Vector2f(w, h));
	body.setPosition(pos);
	
	value = 2;
	anim = false;
	animLength = 3.0f;
}

Reel::~Reel()
{
}

int Reel::GetValue()
{
	return value;
}

void Reel::GenerateValue()
{
	value = rand() % 3 + 1;
}

void Reel::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}

void Reel::LoadTextures()
{
	tex[0].loadFromFile("Resources/cherry.png");
	tex[1].loadFromFile("Resources/lucky7.png");
	tex[2].loadFromFile("Resources/dollar.png");

	body.setTexture(&tex[1]);
}

void Reel::ChangeTexture()
{

	int temp = rand() % 3;
	body.setTexture(&tex[temp]);

}

void Reel::Animate(float switchTime, float deltaTime)
{
	if (anim)
	{
		elapsedTime += deltaTime;
		animLength -= deltaTime;

		if (elapsedTime >= switchTime)
		{
			elapsedTime -= switchTime;
			ChangeTexture();
		}

		if (animLength <= 0)
		{
			SetAnim(false);
		}
	}
}

void Reel::SetAnim(bool value)
{
	anim = value;
	elapsedTime = 0.0f;
	if (!anim)
	{
		animLength = 3.0f;
		body.setTexture(&tex[this->value - 1]);
	}
}

bool Reel::GetAnim()
{
	return anim;
}
