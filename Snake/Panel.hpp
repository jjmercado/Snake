#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.hpp"

class Panel
{
	public:
		Panel();
		Panel(sf::RenderWindow& window);
		bool LoadTexture(std::string filePath);

		void Render(sf::RenderWindow& window);

	private:
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Text menuText;
		sf::Font font;

		Button startButton;
		Button optionsButton;
		Button exitButton;
};

