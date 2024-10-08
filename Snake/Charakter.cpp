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
}

Charakter::~Charakter()
{
}

// eventuell ein struct definieren f�r die richtungen

void Charakter::Events(sf::Event& event, Apple& apple)
{
	if (event.type == sf::Event::KeyPressed && !hasCollided)
	{
		newDirection = direction;

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

		if (event.key.code == sf::Keyboard::J)
		{
			apple.SetPosition(sf::Vector2f(rand() % (800 / (int)tileSize) * (int)tileSize, rand() % (600 / (int)tileSize) * (int)tileSize));
		}

		if(event.key.code == sf::Keyboard::Space)
		{
			for(int i = 0; i < 100; i++)
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
	}

	if (!hasCollided)
	{
		for (auto itr = std::next(snakeBodyParts.begin()); itr != snakeBodyParts.end(); ++itr)
		{
			itr->RenderBodyParts();
			itr->RenderCurveBodyParts(itr, snakeBodyParts.end());

			if (itr == std::prev(snakeBodyParts.end()))
				itr->ChangeTailTexture();
		}
	}

	ChangeHeadTexture();
}

void Charakter::Update(sf::Time deltaTime, IGameState& gameState, Apple& apple)
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
		for(auto& bodyPart : snakeBodyParts)
		{
			bodyPart.SavePosition();
			bodyPart.SetDirection(direction);
		}

		for (auto itr = snakeBodyParts.begin(); itr != snakeBodyParts.end(); ++itr)
		{
			if (itr == snakeBodyParts.begin())
			{
				itr = std::next(itr, 1);
			}

			lastPosition = std::prev(itr)->GetLastPosition();
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

		// �berpr�ft, ob der Charakter nahe genug an der Zielposition ist
		if (std::abs(newPosition.x - targetPosition.x) < 0.1f && std::abs(newPosition.y - targetPosition.y) < 0.1f)
		{
			// Korrigiert die Position, um kleine Abweichungen zu vermeiden
			snakeBodyParts.front().SetPosition(targetPosition);
			
			isLerping = false; // Stoppt die Interpolation, wenn die Zielposition erreicht ist
		}
	}
	else
	{
		// F�hrt die kontinuierliche Bewegung nur aus, wenn der Charakter nicht interpoliert wird
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
		Collision(col, apple);
	}

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

void Charakter::Collision(const sf::IntRect& bodyPartRect, Apple& apple)
{
	sf::Vector2f rndApplePos = sf::Vector2f(rand() % (800 / (int)tileSize) * (int)tileSize, rand() % (600 / (int)tileSize) * (int)tileSize);

	if(apple.GetRect().intersects(bodyPartRect))
	{
		rndApplePos = sf::Vector2f(rand() % (800 / (int)tileSize) * (int)tileSize, rand() % (600 / (int)tileSize) * (int)tileSize);
		apple.SetPosition(rndApplePos);
		std::cout << "Collision" << std::endl;
	}
	
	if (snakeHeadRect.intersects(apple.GetRect()))
	{
		eat.play();
		apple.SetPosition(rndApplePos);
		AddBodyPart();
	}
}

void Charakter::AddBodyPart()
{
	auto back = std::prev(snakeBodyParts.end(), 1);

	if (direction.x > 0)
	{
		snakeBodyParts.push_back(BodyPart(TextureManager::GetTexture("tailLeft"), back->GetPosition()));
	}
	else if (direction.x < 0)
	{
		snakeBodyParts.push_back(BodyPart(TextureManager::GetTexture("tailRight"), back->GetPosition()));
	}
	else if (direction.y > 0)
	{
		snakeBodyParts.push_back(BodyPart(TextureManager::GetTexture("tailUp"), back->GetPosition()));
	}
	else if (direction.y < 0)
	{
		snakeBodyParts.push_back(BodyPart(TextureManager::GetTexture("tailDown"), back->GetPosition()));
	}
}

void Charakter::Reset(sf::RenderWindow& window, Apple& apple)
{
	sf::Vector2f rndApplePos = sf::Vector2f(rand() % (800 / (int)tileSize) * (int)tileSize, rand() % (600 / (int)tileSize) * (int)tileSize);
	gameOver.stop();
	snakeBodyParts.clear();
	sf::Vector2f startPosition = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - 20);
	snakeBodyParts.push_back(BodyPart(TextureManager::GetTexture("headLeft"), startPosition));
	snakeBodyParts.push_back(BodyPart(TextureManager::GetTexture("bodyHorizontal"), startPosition));
	snakeBodyParts.push_back(BodyPart(TextureManager::GetTexture("tailRight"), startPosition));

	snakeBodyParts.front().SetPosition(startPosition);

	isBodyCollisionActive = false;
	hasCollided = false;

	apple.SetPosition(rndApplePos);

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

	return gridPosition + (direction * tileSize * deltaTime.asSeconds()); // Angenommen, die Grid-Gr��e ist 40
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
