#include "GameOverPanel.hpp"

GameOverPanel::GameOverPanel()
{
}

GameOverPanel::GameOverPanel(sf::RenderWindow& window, sf::Font& font) : Panel(window, font)
{
	SetString("Lost");
	SetText("first", "Restart");
	SetText("second", "Options");
	SetText("third", "Exit");
	SetButtonTextPosition("first", sf::Vector2f(window.getSize().x / 2 - 85, (window.getSize().y / 2) - 70));
}

void GameOverPanel::HandleEvents(sf::Event& event, sf::RenderWindow& window, IGameState& gameState, Charakter& charakter, Apple& apple)
{
	Panel::HandleEvents(window, event, gameState, gameState.Playing);
	
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		if (GetFirstButton().IsMouseOnButton(window))
		{
			charakter.Reset(window, apple);
		}
	}
}

void GameOverPanel::Render(sf::RenderWindow& window)
{
	Panel::Render(window);
}