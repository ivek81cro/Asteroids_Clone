#pragma once
#include "SFML/Graphics.hpp"
#include <fstream>
#include <string>
#include <unordered_map>

class ImageHolder
{
  public:
    static ImageHolder& instance()
    {
        static ImageHolder instance;
        return instance;
    }

    const sf::Texture& GetTexture(const std::string& name)
    {
        auto t = textureMap.find(name);
        return (t != std::end(textureMap)) ? t->second : sf::Texture();
    }

  private:
    ImageHolder()
    {
        std::fstream texturePaths("texturePath.txt");
        std::string  path;
        std::string  name;
        sf::Texture  texture;
        while (texturePaths >> path >> name)
        {
            texture.loadFromFile(path);
            textureMap.insert(std::make_pair(name, texture));
        }
    }
    ~ImageHolder() = default;
    std::unordered_map<std::string, sf::Texture> textureMap;
};
