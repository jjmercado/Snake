#pragma once
#include <stdexcept>
#include "TextureManager.hpp"
#include <SFML/Audio.hpp>
#include "IGameState.hpp"
#include "Button.hpp"

class Panel
{
	public:
		Panel();
		Panel(sf::RenderWindow& window, sf::Font& font);
		~Panel();
		void Render(sf::RenderWindow& window);
		void HandleEvents(sf::RenderWindow& window, sf::Event& event, IGameState& gameState);
		void SetTexture(sf::Texture& texture);

	protected:
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Sprite background;
		sf::Text menuText;
		Button optionsButton;
		Button startButton;
		Button exitButton;
		sf::SoundBuffer hoverBuffer;
		sf::SoundBuffer clickBuffer;
		sf::Sound hover;
		sf::Sound click;
		bool hasPlayedSound;
		void PlayHoverSound();
};

