#pragma once
#include <SFML/Graphics.hpp>

class BodyPart
{
	public:
		BodyPart(sf::Texture& texture);
		~BodyPart();
		void SetPosition(const sf::Vector2f& position);
		sf::Vector2f GetPosition();
		sf::IntRect GetRect();
		void Render(sf::RenderWindow& window);
		void Update(const sf::Vector2f& prevPos);

	private:
		sf::Sprite bodyPart;
		sf::Vector2f targetPosition;
		sf::Vector2f direction;
		sf::Clock directionChangeClock;
		sf::IntRect rect;
		sf::Clock clock;
		float currentTime;
		float lastUpdateTime;
		float delay;
};

