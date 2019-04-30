#include "Game.h"
#include "Machine.h"
#include "Reel.h"
#include "Light.h"
#include <string>

Game::Game(sf::RenderWindow& wnd)
{
	gameState = -1;

	this->window = &wnd;
	width = window->getSize().x;
	height = window->getSize().y;

	timesPlayed = 0;
	RunGame();
}

Game::~Game()
{
}

void Game::RunGame()
{
	gameState = 0;

	sf::Clock clock;
	deltaTime = 0.0f;
	
	//Create slotmachine
	Machine slot(250.0f, 320.0f);

	//Create font to show times played and credits available
	sf::Font font;
	font.loadFromFile("Resources/BERNHC.TTF");

	sf::Text credits;
	credits.setFont(font);
	credits.setString("0");
	credits.setFillColor(sf::Color(217,65,65));
	credits.setCharacterSize(30);
	credits.setPosition(width/2, 220.0f);

	sf::Text label;
	label.setFont(font);
	label.setString("CREDITS");
	label.setFillColor(sf::Color(217, 65, 65));
	label.setCharacterSize(20);
	label.setPosition((width / 2)-23.0f, 250.0f);

	sf::Text count;
	count.setFont(font);
	count.setString("0");
	count.setFillColor(sf::Color::Black);
	count.setCharacterSize(20);
	

	//begin game loop
	while (window->isOpen())
	{
		deltaTime = clock.restart().asSeconds();


		//event listener
		sf::Event evnt;
		while (window->pollEvent(evnt)) 
		{
			switch (evnt.type) 
			{
			case sf::Event::Closed:
				window->close();
				break;

			//keyboard input
			case sf::Event::KeyPressed:
				if (evnt.key.code == sf::Keyboard::Up){		//CREDITS IN
					slot.AddCredits();
					
					//Adjust the text position depending on the number of credits
					if (slot.GetCredits() >= 100)
					{
						credits.setPosition((width / 2) - 10.0f, 220.0f);
					}else if (slot.GetCredits() >= 10)
					{
						credits.setPosition((width / 2) - 5.0f, 220.0f);
					}
				}
				if (evnt.key.code == sf::Keyboard::Down){	//CREDITS OUT
					slot.RemoveCredits();

					if (slot.GetCredits() <= 10)
					{
						credits.setPosition((width / 2), 220.0f);
					}
					else if (slot.GetCredits() <= 100)
					{
						credits.setPosition((width / 2) - 5.0f, 220.0f);
					}
				}
				if (evnt.key.code == sf::Keyboard::Enter)	//PLAY
				{
					if (gameState == 0)
					{
						timesPlayed += slot.Play(gameState);
					}
				}
				break;
			}
		}

		//Check results
		slot.CheckIfDone(gameState);


		window->clear(sf::Color::White);
		credits.setString(std::to_string(slot.GetCredits()));
		count.setString(std::to_string(timesPlayed));

		slot.AnimateLights(deltaTime, 0.05f);
		slot.r1.Animate(0.1f, deltaTime);
		slot.r2.Animate(0.1f, deltaTime);
		slot.r3.Animate(0.1f, deltaTime);

		//draw
		slot.Draw(*window);

		window->draw(credits);
		window->draw(label);
		window->draw(count);

		window->display();
	}
}
