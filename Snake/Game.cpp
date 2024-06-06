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
    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        ProcessEvents();
        Update(deltaTime);
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
