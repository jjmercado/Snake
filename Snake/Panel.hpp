#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.hpp"
#include <unordered_map>
#include <string>
#include <stdexcept>
#include "TextureManager.hpp"

class Panel
{
	public:
		Panel();
		Panel(sf::RenderWindow& window, sf::Font& font);

		void Render(sf::RenderWindow& window);
		Button& GetButton(const std::string& buttonName);
		void SetTexture(sf::Texture& texture);

	private:
		std::unordered_map<std::string, Button*> buttonMap;
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Text menuText;

		Button optionsButton;
		Button startButton;
		Button exitButton;
};

