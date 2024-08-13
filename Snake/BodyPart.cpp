#include "BodyPart.hpp"

BodyPart::BodyPart(sf::Texture& texture, sf::Vector2f prev)
{
	collisionRect = sf::IntRect(0, 0, 40, 40);
	bodyPart.setPosition(prev);
	bodyPart.setTexture(texture);
	maxListValue = 8;
	direction = sf::Vector2f(-1, 0);
	positions.push_back(prev);
}

BodyPart::~BodyPart()
{
}

void BodyPart::SetDirection(const sf::Vector2f& dir)
{
	direction = dir;
}

void BodyPart::SetPosition(const sf::Vector2f& position)
{
	bodyPart.setPosition(position);
}

sf::Vector2f BodyPart::GetPosition()
{
	return bodyPart.getPosition();
}

sf::IntRect BodyPart::GetCollisionRect()
{
	return collisionRect;
}

void BodyPart::SetTexture(sf::Texture& texture)
{
	bodyPart.setTexture(texture);
}

void BodyPart::Render(sf::RenderWindow& window)
{
	window.draw(bodyPart);
}

void BodyPart::SavePosition()
{
	positions.push_back(bodyPart.getPosition());

	if (positions.size() > maxListValue)
	{
		positions.pop_front();
	}
}

sf::Vector2f& BodyPart::GetLastPosition()
{
	return positions.front();
}

void BodyPart::RenderBodyParts()
{
	sf::Vector2f direction = CheckDir();

	if (direction.x < 0 || direction.x > 0)
	{
		bodyPart.setTexture(TextureManager::GetTexture("bodyHorizontal"));
	}
	else if (direction.y < 0 || direction.y > 0)
	{
		bodyPart.setTexture(TextureManager::GetTexture("bodyVertical"));
	}
}

void BodyPart::RenderCurveBodyParts(std::list<BodyPart>::iterator itr, std::list<BodyPart>::iterator listEnd)
{
	auto prev = std::prev(itr);
	auto next = std::next(itr);
	sf::Vector2f prevDir = prev->direction;
	sf::Vector2f nextDir;

	if (next != listEnd)
		nextDir = next->direction;
	else
		nextDir = sf::Vector2f(0, 0);

	if (prevDir.x < 0 && nextDir.y < 0) // hoch dann links
	{
		bodyPart.setTexture(TextureManager::GetTexture("bottomLeft"));
		std::cout << "prevDir.x < 0 && nextDir.y < 0" << std::endl;
	}
	else if(prevDir.x > 0 && nextDir.y < 0) // hoch dann rechts
	{
		bodyPart.setTexture(TextureManager::GetTexture("bottomRight"));
	}
	else if(prevDir.x < 0 && nextDir.y > 0) // runter dann links
	{
		bodyPart.setTexture(TextureManager::GetTexture("topLeft"));
	}
	else if(prevDir.x > 0 && nextDir.y > 0) // runter dann rechts
	{
		bodyPart.setTexture(TextureManager::GetTexture("topRight"));
	}
	else if(prevDir.y < 0 && nextDir.x < 0) // links dann hoch
	{
		bodyPart.setTexture(TextureManager::GetTexture("topRight"));
	}
	else if(prevDir.y > 0 && nextDir.x < 0) // links dann runter
	{
		bodyPart.setTexture(TextureManager::GetTexture("bottomRight"));
	}
	else if(prevDir.y < 0 && nextDir.x > 0) // rechts dann hoch
	{
		bodyPart.setTexture(TextureManager::GetTexture("topLeft"));
	}
	else if(prevDir.y > 0 && nextDir.x > 0) // rechts dann runter
	{
		bodyPart.setTexture(TextureManager::GetTexture("bottomLeft"));
	}
}

sf::Vector2f BodyPart::CheckDir()
{
	auto lastItr = positions.end();

	sf::Vector2f currentPosition = bodyPart.getPosition();
	sf::Vector2f previousPosition = *std::prev(lastItr);
	sf::Vector2f direction = currentPosition - previousPosition;

	return direction;
}

void BodyPart::ChangeTailTexture()
{
	sf::Vector2f direction = CheckDir();
	if (direction.x > 0)
	{
		bodyPart.setTexture(TextureManager::GetTexture("tailLeft"));
	}
	else if (direction.x < 0)
	{
		bodyPart.setTexture(TextureManager::GetTexture("tailRight"));
	}
	else if (direction.y > 0)
	{
		bodyPart.setTexture(TextureManager::GetTexture("tailUp"));
	}
	else if (direction.y < 0)
	{
		bodyPart.setTexture(TextureManager::GetTexture("tailDown"));
	}
}