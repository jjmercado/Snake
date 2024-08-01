#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <deque>
#include "TextureManager.hpp"
#include <iostream>

class BodyPart
{
	public:
		BodyPart(sf::Texture& texture, sf::Vector2f prev);
		~BodyPart();
		sf::Vector2f GetDirection();
		sf::Vector2f GetPosition();
		sf::Vector2f& GetLastPosition();
		sf::Vector2f& GetLastDirection();
		sf::IntRect GetBodyRect();
		sf::IntRect GetCollisionRect();
		sf::Sprite bodyPart;
		void RenderBodyParts();
		void SetDirection(const sf::Vector2f& position);
		void SetPosition(const sf::Vector2f& position);
		void SetTexture(sf::Texture& texture);
		void Render(sf::RenderWindow& window);
		void Update(const sf::Vector2f prev);

	private:
		std::deque<sf::Vector2f> directions;
		std::deque<sf::Vector2f> positions;
		sf::IntRect collisionRect;
		sf::Vector2f direction;
		sf::Clock clock;
		int maxListValue;
};