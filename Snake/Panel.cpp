#include "Panel.hpp"

Panel::Panel()
{
}

Panel::Panel(sf::RenderWindow& window, sf::Font& font)
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

Panel::~Panel()
{
}

void Panel::PlayHoverSound()
{
	if (hover.getStatus() != sf::Sound::Playing && !hasPlayedSound)
	{
		hasPlayedSound = true;
		hover.play();
	}
}
