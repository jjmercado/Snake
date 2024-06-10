#pragma once
#include <SFML/Graphics.hpp>
#include "Panel.hpp"
#include "IGameState.hpp"

class MyGame; // forward declaration because of circular dependency

class Menu
{
	public:
		Menu();
		Menu(sf::RenderWindow& window, sf::Font& font);
		void handleEvents(sf::RenderWindow& window, sf::Event& event, IGameState& gameState);
		void handleDrawings(sf::RenderWindow& window);

	private:
		Panel panel;
};

