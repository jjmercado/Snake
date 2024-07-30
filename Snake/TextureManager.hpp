#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class TextureManager
{
    public:
        TextureManager();
        static sf::Texture& GetTexture(const std::string& textureName);
        static void LoadTextures();

    private:
        static std::unordered_map<std::string, sf::Texture> textures;
        static void LoadTexture(const std::string& name, const std::string& filePath);
};
