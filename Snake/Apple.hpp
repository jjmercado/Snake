#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.hpp"
#include <iostream>

class Apple
{
	public:
		Apple();
		void Render(sf::RenderWindow& window);
		void Update();
		sf::IntRect GetRect();
		void SetPosition(const sf::Vector2f& position);

	private:
		sf::Sprite sprite;
		sf::Vector2f position;
		sf::IntRect rect;
};

