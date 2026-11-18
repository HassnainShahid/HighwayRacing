//Highway Racing Semester Project
#include <SFML/Graphics.hpp>

int main()
{
    // CREATING GAME WINDOW
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Highway Racing");

    // SETTING GAME FRAME RATE TO 60 FPS
    window.setFramerateLimit(60);

    // CREATING ROAD
    sf::Texture roadTexture;

    if (!roadTexture.loadFromFile("assets//f1.png"))
    {
        return -1;
    }

    // CREATE 2 ROAD SPRITES
    sf::Sprite road1(roadTexture);
    sf::Sprite road2(roadTexture);

    // RESIZING ROAD SPRITES
    road1.setScale({ 0.5525f, 0.5525f });
    road2.setScale({ 0.5525f, 0.5525f });

    // INITIAL POSITION OF BOTH ROADS
    road1.setPosition({ 0.f, 0.f });
    road2.setPosition({ 0.f, -600.f });

    float roadSpeed = 5.f;

    // MAIN GAME LOOP
    while (window.isOpen())
    {
        // HANDLING WINDOW EVENTS
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        // MOVING BOTH ROAD SPRITES DOWNWARD
        road1.move({ 0.f, roadSpeed });
        road2.move({ 0.f, roadSpeed });

        // RESET ROAD 1
        if (road1.getPosition().y >= 600.f)
        {
            road1.setPosition({ 0.f, road2.getPosition().y - 600.f });
        }

        // RESET ROAD 2
        if (road2.getPosition().y >= 600.f)
        {
            road2.setPosition({ 0.f, road1.getPosition().y - 600.f });
        }

        // DRAWING
        window.clear(sf::Color::Green);

        window.draw(road1);
        window.draw(road2);

        window.display();
    }

    return 0;
}