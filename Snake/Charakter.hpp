#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "TextureManager.hpp"
#include <iostream>
#include "Apple.hpp"
#include <cmath>
#include <queue>
#include "BodyPart.hpp"

class Charakter
{
	public:
		Charakter(sf::RenderWindow& window);
		~Charakter();
		void Events(sf::Event& event);
		void Render(sf::RenderWindow& window);
		void Update(sf::Time deltaTime);
		//void MoveHead();
		void Collision(const sf::IntRect& rect, Apple& apple);
		void AddBodyPart();
		//void Move(sf::Time deltaTime);
		sf::Vector2f CalculateTargetPosition(sf::Time deltaTime);

	private:
		float speed;
		int maxValues;
		sf::Vector2f targetPosition;
		sf::Vector2f direction;
		std::list<BodyPart> snakeBodyParts;
		std::list<sf::Vector2f> directions;
		sf::IntRect rect;
		bool isLerping;
		sf::Clock directionChangeClock;
		sf::Clock testClock;
		float timer;
		sf::Vector2f Lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t);
		int counter;
};

