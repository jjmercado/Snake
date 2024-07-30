#include "MyGame.hpp"

MyGame::MyGame() : gameState(IGameState::StartMenu), menu(window, font), play(window, font), gameOver(window, font)
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
                menu.HandleEvents(window, event, *this);
                break;
            }
            case IGameState::Playing:
            {
                play.HandleEvents(window, event, *this);
                break;
            }
            case IGameState::GameIsOver:
            {
                gameOver.HandleEvents(event, window, *this, play.GetCharakter(), play.GetApple());
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
            play.HandleUpdate(deltaTime, *this);
            break;
        }
        case IGameState::GameIsOver:
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
            menu.HandleDrawings(window);
            break;
        }
        case IGameState::Playing:
        {
            play.HandleDrawings(window);
            break;
        }
        case IGameState::GameIsOver:
        {
            play.HandleDrawings(window);
            gameOver.HandleDrawings(window);
            break;
        }
        default:
            std::cerr << "Invalid game state in Render" << std::endl;
            break;
    }

    window.display();
}

void MyGame::SetState(GameState state)
{
	gameState = state;
}
