#include "Charakter.hpp"

Charakter::Charakter(sf::RenderWindow& window)
{
	AddBodyPart(TextureManager::getTexture("bodyHorizontal"));
	AddBodyPart(TextureManager::getTexture("bodyHorizontal"));
	AddBodyPart(TextureManager::getTexture("bodyHorizontal"));

	tail.setTexture(TextureManager::getTexture("tailRight"));

	headPosition = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - 20);
	tailPosition = headPosition + sf::Vector2f(40, 0);

	head.setPosition(headPosition);
	tail.setPosition(tailPosition);

	speed = 1.0f;
	direction = sf::Vector2f(-1.0f, 0.0f);

	isLerping = false;
	counter = 0;
}

Charakter::~Charakter()
{
}

void Charakter::Events(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		sf::Vector2f newDirection = direction;

		if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
		{
			newDirection = sf::Vector2f(1.0f, 0.0f);
		}
		else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
		{
			newDirection = sf::Vector2f(-1.0f, 0.0f);
		}
		else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
		{
			newDirection = sf::Vector2f(0.0f, 1.0f);
		}
		else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
		{
			newDirection = sf::Vector2f(0.0f, -1.0f);
		}

		if (directionChangeClock.getElapsedTime().asSeconds() > 0.085f) 
		{
			direction = newDirection;
			isLerping = true;
			directionChangeClock.restart();
		}
	}
}

void Charakter::Render(sf::RenderWindow& window)
{
	window.draw(head);
	window.draw(tail);

	if (!bodyParts.empty())
	{
		for (auto& part : bodyParts)
		{
			window.draw(part);
		}
	}
}

void Charakter::Update(sf::Time deltaTime)
{
	//sf::Vector2f offset = direction * 40.0f;

	headPositions.push_back(head.getPosition());

	TrackBodyPartsPosition();
	TrackLastBodyPartsPosition();
	SetBodyPartPosition();

	if (isLerping)
	{
		float lerpRate = 2.0f;

		// Berechnet die Zielposition auf dem Grid
		targetPosition = CalculateTargetPosition(deltaTime);

		// Interpoliert die Position des Charakters zur Zielposition
		sf::Vector2f currentPosition = head.getPosition();
		sf::Vector2f newPosition = Lerp(currentPosition, targetPosition, lerpRate * deltaTime.asSeconds());
		head.setPosition(newPosition);

		// Setzt die neue Position

		// Überprüft, ob der Charakter nahe genug an der Zielposition ist
		if (std::abs(newPosition.x - targetPosition.x) < 0.1f && std::abs(newPosition.y - targetPosition.y) < 0.1f)
		{
			// Korrigiert die Position, um kleine Abweichungen zu vermeiden
			head.setPosition(targetPosition);
			
			isLerping = false; // Stoppt die Interpolation, wenn die Zielposition erreicht ist
		}
	}
	else
	{
		// Führt die kontinuierliche Bewegung nur aus, wenn der Charakter nicht interpoliert wird
		sf::Vector2f newPosition = head.getPosition() + (direction * speed * deltaTime.asSeconds());
		head.setPosition(newPosition);
	}

	if (bodyPartsPositions.size() > 3000)
	{
		bodyPartsPositions.pop_front();
		bodyPartsPositions.pop_front();
		bodyPartsPositions.pop_front();

		lastBodyPartsPositions.pop_front();
		lastBodyPartsPositions.pop_front();
		lastBodyPartsPositions.pop_front();
	}

	if (headPositions.size() > 3000)
	{
		headPositions.pop_front();
	}

	rect = sf::IntRect(head.getPosition().x, head.getPosition().y, head.getGlobalBounds().width, head.getGlobalBounds().height);
	MoveHead();

}

void Charakter::MoveHead()
{
	if (direction.x > 0)
	{
		head.setTexture(TextureManager::getTexture("headRight"));
	}
	else if (direction.x < 0)
	{
		head.setTexture(TextureManager::getTexture("headLeft"));
	}
	else if (direction.y > 0)
	{
		head.setTexture(TextureManager::getTexture("headDown"));
	}
	else if (direction.y < 0)
	{
		head.setTexture(TextureManager::getTexture("headUp"));
	}
}

void Charakter::MoveTail() // refactor that shit xD
{
	if (direction.x > 0)
	{
		tail.setTexture(TextureManager::getTexture("tailLeft"));
	}
	else if (direction.x < 0)
	{
		tail.setTexture(TextureManager::getTexture("tailRight"));
	}
	else if (direction.y > 0)
	{
		tail.setTexture(TextureManager::getTexture("tailUp"));
	}
	else if (direction.y < 0)
	{
		tail.setTexture(TextureManager::getTexture("tailDown"));
	}
}

void Charakter::MoveBodyParts()
{
	for (auto &part : bodyParts)
	{
		if (direction.x > 0)
		{
			part.setTexture(TextureManager::getTexture("bodyHorizontal"));
		}
		else if (direction.x < 0)
		{
			part.setTexture(TextureManager::getTexture("bodyHorizontal"));
		}
		else if (direction.y > 0)
		{
			part.setTexture(TextureManager::getTexture("bodyVertical"));
		}
		else if (direction.y < 0)
		{
			part.setTexture(TextureManager::getTexture("bodyVertical"));
		}
	}
}

void Charakter::Collision(const sf::IntRect& rect, Apple& apple)
{
	if (this->rect.intersects(rect))
	{
		apple.SetPosition(sf::Vector2f(rand() % (800 / 40) * 40, rand() % (600 / 40) * 40));
	}
}

void Charakter::AddBodyPart(sf::Texture& texture)
{
	sf::Sprite sprite;
	sprite.setTexture(texture);
	bodyParts.push_back(sprite);
}

sf::Vector2f Charakter::CalculateTargetPosition(sf::Time deltaTime)
{
	sf::Vector2f currentPosition = head.getPosition();
	sf::Vector2f gridPosition = sf::Vector2f(
		std::round(currentPosition.x / 40.0f) * 40.0f,
		std::round(currentPosition.y / 40.0f) * 40.0f
	);

	return gridPosition + (direction * 40.0f * deltaTime.asSeconds()); // Angenommen, die Grid-Größe ist 40
}

sf::Vector2f Charakter::Lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t)
{
	return a + (b - a) * t;
}

void Charakter::TrackBodyPartsPosition()
{
	int counter = 0;
	for (auto& part : bodyParts)
	{
		bodyPartsPositions.push_back(part.getPosition());
		std::cout << "BodyPartsTracking " << counter << " PosX: " << part.getPosition().x << " Part PosY: " << part.getPosition().y << std::endl;
		counter++;
	}

	std::cout << bodyPartsPositions.size() << std::endl;
}

void Charakter::TrackLastBodyPartsPosition()
{
	for(auto& part : bodyParts)
	{
		lastBodyPartsPositions.push_back(bodyPartsPositions.front());
		std::cout << "Last Part PosX: " << bodyPartsPositions.front().x << " Last Part PosY: " << bodyPartsPositions.front().y << std::endl;
		std::cout << "Last Size: " << lastBodyPartsPositions.size() << std::endl;
	}
}

void Charakter::SetBodyPartPosition()
{
	int counter = 0;
	auto itr = std::next(bodyParts.begin(), counter);
	auto itr2 = std::next(lastBodyPartsPositions.begin(), counter);

	bodyPartsPositions.push_back(headPositions.front());

	for (auto& i = itr; i != bodyParts.end(); i++)
	{
		i->setPosition(sf::Vector2f(itr2->x, itr2->y));
		counter++;
	}
}