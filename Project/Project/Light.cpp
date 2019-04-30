#include "Light.h"


Light::Light()
{
}

Light::Light(float r, sf::Vector2f pos, sf::Color c)
{
	rad = r;
	clr = c;

	body = sf::CircleShape(r);
	body.setFillColor(c);
	body.setPosition(pos);
}

Light::~Light()
{
}

void Light::ChangeLight(sf::Color c)
{
	body.setFillColor(c);
}

void Light::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}
