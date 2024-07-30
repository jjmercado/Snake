#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.hpp"
#include <iostream>

class Apple
{
	public:
		Apple();
		sf::IntRect GetRect();
		void Render(sf::RenderWindow& window);
		void Update();
		void SetPosition(const sf::Vector2f& position);
		void Animation();

	private:
		sf::Sprite sprite;
		sf::Vector2f position;
		sf::IntRect rect;
		float animationSpeed;
		sf::Clock clock;
};

