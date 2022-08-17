#include <SFML/Graphics.hpp>

bool isColiding(sf::Vector2f shape1, sf::Vector2f shape2);

int distanceTo(sf::Vector2f shape1, sf::Vector2f shape2);


bool isColiding2(sf::CircleShape shape1, sf::CircleShape shape2);


bool distanceTo2(sf::CircleShape shape1, sf::CircleShape shape2);

void fillCircle(sf::CircleShape shape, sf::Color color, float time);