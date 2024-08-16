#pragma once
#include <stdexcept>
#include "TextureManager.hpp"
#include <SFML/Audio.hpp>
#include "IGameState.hpp"
#include "Button.hpp"
#include "TextureManager.hpp"

class Panel
{
	public:
		Panel();
		Panel(sf::RenderWindow& window, sf::Font& font);
		~Panel();
		virtual void Render(sf::RenderWindow& window);
		virtual void HandleEvents(sf::RenderWindow& window, sf::Event& event, IGameState& gameState, IGameState::GameState newState);

	protected:
		void SetString(const std::string& text);
		void SetText(std::string buttonName, const std::string& text);
		void SetButtonTextPosition(std::string buttonName, sf::Vector2f position);
		void PlayHoverSound();
		bool hasPlayedSound;
		sf::Sound click;
		Button& GetFirstButton();

	private:
		Button firstButton;
		Button secondButton;
		Button thirdButton;
		sf::Text menuText;
		sf::Texture texture;
		sf::Sprite sprite;
		sf::SoundBuffer hoverBuffer;
		sf::SoundBuffer clickBuffer;
		sf::Sound hover;

};

