#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.hpp"
#include <unordered_map>
#include <string>
#include <stdexcept>

class Panel
{
	public:
		Panel(sf::RenderWindow& window, sf::Font& font);
		bool LoadTexture(std::string filePath);

		void Render(sf::RenderWindow& window);
		Button GetButton(const std::string& buttonName);

	private:
		std::unordered_map<std::string, Button*> buttonMap;

		sf::Texture texture;
		sf::Sprite sprite;
		sf::Text menuText;

		Button startButton;
		Button optionsButton;
		Button exitButton;
};

