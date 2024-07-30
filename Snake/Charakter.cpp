#include "Charakter.hpp"

Charakter::Charakter()
{
}

Charakter::Charakter(sf::RenderWindow& window)
{
	if(!moveBuffer.loadFromFile("move.wav"))
	{
		std::cout << "Error loading sound" << std::endl;
	}
	else
	{
		move.setBuffer(moveBuffer);
	}

	if(!gameOverBuffer.loadFromFile("game-over.mp3"))
	{
		std::cout << "Error loading sound" << std::endl;
	}
	else
	{
		gameOver.setBuffer(gameOverBuffer);
	}

	if(!eatBuffer.loadFromFile("eat.mp3"))
	{
		std::cout << "Error loading sound" << std::endl;
	}
	else
	{
		eat.setBuffer(eatBuffer);
	}

	srand(time(NULL));
	isBodyCollisionActive = false;
	hasCollided = false;
	sf::Vector2f startPosition = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - 20);
	direction = Direction::Left;
	snakeBodyParts.push_back(BodyPart(TextureManager::GetTexture("headLeft"), startPosition));
	snakeBodyParts.push_back(BodyPart(TextureManager::GetTexture("bodyHorizontal"), startPosition));
	snakeBodyParts.push_back(BodyPart(TextureManager::GetTexture("tailRight"), startPosition));

	snakeBodyParts.front().SetPosition(startPosition);

	speed = 250.0f;

	isLerping = false;
	tileSize = 40.0f;
	adjustApplePosition = sf::Vector2f(20, 20);
}

Charakter::~Charakter()
{
}

// eventuell ein struct definieren für die richtungen

void Charakter::Events(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && !hasCollided)
	{
		sf::Vector2f newDirection = direction;

		if ((event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) && newDirection != Direction::Left)
		{
			newDirection = Direction::Right;
			move.play();
		}
		else if ((event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) && newDirection != Direction::Right)
		{
			newDirection = Direction::Left;
			move.play();
		}
		else if ((event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) && newDirection != Direction::Up)
		{
			newDirection = Direction::Down;
			move.play();
		}
		else if ((event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) && newDirection != Direction::Down)
		{
			newDirection = Direction::Up;
			move.play();
		}

		if(event.key.code == sf::Keyboard::Space)
		{
			for(int i = 0; i < 10; i++)
				AddBodyPart();
		}

		if (directionChangeClock.getElapsedTime().asSeconds() > 0.10f && newDirection != direction) 
		{
			direction = newDirection;
			isLerping = true;
			directionChangeClock.restart();
		}
		isBodyCollisionActive = true; // collision nach dem ersten input aktivieren
	}
}

void Charakter::Render(sf::RenderWindow& window)
{
	for (auto& bodyPart : snakeBodyParts)
	{
		bodyPart.Render(window);
		bodyPart.SetDirection(direction);
	}

	if (!hasCollided)
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
				itr->SetTexture(TextureManager::GetTexture("bodyHorizontal"));
			}
			else if (lastDirection.y < 0 || lastDirection.y > 0)
			{
				itr->SetTexture(TextureManager::GetTexture("bodyVertical"));
			}

			ChangeTailTexture();
		}
	}

	ChangeHeadTexture();
}

void Charakter::Update(sf::Time deltaTime, IGameState& gameState)
{
	if (hasCollided)
	{
		speed = 0.0f;
		gameState.SetState(IGameState::GameIsOver);
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
			{
				itr = std::next(itr, 1);
			}

			itr->Update(std::prev(itr)->GetPosition());
			lastPosition = itr->GetLastPosition();
			itr->SetPosition(lastPosition);
		}
	}

	if (isLerping)
	{
		float lerpRate = 60.0f;

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

	for (auto itr = snakeBodyParts.begin(); itr != snakeBodyParts.end(); ++itr)
	{
		if (itr == snakeBodyParts.begin())
			itr = std::next(itr, 1);

		sf::IntRect col = sf::IntRect(itr->GetPosition().x, itr->GetPosition().y, itr->GetCollisionRect().width, itr->GetCollisionRect().height);

		BodyPartCollision(col, gameState);
	}

	rndApplePos = sf::Vector2f(rand() % (800 / (int)tileSize) * (int)tileSize, rand() % (600 / (int)tileSize) * (int)tileSize);
	SetHeadCollisionRect();
	CheckBoundaries();
}

void Charakter::ChangeHeadTexture()
{
	if (direction.x > 0)
	{
		snakeBodyParts.front().SetTexture(TextureManager::GetTexture("headRight"));
	}
	else if (direction.x < 0)
	{
		snakeBodyParts.front().SetTexture(TextureManager::GetTexture("headLeft"));
	}
	else if (direction.y > 0)
	{
		snakeBodyParts.front().SetTexture(TextureManager::GetTexture("headDown"));
	}
	else if (direction.y < 0)
	{
		snakeBodyParts.front().SetTexture(TextureManager::GetTexture("headUp"));
	}
}

void Charakter::ChangeTailTexture()
{
	if (lastDirection.x > 0)
	{
		snakeBodyParts.back().SetTexture(TextureManager::GetTexture("tailLeft"));
	}
	else if (lastDirection.x < 0)
	{
		snakeBodyParts.back().SetTexture(TextureManager::GetTexture("tailRight"));
	}
	else if (lastDirection.y > 0)
	{
		snakeBodyParts.back().SetTexture(TextureManager::GetTexture("tailUp"));
	}
	else if (lastDirection.y < 0)
	{
		snakeBodyParts.back().SetTexture(TextureManager::GetTexture("tailDown"));
	}
}

void Charakter::Collision(const sf::IntRect& rect, Apple& apple)
{
	if (snakeHeadRect.intersects(rect))
	{
		eat.play();

		for(auto position : snakeBodyParts)
		{
			if(position.GetPosition() == rndApplePos)
			{
				apple.SetPosition(rndApplePos + adjustApplePosition);
			}
		}
		apple.SetPosition(rndApplePos + adjustApplePosition);
		AddBodyPart();
	}
}

void Charakter::AddBodyPart()
{
	auto back = snakeBodyParts.back();

	if (lastDirection.x > 0 || lastDirection.x < 0)
	{
		snakeBodyParts.push_back(BodyPart(TextureManager::GetTexture("bodyHorizontal"), back.GetPosition()));
	}
	else if (lastDirection.y > 0 || lastDirection.y < 0)
	{
		snakeBodyParts.push_back(BodyPart(TextureManager::GetTexture("bodyVertical"), back.GetPosition()));
	}
}

void Charakter::Reset(sf::RenderWindow& window, Apple& apple)
{
	gameOver.stop();
	snakeBodyParts.clear();
	sf::Vector2f startPosition = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - 20);
	snakeBodyParts.push_back(BodyPart(TextureManager::GetTexture("headLeft"), startPosition));
	snakeBodyParts.push_back(BodyPart(TextureManager::GetTexture("bodyHorizontal"), startPosition));
	snakeBodyParts.push_back(BodyPart(TextureManager::GetTexture("tailRight"), startPosition));

	snakeBodyParts.front().SetPosition(startPosition);

	isBodyCollisionActive = false;
	hasCollided = false;

	apple.SetPosition(rndApplePos + adjustApplePosition);

	speed = 250.0f;
	direction = Direction::Left;

	isLerping = false;
}

sf::Vector2f Charakter::CalculateTargetPosition(sf::Time deltaTime)
{
	sf::Vector2f currentPosition = snakeBodyParts.front().GetPosition();
	sf::Vector2f gridPosition = sf::Vector2f(
		std::round(currentPosition.x / tileSize) * tileSize,
		std::round(currentPosition.y / tileSize) * tileSize
	);

	return gridPosition + (direction * tileSize * deltaTime.asSeconds()); // Angenommen, die Grid-Größe ist 40
}

void Charakter::BodyPartCollision(const sf::IntRect& bodyPartRect, IGameState& gameState)
{
	if (snakeHeadRect.intersects(bodyPartRect) && isBodyCollisionActive)
	{
		gameState.SetState(IGameState::GameIsOver);
		StartGameOverMusic();
	}
}

void Charakter::CheckBoundaries()
{
	if (snakeBodyParts.front().GetPosition().x < 0 || snakeBodyParts.front().GetPosition().x > 800 - tileSize)
	{
		StartGameOverMusic();
	
	}
	else if (snakeBodyParts.front().GetPosition().y < 0 || snakeBodyParts.front().GetPosition().y > 600 - tileSize)
	{
		StartGameOverMusic();
	}
}

sf::Vector2f Charakter::Lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t)
{
	return a + (b - a) * t;
}

void Charakter::StartGameOverMusic()
{
	gameOver.play();
	hasCollided = true;
}

void Charakter::SetHeadCollisionRect()
{
	if (direction.x > 0)
	{
		snakeHeadRect = sf::IntRect(snakeBodyParts.front().GetPosition().x + 45, snakeBodyParts.front().GetPosition().y + 20, 5, 5);
	}
	else if (direction.x < 0)
	{
		snakeHeadRect = sf::IntRect(snakeBodyParts.front().GetPosition().x - 5, snakeBodyParts.front().GetPosition().y + 20, 5, 5);
	}
	else if (direction.y > 0)
	{
		snakeHeadRect = sf::IntRect(snakeBodyParts.front().GetPosition().x + 20, snakeBodyParts.front().GetPosition().y + 45, 5, 5);
	}
	else if (direction.y < 0)
	{
		snakeHeadRect = sf::IntRect(snakeBodyParts.front().GetPosition().x + 20, snakeBodyParts.front().GetPosition().y - 5, 5, 5);
	}
}
