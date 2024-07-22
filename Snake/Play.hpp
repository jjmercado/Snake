#pragma once
#include "TextureManager.hpp"
#include <SFML/Graphics.hpp>
#include "IGameState.hpp"
#include "Charakter.hpp"
#include "Apple.hpp"
#include "Grid.hpp"

class Play
{
	public:
		Play(sf::RenderWindow& window, sf::Font& font);
		void handleEvents(sf::RenderWindow& window, sf::Event& event, IGameState& gameState);
		void handleDrawings(sf::RenderWindow& window);
		void handleUpdate(sf::Time deltaTime, IGameState& gameState);
		Charakter* GetCharakter();

	private:
		Charakter charakter;
		sf::Sprite background;
		Apple apple;
		Grid grid;
};

