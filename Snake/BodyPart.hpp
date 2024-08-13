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
		void SetDirection(const sf::Vector2f& dir);
		sf::Vector2f GetPosition();
		void ChangeTailTexture();
		sf::Vector2f& GetLastPosition();
		sf::IntRect GetCollisionRect();
		sf::Sprite bodyPart;
		void RenderBodyParts();
		void RenderCurveBodyParts(std::list<BodyPart>::iterator itr, std::list<BodyPart>::iterator listEnd);
		void SetPosition(const sf::Vector2f& position);
		void SetTexture(sf::Texture& texture);
		void Render(sf::RenderWindow& window);
		void SavePosition();

	private:
		std::deque<sf::Vector2f> positions;
		sf::IntRect collisionRect;
		sf::Vector2f direction;
		sf::Clock clock;
		int maxListValue;
		sf::Vector2f CheckDir();
};