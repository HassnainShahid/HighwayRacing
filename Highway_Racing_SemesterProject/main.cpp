
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

int main()
{

    float speed = 5.f;

    // CREATING GAME WINDOW
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Highway Racing");


    window.setFramerateLimit(60);

    //CREATING ROAD
    sf::Texture roadTexture;

    if (!roadTexture.loadFromFile("assets//road.png"))
    {
        return -1;
    }

    sf::Sprite road1(roadTexture);
    sf::Sprite road2(roadTexture);




    road1.setScale({ 0.7f,0.5f });
    road2.setScale({ 0.7f, 0.5f });

    road1.setPosition({ 0.f, 0.f });
    road2.setPosition({ 0.f, -600.f });

    float roadSpeed = 5.f;


    //CREATING PLAYER CAR
    sf::Texture carTexture;

    if (!carTexture.loadFromFile("assets//car1.png"))
    {
        return -1;
    }

    sf::Sprite car(carTexture);
    car.setPosition({ 375.f, 450.f });
    car.setScale({ 2.0f,2.0f });

    // CREATE ENEMY CAR
    sf::Texture enemyTexture;

    if (!enemyTexture.loadFromFile("assets/enemycar.png"))
    {
        return -1;
    }

    sf::Sprite enemycar(enemyTexture);

    enemycar.setScale({ 0.25f, 0.25f });
    enemycar.setPosition({ 350.f, -170.f });

    float enemySpeed = 3.f;
    int lane = 0;
    int randomNumber = 0;

    srand(static_cast<unsigned int>(time(0)));

    //MAIN GAME LOOP
    while (window.isOpen())
    {
        //
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            if (car.getPosition().x > 100.f)
            {
                car.move({ -speed, 0.f });
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            if (car.getPosition().x > 100.f)
            {
                car.move({ -speed, 0.f });
            }
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            if (car.getPosition().x < 600.f)
            {
                car.move({ speed, 0.f });
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            if (car.getPosition().x < 600.f)
            {
                car.move({ speed, 0.f });
            }
        }

        // MOVE BOTH ROADS DOWNWARD
        road1.move({ 0.f, roadSpeed });
        road2.move({ 0.f, roadSpeed });

        // RESET ROAD 1 WHEN IT LEAVES THE SCREEN
        if (road1.getPosition().y >= 600.f)
        {
            road1.setPosition({ 0.f, road2.getPosition().y - 600.f });
        }

        // RESET ROAD 2 WHEN IT LEAVES THE SCREEN
        if (road2.getPosition().y >= 600.f)
        {
            road2.setPosition({ 0.f, road1.getPosition().y - 600.f });
        }

       
        // MOVING ENEMY CAR
        enemycar.move({ 0.f, enemySpeed });

        if (enemycar.getPosition().y > 600.f)
        {
            randomNumber = rand() % 3;

            if (randomNumber == 0)
            {
                lane = 180;
            }
            else if (randomNumber == 1)
            {
                lane = 350;
            }
            else
            {
                lane = 520;
            }

            enemycar.setPosition({ static_cast<float>(lane), -170.f });
        }


        window.clear(sf::Color::Green);
        window.draw(road1);
        window.draw(road2);
        window.draw(enemycar);
        window.draw(car);
        window.display();

    }

    return 0;
}
