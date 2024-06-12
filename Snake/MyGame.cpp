#include "MyGame.hpp"

MyGame::MyGame() : gameState(IGameState::StartMenu), menu(window, font), play(window, font)
{  
}

MyGame::~MyGame()
{
}

void MyGame::ProcessEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        switch (gameState)
        {
            case IGameState::StartMenu:
            {
                menu.handleEvents(window, event, *this);
                break;
            }
            case IGameState::Playing:
            {
                play.handleEvents(window, event, *this);
                break;
            }
            case IGameState::GameOver:
            {

                break;
            }
            default:
                std::cerr << "Invalid game state in Events" << std::endl;
                break;
        }
    }
}

void MyGame::Update(sf::Time deltaTime)
{
    switch (gameState)
    {
        case IGameState::StartMenu:
        {
            break;
        }
        case IGameState::Playing:
        {
            play.handleUpdate(deltaTime);
            break;
        }
        case IGameState::GameOver:
        {

            break;
        }
        default:
            std::cerr << "Invalid game state in Update" << std::endl;
            break;
    }
}

void MyGame::Render()
{
    window.clear();

    switch (gameState)
    {
        case IGameState::StartMenu:
        {
            menu.handleDrawings(window);
            break;
        }
        case IGameState::Playing:
        {
            play.handleDrawings(window);
            break;
        }
        case IGameState::GameOver:
        {
            break;
        }
        default:
            std::cerr << "Invalid game state in Render" << std::endl;
            break;
    }

    window.display();
}

void MyGame::handleGameOver(sf::Event& event)
{
}

void MyGame::SetState(GameState state)
{
	gameState = state;
}
