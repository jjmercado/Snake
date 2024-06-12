#pragma once
#include "TextureManager.hpp"
#include <SFML/Graphics.hpp>
#include "IGameState.hpp"
#include "Charakter.hpp"

class Play
{
	public:
		Play();
		Play(sf::RenderWindow& window, sf::Font& font);
		void handleEvents(sf::RenderWindow& window, sf::Event& event, IGameState& gameState);
		void handleDrawings(sf::RenderWindow& window);

		void handleUpdate(sf::Time deltaTime);

	private:
		sf::Sprite background;
		Charakter charakter;
};

