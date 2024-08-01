#include "TextureManager.hpp"

std::unordered_map<std::string, sf::Texture> TextureManager::textures;

sf::Texture& TextureManager::GetTexture(const std::string& textureName)
{
    auto it = textures.find(textureName);
    if (it == textures.end()) 
    {
        throw std::runtime_error("Texture not found: " + textureName);
    }
    return it->second;
}

void TextureManager::LoadTextures() 
{
	LoadTexture("panel", "..\\UIpack\\PNG\\panel.png");
    LoadTexture("yellowButton", "..\\UIpack\\PNG\\yellow_button00.png");
	LoadTexture("blueButton", "..\\UIpack\\PNG\\blue_button00.png");
    LoadTexture("blueButton13", "..\\UIpack\\PNG\\blue_button13.png");
    LoadTexture("startMenuBackground", "..\\snake_graphics\\snakeBackground.png");
    LoadTexture("playingBackground", "..\\snake_graphics\\playingBackground.png");
    LoadTexture("headLeft", "..\\snake_graphics\\Graphics\\head_left.png");
    LoadTexture("headRight", "..\\snake_graphics\\Graphics\\head_right.png");
    LoadTexture("headUp", "..\\snake_graphics\\Graphics\\head_up.png");
    LoadTexture("headDown", "..\\snake_graphics\\Graphics\\head_down.png");
    LoadTexture("tailRight", "..\\snake_graphics\\Graphics\\tail_right.png");
    LoadTexture("tailLeft", "..\\snake_graphics\\Graphics\\tail_left.png");
    LoadTexture("tailUp", "..\\snake_graphics\\Graphics\\tail_up.png");
    LoadTexture("tailDown", "..\\snake_graphics\\Graphics\\tail_down.png");
    LoadTexture("bodyHorizontal", "..\\snake_graphics\\Graphics\\body_horizontal.png");
    LoadTexture("bodyVertical", "..\\snake_graphics\\Graphics\\body_vertical.png");
    LoadTexture("apple", "..\\snake_graphics\\Graphics\\apple.png");
    LoadTexture("bottomLeft", "..\\snake_graphics\\Graphics\\body_bottomleft.png");
    LoadTexture("bottomRight", "..\\snake_graphics\\Graphics\\body_bottomright.png");
    LoadTexture("topLeft", "..\\snake_graphics\\Graphics\\body_topleft.png");
    LoadTexture("topRight", "..\\snake_graphics\\Graphics\\body_topright.png");
}

void TextureManager::LoadTexture(const std::string& name, const std::string& filePath) 
{
    sf::Texture texture;
    if (!texture.loadFromFile(filePath)) {
        // Fehlerbehandlung, falls das Laden fehlschlägt
        throw std::runtime_error("Failed to load texture: " + filePath);
    }
    textures[name] = std::move(texture);
}