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
		void handleDrawings(sf::RenderWindow& window);
		void handleEvents(sf::Event& event, sf::RenderWindow& window, IGameState& gameState, Charakter& charakter, Apple& apple);
		void handleUpdate(sf::Time deltaTime);

	private:
		GameOverPanel gameOverPanel;
		sf::SoundBuffer hoverBuffer;
		sf::SoundBuffer clickBuffer;
		sf::Sound hover;
		sf::Sound click;
		bool hasPlayedSound;
};

