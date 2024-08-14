#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "Button.hpp"
#include "TextureManager.hpp"
#include <SFML/Audio.hpp>

class GameOverPanel
{
	public:
		GameOverPanel();
		GameOverPanel(sf::RenderWindow& window, sf::Font& font);
		void Render(sf::RenderWindow& window);
		Button& GetButton(const std::string& buttonName);
		void SetTexture(sf::Texture& texture);

	private:
		std::unordered_map<std::string, Button*> buttonMap;
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Text menuText;
		Button optionsButton;
		Button playAgain;
		Button exitButton;
		sf::SoundBuffer hoverBuffer;
		sf::SoundBuffer clickBuffer;
		sf::Sound hover;
		sf::Sound click;
		bool hasPlayedSound;
		void PlayHoverSound();
};

