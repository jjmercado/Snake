#include "GameOverPanel.hpp"

GameOverPanel::GameOverPanel()
{
}

GameOverPanel::GameOverPanel(sf::RenderWindow& window, sf::Font& font) : playAgain(font), optionsButton(font), exitButton(font)
{
	buttonMap["PlayAgain"] = &playAgain;
	buttonMap["Options"] = &optionsButton;
	buttonMap["Exit"] = &exitButton;

	SetTexture(TextureManager::GetTexture("panel"));

	sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2));
	sprite.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));

	menuText.setFont(font);
	menuText.setCharacterSize(40);
	menuText.setFillColor(sf::Color::White);
	menuText.setString("Lost");
	menuText.setOrigin(menuText.getLocalBounds().width / 2, menuText.getLocalBounds().height / 2);
	menuText.setPosition(sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 2) - 165));

	playAgain.SetSprite(TextureManager::GetTexture("yellowButton"));
	playAgain.SetPosition(sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 2) - 50));
	playAgain.SetText("Restart");
	playAgain.SetTextPosition(sf::Vector2f(window.getSize().x / 2 - 85, (window.getSize().y / 2) - 70));

	optionsButton.SetSprite(TextureManager::GetTexture("blueButton"));
	optionsButton.SetPosition(sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 2) + 20));
	optionsButton.SetText("Options");
	optionsButton.SetTextPosition(sf::Vector2f(window.getSize().x / 2 - 75, (window.getSize().y / 2)));

	exitButton.SetSprite(TextureManager::GetTexture("blueButton"));
	exitButton.SetPosition(sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 2) + 90));
	exitButton.SetText("Exit");
	exitButton.SetTextPosition(sf::Vector2f(window.getSize().x / 2 - 40, (window.getSize().y / 2) + 70));

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

void GameOverPanel::Render(sf::RenderWindow& window)
{
	window.draw(sprite);
	playAgain.Render(window);
	optionsButton.Render(window);
	exitButton.Render(window);
	window.draw(menuText);

	if (playAgain.IsMouseOnButton(window))
	{
		playAgain.SetSprite(TextureManager::GetTexture("blueButton13"));
		playAgain.SetTextFillColor(sf::Color::Black);
		PlayHoverSound();
	}
	else if (optionsButton.IsMouseOnButton(window))
	{
		optionsButton.SetSprite(TextureManager::GetTexture("yellowButton"));
		PlayHoverSound();
	}
	else if (exitButton.IsMouseOnButton(window))
	{
		exitButton.SetSprite(TextureManager::GetTexture("yellowButton"));
		PlayHoverSound();
	}
	else
	{
		playAgain.SetTextFillColor(sf::Color::White);
		playAgain.SetSprite(TextureManager::GetTexture("yellowButton"));
		optionsButton.SetSprite(TextureManager::GetTexture("blueButton"));
		exitButton.SetSprite(TextureManager::GetTexture("blueButton"));
		hasPlayedSound = false;
	}
}

Button& GameOverPanel::GetButton(const std::string& buttonName)
{
	if (buttonMap.empty())
	{
		throw std::invalid_argument("Button map is empty");
	}
	else
	{
		auto it = buttonMap.find(buttonName);
		if (it != buttonMap.end())
		{
			return *(it->second);
		}
		throw std::invalid_argument("Button not found: " + buttonName);
	}
}

void GameOverPanel::SetTexture(sf::Texture& texture)
{
	sprite.setTexture(texture);
}

void GameOverPanel::PlayHoverSound()
{
	if (hover.getStatus() != sf::Sound::Playing && !hasPlayedSound)
	{
		hasPlayedSound = true;
		hover.play();
	}
}
