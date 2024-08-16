#include "MenuPanel.hpp"

MenuPanel::MenuPanel()
{
}

MenuPanel::MenuPanel(sf::RenderWindow& window, sf::Font& font) : Panel(window, font)
{
	background.setTexture(TextureManager::GetTexture("startMenuBackground"));

	SetString("Snake");
	SetText("first", "Start");
	SetText("second", "Options");
	SetText("third", "Exit");
}

MenuPanel::~MenuPanel()
{
}

void MenuPanel::Render(sf::RenderWindow& window)
{
	window.draw(background);
	Panel::Render(window);
}

void MenuPanel::HandleEvents(sf::RenderWindow& window, sf::Event& event, IGameState& gameState)
{
	Panel::HandleEvents(window, event, gameState, gameState.Playing);
}
