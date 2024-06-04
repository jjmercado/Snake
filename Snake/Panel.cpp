#include "Panel.hpp"

Panel::Panel()
{
}

Panel::Panel(sf::RenderWindow& window)
{
	LoadTexture("..\\UIpack\\PNG\\panel.png");
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
	sprite.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));

	if (!font.loadFromFile("..\\UIpack\\Font\\kenvector_future.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}

	menuText.setFont(font);
	menuText.setCharacterSize(40);
	menuText.setFillColor(sf::Color::White);
	menuText.setString("Snake");
	menuText.setOrigin(menuText.getLocalBounds().width / 2, menuText.getLocalBounds().height / 2);
	menuText.setPosition(sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 2) - 165));

	optionsButton.LoadTexture(sf::IntRect(0, 0, 190, 49));
	optionsButton.SetPosition(sf::Vector2f(window.getSize().x / 2, (window.getSize().y / 2)));
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
	optionsButton.Render(window);
	window.draw(menuText);
}
