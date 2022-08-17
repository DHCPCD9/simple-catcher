#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <utils.hpp>



int distanceTo(sf::Vector2f shape1, sf::Vector2f shape2) {
    float x1 = shape1.x;
    float x2 = shape2.x;

    float y1 = shape1.y;
    float y2 = shape2.y;

    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}


bool isColiding(sf::Vector2f shape1, sf::Vector2f shape2) {
    return distanceTo(shape1, shape2) < 10;
}

bool distanceTo2(sf::CircleShape shape1, sf::CircleShape shape2) {
    float x1 = shape1.getPosition().x + shape1.getRadius();
    float x2 = shape2.getPosition().x + shape2.getRadius();

    float y1 = shape1.getPosition().y + shape1.getRadius();
    float y2 = shape2.getPosition().y + shape2.getRadius();

    return distanceTo(sf::Vector2f(x1, y1), sf::Vector2f(x2, y2));
}

void fillCircle(sf::CircleShape shape, sf::Color color, float time) {
    int r = shape.getFillColor().r - color.r;
    int g = shape.getFillColor().g - color.g;
    int b = shape.getFillColor().b - color.b;

    //Fade color in time
    for (int i = 0; i < time; i++) {
        
        if (r > 0) {
            shape.setFillColor(sf::Color(shape.getFillColor().r + 1, shape.getFillColor().g, shape.getFillColor().b));
            r--;
        }

        if (g > 0) {
            shape.setFillColor(sf::Color(shape.getFillColor().r, shape.getFillColor().g + 1, shape.getFillColor().b));
            g--;
        }

        if (b > 0) {
            shape.setFillColor(sf::Color(shape.getFillColor().r, shape.getFillColor().g, shape.getFillColor().b + 1));
            b--;
        }
      
    }
}