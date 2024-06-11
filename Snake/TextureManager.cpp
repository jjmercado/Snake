#include "TextureManager.hpp"

std::unordered_map<std::string, sf::Texture> TextureManager::textures;

sf::Texture& TextureManager::getTexture(const std::string& textureName)
{
    auto it = textures.find(textureName);
    if (it == textures.end()) 
    {
        throw std::runtime_error("Texture not found: " + textureName);
    }
    return it->second;
}

void TextureManager::loadTextures() 
{
	loadTexture("panel", "..\\UIpack\\PNG\\panel.png");
    loadTexture("yellowButton", "..\\UIpack\\PNG\\yellow_button00.png");
	loadTexture("blueButton", "..\\UIpack\\PNG\\blue_button00.png");
    loadTexture("blueButton13", "..\\UIpack\\PNG\\blue_button13.png");
    loadTexture("startMenuBackground", "..\\snake_graphics\\snakeBackground.png");
    loadTexture("playingBackground", "..\\snake_graphics\\playingBackground.png");
}

void TextureManager::loadTexture(const std::string& name, const std::string& filePath) 
{
    sf::Texture texture;
    if (!texture.loadFromFile(filePath)) {
        // Fehlerbehandlung, falls das Laden fehlschlägt
        throw std::runtime_error("Failed to load texture: " + filePath);
    }
    textures[name] = std::move(texture);
}