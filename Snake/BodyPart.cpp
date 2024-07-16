#include "BodyPart.hpp"

BodyPart::BodyPart(sf::Texture& texture, std::string name, sf::Vector2f prev)
{
	this->name = name; // for debugging purposes
	bodyPart.setTexture(texture);
	direction = sf::Vector2f(-1.0f, 0.0f);
	dynamicCounter = 1700;

	for(int i = 0; i < 2000; i++)
	{
		positions.push_back(prev);
	}
}

BodyPart::~BodyPart()
{
}

void BodyPart::SetDirection(const sf::Vector2f& direction)
{
	this->direction = direction;
}

sf::Vector2f BodyPart::GetDirection()
{
	return direction;
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

void BodyPart::SetTexture(sf::Texture& texture)
{
	bodyPart.setTexture(texture);
}

void BodyPart::Render(sf::RenderWindow& window)
{
	window.draw(bodyPart);

	directions.push_back(direction);

	if(directions.size() > dynamicCounter)
	{
		directions.pop_front();
	}
}

void BodyPart::Update(const sf::Vector2f prev)
{
	positions.push_back(prev);

	if (positions.size() > 2000)
	{
		positions.pop_front();
	}
}

sf::Vector2f& BodyPart::GetLastPosition()
{
	return positions.front();
}

sf::Vector2f& BodyPart::GetLastDirection()
{
	return directions.front();
}