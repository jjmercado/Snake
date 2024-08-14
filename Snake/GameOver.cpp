#include "GameOver.hpp"

GameOver::GameOver()
{
}

GameOver::GameOver(sf::RenderWindow& window, sf::Font& font): gameOverPanel(window, font)
{

}

GameOver::~GameOver()
{
}

void GameOver::HandleDrawings(sf::RenderWindow& window)
{

    gameOverPanel.Render(window);
}

void GameOver::HandleEvents(sf::Event& event, sf::RenderWindow& window, IGameState& gameState, Charakter& charakter, Apple& apple)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if (gameOverPanel.GetButton("PlayAgain").IsMouseOnButton(window))
        {
            gameState.SetState(IGameState::Playing);
            charakter.Reset(window, apple);
        }
        else if (gameOverPanel.GetButton("Options").IsMouseOnButton(window))
        {
            // TODO: Implement options menu
        }
        else if (gameOverPanel.GetButton("Exit").IsMouseOnButton(window))
        {
            window.close();
        }
    }
}

void GameOver::HandleUpdate(sf::Time deltaTime)
{
}
