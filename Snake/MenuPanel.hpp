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

class MenuPanel
{
	public:
		MenuPanel();
		MenuPanel(sf::RenderWindow& window, sf::Font& font);
		~MenuPanel();
		void Render(sf::RenderWindow& window);
		void HandleEvents(sf::RenderWindow& window, sf::Event& event, IGameState& gameState);
		void SetTexture(sf::Texture& texture);

	private:
		std::unordered_map<std::string, Button*> buttonMap;
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Sprite background;
		sf::Text menuText;
		Button optionsButton;
		Button startButton;
		Button exitButton;
		sf::SoundBuffer hoverBuffer;
		sf::SoundBuffer clickBuffer;
		sf::Sound hover;
		sf::Sound click;
		bool hasPlayedSound;
		void PlayHoverSound();
};

