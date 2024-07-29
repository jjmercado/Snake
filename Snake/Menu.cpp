#include "Menu.hpp"

Menu::Menu()
{
}

Menu::Menu(sf::RenderWindow& window, sf::Font& font) : panel(window, font)
{
    if (!hoverBuffer.loadFromFile("hover.wav"))
    {
        throw std::runtime_error("Failed to load audio file: random.wav");
    }

    if(!clickBuffer.loadFromFile("click.mp3"))
	{
		throw std::runtime_error("Failed to load audio file: click.wav");
	}

    click.setBuffer(clickBuffer);
    hover.setBuffer(hoverBuffer);
    background.setTexture(TextureManager::getTexture("startMenuBackground"));
}

void Menu::handleEvents(sf::RenderWindow& window, sf::Event& event, IGameState& gameState)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if (panel.GetButton("Start").IsMouseOnButton(window))
        {
            click.play();
            gameState.SetState(IGameState::Playing);

        }
        else if (panel.GetButton("Options").IsMouseOnButton(window))
        {
            // TODO: Implement options menu
            click.play();
        }
        else if (panel.GetButton("Exit").IsMouseOnButton(window))
        {
            click.play();
            window.close();
        }
    }
}

void Menu::handleDrawings(sf::RenderWindow& window)
{
	window.draw(background);
    if (panel.GetButton("Start").IsMouseOnButton(window))
    {
        panel.GetButton("Start").SetSprite(TextureManager::getTexture("blueButton13"));
        panel.GetButton("Start").SetTextFillColor(sf::Color::Black);

        if (hover.getStatus() != sf::Sound::Playing && !hasPlayedSound)
        {
            hasPlayedSound = true;
            hover.play();
        }
    }
    else if (panel.GetButton("Options").IsMouseOnButton(window))
    {
        panel.GetButton("Options").SetSprite(TextureManager::getTexture("yellowButton"));
        if (hover.getStatus() != sf::Sound::Playing && !hasPlayedSound)
        {
            hasPlayedSound = true;
            hover.play();
        }
    }
    else if (panel.GetButton("Exit").IsMouseOnButton(window))
    {
        panel.GetButton("Exit").SetSprite(TextureManager::getTexture("yellowButton"));
        if (hover.getStatus() != sf::Sound::Playing && !hasPlayedSound)
        {
            hasPlayedSound = true;
            hover.play();
        }
    }
    else
    {
        panel.GetButton("Start").SetTextFillColor(sf::Color::White);
        panel.GetButton("Start").SetSprite(TextureManager::getTexture("yellowButton"));
        panel.GetButton("Options").SetSprite(TextureManager::getTexture("blueButton"));
        panel.GetButton("Exit").SetSprite(TextureManager::getTexture("blueButton"));
        hasPlayedSound = false;
    }
    panel.Render(window);
}
