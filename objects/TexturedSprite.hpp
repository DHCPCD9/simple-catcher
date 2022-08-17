#pragma once
#include <SFML/Graphics.hpp>

class TexturedSprite {
    public:
        sf::Sprite sprite;
        sf::Texture texture;
        TexturedSprite(sf::Texture& texture);
        TexturedSprite(std::string texture, sf::IntRect rect);
        TexturedSprite(std::string texture);
        TexturedSprite();
        void setTexture(std::string texture);
        void setTexture(std::string texture, sf::IntRect rect);
        void setTexture(sf::Texture& texture, sf::IntRect rect);
};