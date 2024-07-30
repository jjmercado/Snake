#pragma once
#include <SFML/Graphics.hpp>
#include "GameOverPanel.hpp"
#include "IGameState.hpp"
#include "Charakter.hpp"
#include <SFML/Audio.hpp>

class GameOver
{
	public:
		GameOver();
		GameOver(sf::RenderWindow& window, sf::Font& font);
		~GameOver();
		void HandleDrawings(sf::RenderWindow& window);
		void HandleEvents(sf::Event& event, sf::RenderWindow& window, IGameState& gameState, Charakter& charakter, Apple& apple);
		void HandleUpdate(sf::Time deltaTime);

	private:
		GameOverPanel gameOverPanel;
		sf::SoundBuffer hoverBuffer;
		sf::SoundBuffer clickBuffer;
		sf::Sound hover;
		sf::Sound click;
		bool hasPlayedSound;
		void PlayHoverSound();
};

