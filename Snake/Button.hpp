#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Button
{
	public:
		Button();
		void SetPosition(sf::Vector2f position);

		void SetText(std::string text);

		void SetTextPosition(sf::Vector2f position);

		void Render(sf::RenderWindow& window);
		bool LoadTexture(std::string filePath);
		bool LoadTexture(sf::IntRect rect);

	private:
		sf::Texture textureSpriteSheet;
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Text text;
		sf::Font font;


		bool LoadSpriteSheet(std::string filePath);
};

