#include "BodyPart.hpp"

BodyPart::BodyPart(sf::Texture& texture, std::string name)
{
	this->name = name; // for debugging purposes
	bodyPart.setTexture(texture);

	for(int i = 0; i < 3000; i++)
	{
		positions.push_back(sf::Vector2f(0.0f, 0.0f));
	}
}

BodyPart::~BodyPart()
{
}

void BodyPart::SetPosition(const sf::Vector2f& position)
{
	bodyPart.setPosition(position);
}

sf::Vector2f BodyPart::GetPosition()
{
	return bodyPart.getPosition();
}

sf::IntRect BodyPart::GetRect()
{
	return bodyPart.getTextureRect();
}

void BodyPart::Render(sf::RenderWindow& window)
{
	window.draw(bodyPart);
}

void BodyPart::Update(const sf::Vector2f prev)
{
	positions.push_back(prev);

	if (positions.size() > 3000)
	{
		positions.pop_front();
	}
}

sf::Vector2f& BodyPart::GetLastPosition()
{
	return positions.front();
}