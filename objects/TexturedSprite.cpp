#include "TexturedSprite.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

TexturedSprite::TexturedSprite(sf::Texture& texture) : sprite(texture) {
            texture.setSmooth(true);
            this->texture = texture;
            sprite = sf::Sprite(this->texture);
};

TexturedSprite::TexturedSprite(std::string texture, sf::IntRect rect) {
            if (!this->texture.loadFromFile(texture, rect)) {
                std::cout << "Error loading texture: " << texture << std::endl;
                return;
            }

            std::cout << "Loaded texture: " << texture << std::endl;
            this->texture.setSmooth(true);
            sprite = sf::Sprite(this->texture);
};

TexturedSprite::TexturedSprite(std::string texture) {
            if (!this->texture.loadFromFile(texture)) {
                std::cout << "Error loading texture: " << texture << std::endl;
                return;
            }
            this->texture.setSmooth(true);
            sprite = sf::Sprite(this->texture);
};

TexturedSprite::TexturedSprite() {
            sprite = sf::Sprite();
};

void TexturedSprite::setTexture(std::string texture) {
            if (!this->texture.loadFromFile(texture)) {
                std::cout << "Error loading texture: " << texture << std::endl;
                return;
            }
            this->texture.setSmooth(true);
            sprite = sf::Sprite(this->texture);
};

void TexturedSprite::setTexture(sf::Texture& texture, sf::IntRect rect) {
            this->texture = texture;
            this->texture.setSmooth(true);
            sprite = sf::Sprite(this->texture, rect);
};

void TexturedSprite::setTexture(std::string texture, sf::IntRect rect) {
            if (!this->texture.loadFromFile(texture, rect)) {
                std::cout << "Error loading texture: " << texture << std::endl;
                return;
            }
            this->texture.setSmooth(true);
            sprite = sf::Sprite(this->texture, rect);
};