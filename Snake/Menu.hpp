#pragma once
#include <SFML/Graphics.hpp>
#include "Panel.hpp"
#include "IGameState.hpp"
#include <SFML/Audio.hpp>

class Menu
{
	public:
		Menu();
		Menu(sf::RenderWindow& window, sf::Font& font);
		void handleEvents(sf::RenderWindow& window, sf::Event& event, IGameState& gameState);
		void handleDrawings(sf::RenderWindow& window);

	private:
		Panel panel;
		sf::Sprite background;
		sf::SoundBuffer buffer;
		sf::Sound sound;
		bool hasPlayedSound = false;
};

