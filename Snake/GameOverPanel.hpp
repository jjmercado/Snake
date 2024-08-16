#pragma once
#include "Charakter.hpp"
#include "Panel.hpp"

class GameOverPanel : public Panel
{
	public:
		GameOverPanel();
		GameOverPanel(sf::RenderWindow& window, sf::Font& font);
		void Render(sf::RenderWindow& window);
		void HandleEvents(sf::Event& event, sf::RenderWindow& window, IGameState& gameState, Charakter& charakter, Apple& apple);
};

