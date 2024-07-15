#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <list>

class BodyPart
{
	public:
		BodyPart(sf::Texture& texture, std::string name);
		~BodyPart();
		void SetPosition(const sf::Vector2f& position);
		sf::Vector2f GetPosition();
		sf::IntRect GetRect();
		void Render(sf::RenderWindow& window);
		void Update(const sf::Vector2f prev);
		sf::Vector2f& GetLastPosition();

	private:
		sf::Sprite bodyPart;
		sf::Vector2f lastPosition;
		std::list<sf::Vector2f> positions;
		std::string name;
};