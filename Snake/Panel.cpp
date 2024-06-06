#include "Panel.hpp"

Panel::Panel(sf::RenderWindow& window, sf::Font& font) : startButton(font), optionsButton(font), exitButton(font)
{
	buttonMap["Start"] = &startButton;
	buttonMap["Options"] = &optionsButton;
	buttonMap["Exit"] = &exitButton;

	LoadTexture("..\\UIpack\\PNG\\panel.png");
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
	sprite.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));

	menuText.setFont(font);
	menuText.setCharacterSize(40);
	menuText.setFillColor(sf::Color::White);
	menuText.setString("Snake");
	menuText.setOrigin(menuText.getLocalBounds().width / 2, menuText.getLocalBounds().height / 2);
	menuText.setPosition(sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 2) - 165));

	startButton.LoadTexture("..\\UIpack\\PNG\\yellow_button00.png");
	startButton.SetPosition(sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 2) - 50));
	startButton.SetText("Start");
	startButton.SetTextPosition(sf::Vector2f(window.getSize().x / 2 - 55, (window.getSize().y / 2) - 70));

	optionsButton.LoadTexture("..\\UIpack\\PNG\\blue_button00.png");
	optionsButton.SetPosition(sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 2) + 20));
	optionsButton.SetText("Options");
	optionsButton.SetTextPosition(sf::Vector2f(window.getSize().x / 2 - 75, (window.getSize().y / 2)));

	exitButton.LoadTexture("..\\UIpack\\PNG\\blue_button00.png");
	exitButton.SetPosition(sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 2) + 90));
	exitButton.SetText("Exit");
	exitButton.SetTextPosition(sf::Vector2f(window.getSize().x / 2 - 40, (window.getSize().y / 2) + 70));
}

bool Panel::LoadTexture(std::string filePath)
{
	if (!texture.loadFromFile(filePath))
	{
		return EXIT_FAILURE;
	}

	sprite.setTexture(texture);
	std::cout << "Element loaded" << std::endl;
	return EXIT_SUCCESS;
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
