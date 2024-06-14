#include "Game.hpp"

Game::Game() : window(sf::VideoMode(800, 600), "Snake")
{
    if(!font.loadFromFile("../UIpack/Font/kenvector_future.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}

    TextureManager::loadTextures();
}

Game::~Game()
{
}

void Game::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time TimePerFrame = sf::seconds(1.f / 60.f); // 60 Updates pro Sekunde

    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        timeSinceLastUpdate += deltaTime;

        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
        }
            ProcessEvents();
            Update(TimePerFrame); // Update mit fester Zeitrate

        Render();
    }
}

void Game::ProcessEvents()
{
}

void Game::Update(sf::Time deltaTime)
{
}

void Game::Render()
{
}
