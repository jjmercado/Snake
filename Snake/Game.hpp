#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureManager.hpp"

class Game
{
	public:
		Game();
		virtual ~Game();
		void Run();

	protected:
		virtual void ProcessEvents();
		virtual void Update(sf::Time deltaTime);
		virtual void Render();
		sf::RenderWindow window;
		sf::Clock fpsClock;
		sf::Font font;
		unsigned int frameCount;
};

