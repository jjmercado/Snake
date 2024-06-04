#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Button
{
	public:
		Button();
		bool LoadTexture(std::string filePath);
		void SetPosition(sf::Vector2f position);

		void SetText(std::string text);

		void SetTextPosition(sf::Vector2f position);

		void Render(sf::RenderWindow& window);
		bool LoadTexture(std::string filePath, sf::IntRect rect);

	private:
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Text text;
		sf::Font font;
};

