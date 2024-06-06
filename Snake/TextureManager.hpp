#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class TextureManager
{
public:
    TextureManager();

    static sf::Texture& getTexture(const std::string& textureName);
    static void loadTextures();

private:
    static std::unordered_map<std::string, sf::Texture> textures;

    static void loadTexture(const std::string& name, const std::string& filePath);
};
