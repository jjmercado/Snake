#include "MyGame.hpp"

MyGame::MyGame() : gameState(IGameState::StartMenu), menuPanel(window, font), play(window, font), gameOverPanel(window, font)
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
                menuPanel.HandleEvents(window, event, *this);
                break;
            }
            case IGameState::Playing:
            {
                play.HandleEvents(window, event, *this);
                break;
            }
            case IGameState::GameIsOver:
            {
                gameOverPanel.HandleEvents(event, window, *this, play.GetCharakter(), play.GetApple());
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
            menuPanel.Render(window);
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
            gameOverPanel.Render(window);
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
