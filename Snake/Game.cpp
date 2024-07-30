#include "Game.hpp"

Game::Game() : window(sf::VideoMode(800, 600), "Snake")
{
    if(!font.loadFromFile("../UIpack/Font/kenvector_future.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}

    window.setKeyRepeatEnabled(false);

    TextureManager::LoadTextures();
    frameCount = 0;
}

Game::~Game()
{
}

void Game::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        timeSinceLastUpdate += deltaTime;

        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            ProcessEvents();
            Update(TimePerFrame);
            Render();
            frameCount++;
            if (fpsClock.getElapsedTime().asSeconds() >= 1.0f)
            {
                std::cout << "FPS: " << frameCount << std::endl;
                frameCount = 0;
                fpsClock.restart();
            }
        }
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
