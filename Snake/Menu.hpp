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
		void HandleEvents(sf::RenderWindow& window, sf::Event& event, IGameState& gameState);
		void HandleDrawings(sf::RenderWindow& window);

	private:
		Panel panel;
		sf::Sprite background;
		sf::SoundBuffer hoverBuffer;
		sf::SoundBuffer clickBuffer;
		sf::Sound hover;
		sf::Sound click;
		bool hasPlayedSound;
		void PlayHoverSound();
};

