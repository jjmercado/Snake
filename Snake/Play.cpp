#include "Play.hpp"

Play::Play(sf::RenderWindow& window, sf::Font& font)
{
	background.setTexture(TextureManager::getTexture("playingBackground"));
}

void Play::handleEvents(sf::RenderWindow& window, sf::Event& event, IGameState& gameState)
{
}

void Play::handleDrawings(sf::RenderWindow& window)
{
	window.draw(background);
}
