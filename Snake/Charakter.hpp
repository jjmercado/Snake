#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "TextureManager.hpp"
#include <iostream>
#include "Apple.hpp"

class Charakter
{
	public:
		Charakter(sf::RenderWindow& window);
		~Charakter();
		void Events(sf::Event& event);
		void Render(sf::RenderWindow& window);
		void Update(sf::Time deltaTime);
		void Move(sf::Time deltaTime);
		void Collision(const sf::IntRect& rect, Apple& apple);

	private:
		float speed;
		sf::Vector2f direction;
		sf::Sprite sprite;
		std::list<sf::Sprite> sprites;
		sf::IntRect rect;
};

