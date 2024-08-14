#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "Button.hpp"
#include "TextureManager.hpp"
#include <SFML/Audio.hpp>
#include "Charakter.hpp"

class GameOverPanel
{
	public:
		GameOverPanel();
		GameOverPanel(sf::RenderWindow& window, sf::Font& font);
		void Render(sf::RenderWindow& window);
		void HandleEvents(sf::Event& event, sf::RenderWindow& window, IGameState& gameState, Charakter& charakter, Apple& apple);
		void SetTexture(sf::Texture& texture);

	private:
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

