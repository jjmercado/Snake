#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.hpp"
#include <unordered_map>
#include <string>
#include <stdexcept>
#include "TextureManager.hpp"
#include <SFML/Audio.hpp>
#include "IGameState.hpp"
#include "Panel.hpp"

class MenuPanel : public Panel
{
	public:
		MenuPanel();
		MenuPanel(sf::RenderWindow& window, sf::Font& font);
		~MenuPanel();
		void Render(sf::RenderWindow& window);
		void HandleEvents(sf::RenderWindow& window, sf::Event& event, IGameState& gameState);
		void SetTexture(sf::Texture& texture);

	private:
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Sprite background;
		sf::Text menuText;
		Button optionsButton;
		Button startButton;
		Button exitButton;
};

