#include "Charakter.hpp"

Charakter::Charakter(sf::RenderWindow& window)
{
	sf::Vector2f startPosition = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - 20);
	snakeBodyParts.push_back(BodyPart(TextureManager::getTexture("headLeft"), "Head", startPosition));
	snakeBodyParts.push_back(BodyPart(TextureManager::getTexture("bodyHorizontal"), "BodyPart0", startPosition));
	snakeBodyParts.push_back(BodyPart(TextureManager::getTexture("tailRight"), "Tail", startPosition));
	window.setKeyRepeatEnabled(false);

	snakeBodyParts.front().SetPosition(startPosition);

	speed = 1.0f;
	direction = sf::Vector2f(-1.0f, 0.0f);

	isLerping = false;
	counter = 0;
}

Charakter::~Charakter()
{
}

// eventuell ein struct definieren für die richtungen

void Charakter::Events(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && !CheckBoundaries())
	{
		sf::Vector2f newDirection = direction;

		if ((event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) && newDirection != sf::Vector2f(-1.0f, 0.0f))
		{
			newDirection = sf::Vector2f(1.0f, 0.0f);
		}
		else if ((event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) && newDirection != sf::Vector2f(1.0f, 0.0f))
		{
			newDirection = sf::Vector2f(-1.0f, 0.0f);
		}
		else if ((event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) && newDirection != sf::Vector2f(0.0f, -1.0f))
		{
			newDirection = sf::Vector2f(0.0f, 1.0f);
		}
		else if ((event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) && newDirection != sf::Vector2f(0.0f, 1.0f))
		{
			newDirection = sf::Vector2f(0.0f, -1.0f);
		}

		if(event.key.code == sf::Keyboard::Space)
		{
			for(int i = 0; i < 300; i++)
				AddBodyPart();
		}

		if (directionChangeClock.getElapsedTime().asSeconds() > 0.095f && newDirection != direction) 
		{
			direction = newDirection;
			isLerping = true;
			directionChangeClock.restart();
		}
	}
}

void Charakter::Render(sf::RenderWindow& window)
{
	for (auto& bodyPart : snakeBodyParts)
	{
		bodyPart.Render(window);
		bodyPart.SetDirection(direction);
	}

	if (!CheckBoundaries())
	{
		for (auto itr = snakeBodyParts.begin(); itr != snakeBodyParts.end(); ++itr)
		{
			if (itr == snakeBodyParts.begin())
			{
				itr = std::next(itr, 1);
			}

			lastDirection = std::prev(itr)->GetLastDirection();
			itr->SetDirection(lastDirection);

			if (lastDirection.x < 0 || lastDirection.x > 0)
			{
				itr->SetTexture(TextureManager::getTexture("bodyHorizontal"));
			}
			else if (lastDirection.y < 0 || lastDirection.y > 0)
			{
				itr->SetTexture(TextureManager::getTexture("bodyVertical"));
			}

			ChangeTailTexture();
		}
	}

	ChangeHeadTexture();
}

void Charakter::Update(sf::Time deltaTime)
{
	if (CheckBoundaries())
	{
		speed = 0.0f;
		for (auto itr = snakeBodyParts.begin(); itr != snakeBodyParts.end(); ++itr)
		{
			if (itr == snakeBodyParts.begin())
				itr = std::next(itr, 1);

			itr->SetPosition(itr->GetPosition());
		}
	}
	else
	{
		for (auto itr = snakeBodyParts.begin(); itr != snakeBodyParts.end(); ++itr)
		{
			if (itr == snakeBodyParts.begin())
				itr = std::next(itr, 1);

			itr->Update(std::prev(itr)->GetPosition());
			lastPosition = itr->GetLastPosition();
			itr->SetPosition(lastPosition);
		}
	}

	if (isLerping)
	{
		float lerpRate = 2.0f;

		// Berechnet die Zielposition auf dem Grid
		targetPosition = CalculateTargetPosition(deltaTime);

		// Interpoliert die Position des Charakters zur Zielposition
		sf::Vector2f currentPosition = snakeBodyParts.front().GetPosition();
		sf::Vector2f newPosition = Lerp(currentPosition, targetPosition, lerpRate * deltaTime.asSeconds());
		snakeBodyParts.front().SetPosition(newPosition);

		// Überprüft, ob der Charakter nahe genug an der Zielposition ist
		if (std::abs(newPosition.x - targetPosition.x) < 0.1f && std::abs(newPosition.y - targetPosition.y) < 0.1f)
		{
			// Korrigiert die Position, um kleine Abweichungen zu vermeiden
			snakeBodyParts.front().SetPosition(targetPosition);
			
			isLerping = false; // Stoppt die Interpolation, wenn die Zielposition erreicht ist
		}
	}
	else
	{
		// Führt die kontinuierliche Bewegung nur aus, wenn der Charakter nicht interpoliert wird
		sf::Vector2f velocity = direction * speed * deltaTime.asSeconds();
		sf::Vector2f newPosition = snakeBodyParts.front().GetPosition() + velocity;
		snakeBodyParts.front().SetPosition(newPosition);
	}

	rect = sf::IntRect(snakeBodyParts.front().GetPosition().x, snakeBodyParts.front().GetPosition().y, snakeBodyParts.front().GetRect().width, snakeBodyParts.front().GetRect().height);
}

void Charakter::ChangeHeadTexture()
{
	if (direction.x > 0)
	{
		snakeBodyParts.front().SetTexture(TextureManager::getTexture("headRight"));
	}
	else if (direction.x < 0)
	{
		snakeBodyParts.front().SetTexture(TextureManager::getTexture("headLeft"));
	}
	else if (direction.y > 0)
	{
		snakeBodyParts.front().SetTexture(TextureManager::getTexture("headDown"));
	}
	else if (direction.y < 0)
	{
		snakeBodyParts.front().SetTexture(TextureManager::getTexture("headUp"));
	}
}

void Charakter::ChangeTailTexture()
{
	if (lastDirection.x > 0)
	{
		snakeBodyParts.back().SetTexture(TextureManager::getTexture("tailLeft"));
	}
	else if (lastDirection.x < 0)
	{
		snakeBodyParts.back().SetTexture(TextureManager::getTexture("tailRight"));
	}
	else if (lastDirection.y > 0)
	{
		snakeBodyParts.back().SetTexture(TextureManager::getTexture("tailUp"));
	}
	else if (lastDirection.y < 0)
	{
		snakeBodyParts.back().SetTexture(TextureManager::getTexture("tailDown"));
	}
}

void Charakter::Collision(const sf::IntRect& rect, Apple& apple)
{
	if (this->rect.intersects(rect))
	{
		apple.SetPosition(sf::Vector2f(rand() % (800 / 40) * 40, rand() % (600 / 40) * 40));
		AddBodyPart();
	}
}

void Charakter::AddBodyPart()
{
	auto head = snakeBodyParts.front();
	auto second = std::next(snakeBodyParts.begin(), 1);

	if (lastDirection.x > 0 || lastDirection.x < 0)
	{
		snakeBodyParts.insert(second, BodyPart(TextureManager::getTexture("bodyHorizontal"), "BodyPart", head.GetPosition()));
	}
	else if(lastDirection.y > 0 || lastDirection.y < 0)
	{
		snakeBodyParts.insert(second, BodyPart(TextureManager::getTexture("bodyVertical"), "BodyPart", head.GetPosition()));
	}
}

sf::Vector2f Charakter::CalculateTargetPosition(sf::Time deltaTime)
{
	sf::Vector2f currentPosition = snakeBodyParts.front().GetPosition();
	sf::Vector2f gridPosition = sf::Vector2f(
		std::round(currentPosition.x / 40.0f) * 40.0f,
		std::round(currentPosition.y / 40.0f) * 40.0f
	);

	return gridPosition + (direction * 40.0f * deltaTime.asSeconds()); // Angenommen, die Grid-Größe ist 40
}

bool Charakter::CheckBoundaries()
{
	if (snakeBodyParts.front().GetPosition().x < 0 || snakeBodyParts.front().GetPosition().x > 800 - 40)
	{
		return true;
	}
	else if (snakeBodyParts.front().GetPosition().y < 0 || snakeBodyParts.front().GetPosition().y > 600 - 40)
	{
		return true;
	}
	else
	{
		return false;
	}
}

sf::Vector2f Charakter::Lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t)
{
	return a + (b - a) * t;
}