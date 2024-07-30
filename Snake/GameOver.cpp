#include "GameOver.hpp"

GameOver::GameOver()
{
}

GameOver::GameOver(sf::RenderWindow& window, sf::Font& font): gameOverPanel(window, font)
{
    hasPlayedSound = false;
    if (!hoverBuffer.loadFromFile("hover.wav"))
    {
        throw std::runtime_error("Failed to load audio file: random.wav");
    }

    if (!clickBuffer.loadFromFile("click.mp3"))
    {
        throw std::runtime_error("Failed to load audio file: click.wav");
    }

    click.setBuffer(clickBuffer);
    hover.setBuffer(hoverBuffer);
}

GameOver::~GameOver()
{
}

void GameOver::HandleDrawings(sf::RenderWindow& window)
{
    if (gameOverPanel.GetButton("PlayAgain").IsMouseOnButton(window))
    {
        gameOverPanel.GetButton("PlayAgain").SetSprite(TextureManager::GetTexture("blueButton13"));
        gameOverPanel.GetButton("PlayAgain").SetTextFillColor(sf::Color::Black);
        PlayHoverSound();
    }
    else if (gameOverPanel.GetButton("Options").IsMouseOnButton(window))
    {
        gameOverPanel.GetButton("Options").SetSprite(TextureManager::GetTexture("yellowButton"));
        PlayHoverSound();
    }
    else if (gameOverPanel.GetButton("Exit").IsMouseOnButton(window))
    {
        gameOverPanel.GetButton("Exit").SetSprite(TextureManager::GetTexture("yellowButton"));
        PlayHoverSound();
    }
    else
    {
        gameOverPanel.GetButton("PlayAgain").SetTextFillColor(sf::Color::White);
        gameOverPanel.GetButton("PlayAgain").SetSprite(TextureManager::GetTexture("yellowButton"));
        gameOverPanel.GetButton("Options").SetSprite(TextureManager::GetTexture("blueButton"));
        gameOverPanel.GetButton("Exit").SetSprite(TextureManager::GetTexture("blueButton"));
        hasPlayedSound = false;
    }
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
            click.play();
        }
        else if (gameOverPanel.GetButton("Options").IsMouseOnButton(window))
        {
            click.play();
            // TODO: Implement options menu
        }
        else if (gameOverPanel.GetButton("Exit").IsMouseOnButton(window))
        {
            click.play();
            window.close();
        }
    }
}

void GameOver::HandleUpdate(sf::Time deltaTime)
{
}

void GameOver::PlayHoverSound()
{
    if (hover.getStatus() != sf::Sound::Playing && !hasPlayedSound)
    {
        hasPlayedSound = true;
        hover.play();
    }
}
