#pragma once
class IGameState
{
    public:
        virtual ~IGameState() = default;

        enum GameState { StartMenu, Playing, GameIsOver };
        virtual void SetState(GameState newState) = 0;
        // Weitere notwendige virtuelle Methoden
};

