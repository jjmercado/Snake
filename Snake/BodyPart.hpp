#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include "TextureManager.hpp"
#include <iostream>

class BodyPart
{
	public:
		BodyPart(sf::Texture& texture, std::string name, sf::Vector2f prev);
		~BodyPart();
		void SetDirection(const sf::Vector2f& position);
		sf::Vector2f GetDirection();
		void SetPosition(const sf::Vector2f& position);
		sf::Vector2f GetPosition();
		sf::IntRect GetRect();
		void SetTexture(sf::Texture& texture);
		void Render(sf::RenderWindow& window);
		void Update(const sf::Vector2f prev);
		sf::Vector2f& GetLastPosition();
		sf::Vector2f& GetLastDirection();


	private:
		sf::Sprite bodyPart;
		sf::Vector2f lastPosition;
		sf::Vector2f lastDirection;
		sf::Vector2f direction;
		std::list<sf::Vector2f> directions;
		std::list<sf::Vector2f> positions;
		std::string name;
};