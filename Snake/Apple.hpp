#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.hpp"
#include <random>

class Apple
{
	public:
		Apple();
		void Render(sf::RenderWindow& window);
		void Update();

	private:
		sf::Sprite sprite;
		sf::Vector2f position;
};

