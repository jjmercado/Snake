#pragma once
class IGameState
{
    public:
        virtual ~IGameState() = default;

        enum GameState { StartMenu, Playing, GameOver };
        virtual void SetState(GameState newState) = 0;
        // Weitere notwendige virtuelle Methoden
};

