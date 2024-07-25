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
		void SetDirection(const sf::Vector2f& position);
		sf::Vector2f GetDirection();
		void SetPosition(const sf::Vector2f& position);
		sf::Vector2f GetPosition();
		sf::IntRect GetRect();
		void SetTexture(sf::Texture& texture);
		void Render(sf::RenderWindow& window);
		void RenderCollisionRect(sf::RenderWindow& window);
		void Update(const sf::Vector2f prev);
		sf::Vector2f& GetLastPosition();
		sf::Vector2f& GetLastDirection();
		void CollisionPart();
		sf::IntRect GetColisionRect();
		void RotateBodyPart();

	private:
		sf::Sprite collision;
		sf::Sprite bodyPart;
		sf::Texture collisionTexture;
		//sf::Vector2f lastPosition;
		//sf::Vector2f lastDirection;
		sf::Vector2f direction;
		std::deque<sf::Vector2f> directions;
		std::deque<sf::Vector2f> positions;
		int dynamicCounter;
};