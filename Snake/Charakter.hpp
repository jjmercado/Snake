#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "TextureManager.hpp"
#include <iostream>
#include "Apple.hpp"
#include <cmath>

class Charakter
{
	public:
		Charakter(sf::RenderWindow& window);
		~Charakter();
		void Events(sf::Event& event);
		void Render(sf::RenderWindow& window);
		void Update(sf::Time deltaTime);
		void Move(sf::Time deltaTime);
		void MoveBodyParts(sf::Time deltaTime);
		void Collision(const sf::IntRect& rect, Apple& apple);
		void AddBodyPart(sf::Texture& texture);
		sf::Vector2f CalculateTargetPosition(sf::Time deltaTime);

	private:
		float speed;
		sf::Vector2f targetPosition;
		sf::Vector2f direction;
		std::list<sf::Sprite> sprites;
		sf::IntRect rect;
		bool isMoving;
		sf::Clock directionChangeClock;
		sf::Vector2f Lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t);
};

