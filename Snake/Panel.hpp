#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.hpp"

class Panel
{
	public:
		Panel(sf::RenderWindow& window, sf::Font& font);
		bool LoadTexture(std::string filePath);

		void Render(sf::RenderWindow& window);

	private:
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Text menuText;

		Button startButton;
		Button optionsButton;
		Button exitButton;
};

