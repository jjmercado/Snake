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
#include <SFML/Audio.hpp>
#include "Direction.hpp"

class Charakter
{
	public:
		Charakter();
		Charakter(sf::RenderWindow& window);
		~Charakter();
		void Events(sf::Event& event);
		void Render(sf::RenderWindow& window);
		void Update(sf::Time deltaTime, IGameState& gameState);
		void Collision(const sf::IntRect& rect, Apple& apple);
		void Reset(sf::RenderWindow& window, Apple& apple);

	private:
		void ChangeHeadTexture();
		void AddBodyPart();
		void BodyPartCollision(const sf::IntRect& bodyPartRect, IGameState& gameState);
		void CheckBoundaries();
		void StartGameOverMusic();
		void SetHeadCollisionRect();
		sf::Vector2f CalculateTargetPosition(sf::Time deltaTime);
		sf::Vector2f Lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t);
		float speed;
		float timer;
		float tileSize;
		int maxValues;
		bool isBodyCollisionActive;
		bool hasCollided;
		bool isLerping;
		std::list<BodyPart> snakeBodyParts;
		sf::Vector2f targetPosition;
		sf::Vector2f newDirection;
		sf::Vector2f direction;
		sf::Vector2f lastPosition;
		sf::Vector2f lastDirection;
		sf::Vector2f adjustApplePosition;
		sf::IntRect snakeHeadRect;
		sf::Clock directionChangeClock;
		sf::Clock testClock;
		sf::SoundBuffer eatBuffer;
		sf::SoundBuffer gameOverBuffer;
		sf::SoundBuffer moveBuffer;
		sf::Sound eat;
		sf::Sound gameOver;
		sf::Sound move;
};

