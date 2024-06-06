#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Button
{
	public:
		Button();
		Button(sf::Font& font);
		bool LoadTexture(std::string filePath);
		void SetPosition(sf::Vector2f position);

		void SetText(std::string text);

		void SetTextPosition(sf::Vector2f position);

		void Render(sf::RenderWindow& window);

		bool IsMouseOnButton(sf::RenderWindow& window);

		bool IsButtonPressed(sf::RenderWindow& window);
		void SetSprite(std::string filePath);

	private:
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Text text;
};

