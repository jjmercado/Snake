#pragma once
#include "TextureManager.hpp"
#include <SFML/Graphics.hpp>
#include "IGameState.hpp"
#include "Charakter.hpp"
#include "Apple.hpp"

class Play
{
	public:
		Play(sf::RenderWindow& window, sf::Font& font);
		void HandleEvents(sf::RenderWindow& window, sf::Event& event, IGameState& gameState);
		void HandleDrawings(sf::RenderWindow& window);
		void HandleUpdate(sf::Time deltaTime, IGameState& gameState);
		Charakter& GetCharakter();
		Apple& GetApple();

	private:
		Charakter charakter;
		sf::Sprite background;
		Apple apple;
};

