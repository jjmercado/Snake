#include "Panel.hpp"

Panel::Panel()
{
}

Panel::Panel(sf::RenderWindow& window, sf::Font& font) : firstButton(font), secondButton(font), thirdButton(font)
{
	sprite.setTexture(TextureManager::GetTexture("panel"));

	sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2));
	sprite.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));

	menuText.setFont(font);
	menuText.setCharacterSize(40);
	menuText.setFillColor(sf::Color::White);
	menuText.setPosition(sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 2) - 165));

	firstButton.SetSprite(TextureManager::GetTexture("yellowButton"));
	firstButton.SetPosition(sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 2) - 50));
	firstButton.SetTextPosition(sf::Vector2f(window.getSize().x / 2 - 55, (window.getSize().y / 2) - 70));

	secondButton.SetSprite(TextureManager::GetTexture("blueButton"));
	secondButton.SetPosition(sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 2) + 20));
	secondButton.SetTextPosition(sf::Vector2f(window.getSize().x / 2 - 75, (window.getSize().y / 2)));

	thirdButton.SetSprite(TextureManager::GetTexture("blueButton"));
	thirdButton.SetPosition(sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 2) + 90));
	thirdButton.SetTextPosition(sf::Vector2f(window.getSize().x / 2 - 40, (window.getSize().y / 2) + 70));

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

Panel::~Panel()
{
}

void Panel::Render(sf::RenderWindow& window)
{
	window.draw(sprite);
	firstButton.Render(window);
	secondButton.Render(window);
	thirdButton.Render(window);
	window.draw(menuText);

	if (firstButton.IsMouseOnButton(window))
	{
		firstButton.SetSprite(TextureManager::GetTexture("blueButton13"));
		firstButton.SetTextFillColor(sf::Color::Black);
		PlayHoverSound();
	}
	else if (secondButton.IsMouseOnButton(window))
	{
		secondButton.SetSprite(TextureManager::GetTexture("yellowButton"));
		PlayHoverSound();
	}
	else if (thirdButton.IsMouseOnButton(window))
	{
		thirdButton.SetSprite(TextureManager::GetTexture("yellowButton"));
		PlayHoverSound();
	}
	else
	{
		firstButton.SetTextFillColor(sf::Color::White);
		firstButton.SetSprite(TextureManager::GetTexture("yellowButton"));
		secondButton.SetSprite(TextureManager::GetTexture("blueButton"));
		thirdButton.SetSprite(TextureManager::GetTexture("blueButton"));
		hasPlayedSound = false;
	}
}

void Panel::HandleEvents(sf::RenderWindow& window, sf::Event& event, IGameState& gameState, IGameState::GameState newState)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		if (firstButton.IsMouseOnButton(window))
		{
			gameState.SetState(newState);
			click.play();
		}
		else if (secondButton.IsMouseOnButton(window))
		{
			// TODO: Implement options menu
			click.play();
		}
		else if (thirdButton.IsMouseOnButton(window))
		{
			window.close();
			click.play();
		}
	}
}

void Panel::SetString(const std::string& text)
{
	menuText.setString(text);
	menuText.setOrigin(menuText.getLocalBounds().width / 2, menuText.getLocalBounds().height / 2);
}

void Panel::SetText(std::string buttonName, const std::string& text)
{
	if (buttonName == "first")
	{
		firstButton.SetText(text);
	}
	else if (buttonName == "second")
	{
		secondButton.SetText(text);
	}
	else if (buttonName == "third")
	{
		thirdButton.SetText(text);
	}
	else
	{
		throw std::invalid_argument("Invalid button name");
	}
}

void Panel::SetButtonTextPosition(std::string buttonName, sf::Vector2f position)
{
	if (buttonName == "first")
	{
		firstButton.SetTextPosition(position);
	}
	else if (buttonName == "second")
	{
		secondButton.SetTextPosition(position);
	}
	else if (buttonName == "third")
	{
		thirdButton.SetTextPosition(position);
	}
	else
	{
		throw std::invalid_argument("Invalid button name");
	}
}

void Panel::PlayHoverSound()
{
	if (hover.getStatus() != sf::Sound::Playing && !hasPlayedSound)
	{
		hasPlayedSound = true;
		hover.play();
	}
}

Button& Panel::GetFirstButton()
{
	return firstButton;
}
