#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "TextureManager.hpp"
#include <iostream>

class Charakter
{
	public:
		Charakter();
		~Charakter();
		void Render(sf::RenderWindow& window);
		void Update(sf::Time deltaTime);

	private:
		sf::Sprite sprite;
		std::list<sf::Sprite> sprites;
};

