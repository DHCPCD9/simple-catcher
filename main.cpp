#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <utils.hpp>
#include <thread>
#include "objects/TexturedSprite.hpp"
#include "packets/GetProfile.hpp"
#include <effolkronium/random.hpp>


//71 в лево
//73 в верх
//72 в право
//74 в низ

using Random = effolkronium::random_static;


int main() {


    //Connecting to server
    sf::TcpSocket socket;
    std::cout << "Connecting to server..." << std::endl;

    sf::Socket::Status status = socket.connect("localhost", 45321);

    if (status != sf::Socket::Done) {
        std::cout << "Error: " << status << std::endl;
        return -1;
    }
    std::cout << "Connected to server" << std::endl;

    socket.setBlocking(false);

    //Creating packet
    sf::Packet packet;
    std::string username = "user-" + std::to_string(Random::get(1, 100));
    packet >> username; 
    std::cout << "Sending packet..." << std::endl;
    if (socket.send(packet) != sf::Socket::Done) {
        std::cout << "Error: " << status << std::endl;
        return -1;
    }

    

    
    
    sf::RenderWindow window(sf::VideoMode(800,600, 32), "Noice");
    window.requestFocus();
    window.setMouseCursorVisible(false);

    TexturedSprite cursor("./assets/cursor.png");
    const int totalApples = 10;
    TexturedSprite apples[totalApples];
    TexturedSprite player("./assets/player.png");
    player.sprite.setPosition(window.getSize().x / 2, window.getSize().y - player.texture.getSize().y);

    for (int i = 0; i < totalApples; i++) {
        apples[i].setTexture("./assets/apple.png", sf::IntRect(0, 0, 64, 64));
        float x = Random::get(0, (int) window.getSize().x);
        float y = Random::get(0, (int) window.getSize().y - 300);
        apples[i].sprite.setPosition(x, y);
    }
    


 
    sf::Clock clock;
    sf::Clock objectClock;
    float fps;

    sf::Font font;
    if (!font.loadFromFile("assets/font.ttf"))
    {
        return -1;
    }

    int score = 0;

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(48);
    scoreText.setPosition(window.getSize().x / 2, window.getSize().y / 12);
    scoreText.setString("0");
    scoreText.setColor(sf::Color::White);


    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setPosition(0, 0);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setCharacterSize(12);

    //Starting playing music
    sf::Music music;
    if (!music.openFromFile("./assets/music.ogg"))
    {
        return -1;
    }

    music.play();
    music.setLoop(true);
    music.setVolume(50);
    char buffer[1024];
    size_t received;
    socket.setBlocking(false);


    while (window.isOpen())
    {

        sf::Event event;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));

                player.sprite.setPosition(window.getSize().x / 2, window.getSize().y - player.texture.getSize().y);

                for (int i = 0; i < 15; i++) {
                    int x = apples[i].sprite.getPosition().x;
                    int y = apples[i].sprite.getPosition().y;

                    apples[i].sprite.setPosition(x + (window.getSize().x - x) / 2, y + (window.getSize().y - y) / 2);
                }
            }

            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0) {
                    music.setVolume(music.getVolume() + 5);
                } else {
                    music.setVolume(music.getVolume() - 5);
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                int speed = window.getSize().x / 100;

                if (event.key.shift) {
                    speed = speed*2.5f;
                }

                if (event.key.code == sf::Keyboard::Left) {
                    player.sprite.move(-speed, 0);
                }

                if (event.key.code == sf::Keyboard::Right) {
                    player.sprite.move(speed, 0);
                }

                if (player.sprite.getPosition().x < 0) {
                    player.sprite.setPosition(window.getSize().x, player.sprite.getPosition().y);
                }

                if (player.sprite.getPosition().x > window.getSize().x) {
                    player.sprite.setPosition(0, player.sprite.getPosition().y);
                }
                if (event.key.code == 36) {
                    window.close();
                }
            }
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseMoved){
                cursor.sprite.setPosition(event.mouseMove.x, event.mouseMove.y);
            }
        }

        for (int i = 0; i < totalApples; i++) {
            if (objectClock.getElapsedTime().asSeconds() > 0.1) {
                apples[i].sprite.setPosition(apples[i].sprite.getPosition().x, apples[i].sprite.getPosition().y + 2);
            }
        }

        if (objectClock.getElapsedTime().asSeconds() > 0.1) {
            objectClock.restart();
        }

        for (int i = 0; i < totalApples; i++) {
            if (isColiding(player.sprite.getPosition(), apples[i].sprite.getPosition())) {
                apples[i].sprite.setPosition(Random::get(0, (int) window.getSize().x), Random::get(0, (int) window.getSize().y - 300));
                score++;
            }
    

            if (apples[i].sprite.getPosition().y > window.getSize().y) {
                apples[i].sprite.setPosition(Random::get(0, (int) window.getSize().x), Random::get(0, (int) window.getSize().y - 300));
            }
        }

        scoreText.setString(std::to_string(score));

        
        window.clear();
        window.draw(fpsText);
        window.draw(cursor.sprite);
        window.draw(scoreText);
        for (int i = 0; i < totalApples; i++) {
            window.draw(apples[i].sprite);
        }
        window.draw(player.sprite);
        fpsText.setString(std::to_string(clock.getElapsedTime().asMilliseconds()) + "ms");
        window.display();
        clock.restart();


    }

    return 0;
}