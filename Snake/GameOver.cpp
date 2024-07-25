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

void GameOver::handleDrawings(sf::RenderWindow& window)
{
    if (gameOverPanel.GetButton("PlayAgain").IsMouseOnButton(window))
    {
        gameOverPanel.GetButton("PlayAgain").SetSprite(TextureManager::getTexture("blueButton13"));
        gameOverPanel.GetButton("PlayAgain").SetTextFillColor(sf::Color::Black);
    }
    else if (gameOverPanel.GetButton("Options").IsMouseOnButton(window))
    {
        gameOverPanel.GetButton("Options").SetSprite(TextureManager::getTexture("yellowButton"));
    }
    else if (gameOverPanel.GetButton("Exit").IsMouseOnButton(window))
    {
        gameOverPanel.GetButton("Exit").SetSprite(TextureManager::getTexture("yellowButton"));
    }
    else
    {

        gameOverPanel.GetButton("PlayAgain").SetTextFillColor(sf::Color::White);
        gameOverPanel.GetButton("PlayAgain").SetSprite(TextureManager::getTexture("yellowButton"));
        gameOverPanel.GetButton("Options").SetSprite(TextureManager::getTexture("blueButton"));
        gameOverPanel.GetButton("Exit").SetSprite(TextureManager::getTexture("blueButton"));
    }
    gameOverPanel.Render(window);
}

void GameOver::handleEvents(sf::Event& event, sf::RenderWindow& window, IGameState& gameState, Charakter& charakter, Apple& apple)
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

void GameOver::handleUpdate(sf::Time deltaTime)
{
}
