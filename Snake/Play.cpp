#include "Play.hpp"

Play::Play(sf::RenderWindow& window, sf::Font& font) : charakter(window)
{
	background.setTexture(TextureManager::getTexture("playingBackground"));
}

void Play::handleEvents(sf::RenderWindow& window, sf::Event& event, IGameState& gameState)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			gameState.SetState(IGameState::StartMenu);
		}

		charakter.Events(event);
	}
}

void Play::handleDrawings(sf::RenderWindow& window)
{
	window.draw(background);
	charakter.Render(window);
	apple.Render(window);
}

void Play::handleUpdate(sf::Time deltaTime)
{
	charakter.Update(deltaTime);
}
