#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "TextureManager.hpp"
#include <iostream>

class Charakter
{
	public:
		Charakter(sf::RenderWindow& window);
		~Charakter();
		void Events(sf::Event& event);
		void Render(sf::RenderWindow& window);
		void Update(sf::Time deltaTime);
		void Move(sf::Time deltaTime);

	private:
		float speed;
		sf::Vector2f direction;
		sf::Sprite sprite;
		std::list<sf::Sprite> sprites;
};

