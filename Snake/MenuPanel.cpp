#include "MenuPanel.hpp"

MenuPanel::MenuPanel()
{
}

MenuPanel::MenuPanel(sf::RenderWindow& window, sf::Font& font) : startButton(font), optionsButton(font), exitButton(font)
{
	buttonMap["Start"] = &startButton;
	buttonMap["Options"] = &optionsButton;
	buttonMap["Exit"] = &exitButton;

	SetTexture(TextureManager::GetTexture("panel"));
	background.setTexture(TextureManager::GetTexture("startMenuBackground"));

	sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2));
	sprite.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));

	menuText.setFont(font);
	menuText.setCharacterSize(40);
	menuText.setFillColor(sf::Color::White);
	menuText.setString("Snake");
	menuText.setOrigin(menuText.getLocalBounds().width / 2, menuText.getLocalBounds().height / 2);
	menuText.setPosition(sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 2) - 165));

	startButton.SetSprite(TextureManager::GetTexture("yellowButton"));
	startButton.SetPosition(sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 2) - 50));
	startButton.SetText("Start");
	startButton.SetTextPosition(sf::Vector2f(window.getSize().x / 2 - 55, (window.getSize().y / 2) - 70));

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

MenuPanel::~MenuPanel()
{
}

void MenuPanel::Render(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(sprite);
	startButton.Render(window);
	optionsButton.Render(window);
	exitButton.Render(window);
	window.draw(menuText);

	if (startButton.IsMouseOnButton(window))
	{
		startButton.SetSprite(TextureManager::GetTexture("blueButton13"));
		startButton.SetTextFillColor(sf::Color::Black);
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
		startButton.SetTextFillColor(sf::Color::White);
		startButton.SetSprite(TextureManager::GetTexture("yellowButton"));
		optionsButton.SetSprite(TextureManager::GetTexture("blueButton"));
		exitButton.SetSprite(TextureManager::GetTexture("blueButton"));
		hasPlayedSound = false;
	}
}

void MenuPanel::HandleEvents(sf::RenderWindow& window, sf::Event& event, IGameState& gameState)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		if (startButton.IsMouseOnButton(window))
		{
			gameState.SetState(IGameState::Playing);
			click.play();
		}
		else if (optionsButton.IsMouseOnButton(window))
		{
			// TODO: Implement options menu
			click.play();
		}
		else if (exitButton.IsMouseOnButton(window))
		{
			window.close();
			click.play();
		}
	}
}

void MenuPanel::SetTexture(sf::Texture& texture)
{
	sprite.setTexture(texture);
}

void MenuPanel::PlayHoverSound()
{
	if (hover.getStatus() != sf::Sound::Playing && !hasPlayedSound)
	{
		hasPlayedSound = true;
		hover.play();
	}
}
