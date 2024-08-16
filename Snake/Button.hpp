#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Button
{
	public:
		Button();
		Button(sf::Font& font);
		void SetPosition(sf::Vector2f position);
		void SetText(std::string text);
		void SetTextPosition(sf::Vector2f position);
		void SetTextFillColor(sf::Color color);
		void Render(sf::RenderWindow& window);
		bool IsMouseOnButton(sf::RenderWindow& window);
		void SetSprite(sf::Texture& texture);
		void SetScale(sf::Vector2f scale);

	private:
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Text text;
};

