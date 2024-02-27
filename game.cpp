#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace sf;

const int maxParticles = 7;

int main() {
    srand(static_cast<unsigned>(time(0)));

    RenderWindow window(VideoMode(500, 500), "My window", Style::Close | Style::Resize);

    RectangleShape player(Vector2f(100.0f, 100.0f));
    player.setPosition(250, 440);
    Texture playerTexture;
    playerTexture.loadFromFile("playerTexture.png");
    player.setTexture(&playerTexture);

    RectangleShape particles[maxParticles];
    Texture particleTexture;
    particleTexture.loadFromFile("particle.png");

    int lives = 3;

    for (int i = 0; i < maxParticles; ++i) {
        particles[i].setSize(Vector2f(20.0f, 20.0f));
        particles[i].setFillColor(Color::Blue);
        particles[i].setTexture(&particleTexture);
        particles[i].setPosition(static_cast<float>(rand() % window.getSize().x), static_cast<float>(rand() % window.getSize().y));
    }

    while (window.isOpen()) {
        Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == ev.Closed) {
                window.close();
            }
            if (ev.type == ev.Resized) {
                cout << " Event width " << ev.size.width << " Event height " << ev.size.height << endl;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
            player.move(-0.1f, 0.0f);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
            player.move(0.0f, -0.1f);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
            player.move(0.1f, 0.0f);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
            player.move(0.f, 0.1f);
        }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            Vector2i mousePosition = Mouse::getPosition(window);
            player.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
        }

        
        for (int i = 0; i < maxParticles; ++i) {
            particles[i].move(0.0f, 0.1f);

            
            if (particles[i].getGlobalBounds().intersects(player.getGlobalBounds())) {
                
                lives--;
                cout << "Lives left: " << lives << endl;
                particles[i].setPosition(static_cast<float>(rand() % window.getSize().x), 0.0f);
            }

            
            if (particles[i].getPosition().y > window.getSize().y) {
                particles[i].setPosition(static_cast<float>(rand() % window.getSize().x), 0.0f);
            }
        }

        window.clear();

        window.draw(player);

        for (int i = 0; i < maxParticles; ++i) {
            window.draw(particles[i]);
        }

        window.display();

        if (lives <= 0) {
            cout << "Game Over!" << endl;
            window.close();
        }
    }

    return 0;
}
