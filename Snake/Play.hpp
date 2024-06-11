#pragma once
#include <SFML/Graphics.hpp>
#include "IGameState.hpp"
#include "TextureManager.hpp"

class Play
{
	public:
		Play();
		Play(sf::RenderWindow& window, sf::Font& font);
		void handleEvents(sf::RenderWindow& window, sf::Event& event, IGameState& gameState);
		void handleDrawings(sf::RenderWindow& window);

	private:
		sf::Sprite background;
};

