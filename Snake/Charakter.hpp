#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "TextureManager.hpp"
#include <iostream>
#include "Apple.hpp"
#include <cmath>
#include <queue>
#include "BodyPart.hpp"
#include "IGameState.hpp"

class Charakter
{
	public:
		Charakter();
		Charakter(sf::RenderWindow& window);
		~Charakter();
		void Events(sf::Event& event);
		void Render(sf::RenderWindow& window);
		void Update(sf::Time deltaTime, IGameState& gameState);
		void ChangeHeadTexture();
		void ChangeTailTexture();
		void Collision(const sf::IntRect& rect, Apple& apple);
		void AddBodyPart();
		void Reset(sf::RenderWindow& window, Apple& apple);
		sf::Vector2f CalculateTargetPosition(sf::Time deltaTime);

	private:
		void BodyPartCollision(const sf::IntRect& bodyPartRect, IGameState& gameState);
		bool CheckBoundaries();
		float speed;
		int maxValues;
		sf::Vector2f targetPosition;
		sf::Vector2f direction;
		std::list<BodyPart> snakeBodyParts;
		sf::IntRect snakeHeadRect;
		bool isLerping;
		sf::Clock directionChangeClock;
		sf::Clock testClock;
		float timer;
		sf::Vector2f Lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t);
		int counter;
		sf::Vector2f lastPosition;
		sf::Vector2f lastDirection;
		bool isBodyCollisionActive;
		sf::Vector2f rndApplePos;
};

