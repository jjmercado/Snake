#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "TextureManager.hpp"
#include <iostream>
#include "Apple.hpp"
#include <cmath>
#include <queue>

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
		sf::Vector2f headPosition;
		sf::Vector2f tailPosition;
		sf::Sprite head;
		sf::Sprite tail;
		std::list<sf::Sprite> bodyParts;
		std::list<sf::Vector2f> positions;
		sf::IntRect rect;
		bool isLerping;
		sf::Clock directionChangeClock;
		sf::Vector2f Lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t);
};

