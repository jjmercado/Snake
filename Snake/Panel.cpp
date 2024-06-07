#include "Panel.hpp"

Panel::Panel(sf::RenderWindow& window, sf::Font& font) : startButton(font), optionsButton(font), exitButton(font)
{
	buttonMap["Start"] = &startButton;
	buttonMap["Options"] = &optionsButton;
	buttonMap["Exit"] = &exitButton;

	SetTexture(TextureManager::getTexture("panel"));

	sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2));
	sprite.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));

	menuText.setFont(font);
	menuText.setCharacterSize(40);
	menuText.setFillColor(sf::Color::White);
	menuText.setString("Snake");
	menuText.setOrigin(menuText.getLocalBounds().width / 2, menuText.getLocalBounds().height / 2);
	menuText.setPosition(sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 2) - 165));

	startButton.SetSprite(TextureManager::getTexture("yellowButton"));
	startButton.SetPosition(sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 2) - 50));
	startButton.SetText("Start");
	startButton.SetTextPosition(sf::Vector2f(window.getSize().x / 2 - 55, (window.getSize().y / 2) - 70));

	optionsButton.SetSprite(TextureManager::getTexture("blueButton"));
	optionsButton.SetPosition(sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 2) + 20));
	optionsButton.SetText("Options");
	optionsButton.SetTextPosition(sf::Vector2f(window.getSize().x / 2 - 75, (window.getSize().y / 2)));

	exitButton.SetSprite(TextureManager::getTexture("blueButton"));
	exitButton.SetPosition(sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 2) + 90));
	exitButton.SetText("Exit");
	exitButton.SetTextPosition(sf::Vector2f(window.getSize().x / 2 - 40, (window.getSize().y / 2) + 70));
}

void Panel::Render(sf::RenderWindow& window)
{
	window.draw(sprite);
	startButton.Render(window);
	optionsButton.Render(window);
	exitButton.Render(window);
	window.draw(menuText);
}

Button& Panel::GetButton(const std::string& buttonName)
{
	auto it = buttonMap.find(buttonName);
	if (it != buttonMap.end())
	{
		return *(it->second);
	}
	throw std::invalid_argument("Button not found: " + buttonName);
}

void Panel::SetTexture(sf::Texture& texture)
{
	sprite.setTexture(texture);
}
