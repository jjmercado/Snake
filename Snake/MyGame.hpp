#pragma once
#include "Game.hpp"
#include "Panel.hpp"
#include <iostream>

class MyGame : public Game
{
	public:
		MyGame();
		enum GameState { StartMenu, Playing, GameOver };

	protected:
		void ProcessEvents() override;
		void Update(sf::Time deltaTime) override;
		void Render() override;

		void handleStartMenuEvents(sf::Event& event);
		void handleStartMenuDrawings(sf::RenderWindow& window);
		void handlePlayingEvents(sf::Event& event);
		void handleGameOver(sf::Event& event);

	private:
		GameState gameState;

		Panel startMenuPanel;
};

