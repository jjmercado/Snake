#include "Menu.hpp"

Menu::Menu()
{
}

Menu::Menu(sf::RenderWindow& window, sf::Font& font) : panel(window, font)
{

}

void Menu::HandleEvents(sf::RenderWindow& window, sf::Event& event, IGameState& gameState)
{
	panel.HandleEvents(window, event, gameState);
}

void Menu::HandleDrawings(sf::RenderWindow& window)
{
	window.draw(background);
    panel.Render(window);
}


