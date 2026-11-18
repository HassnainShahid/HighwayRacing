//Highway Racing Semester Project
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <string>

int main()
{

    float playerCarSpeed = 5.f;

    // CREATING GAME WINDOW
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Highway Racing");

    // SETTING GAME FRAME RATE TO 60 FPS
    window.setFramerateLimit(60);

    // -------------------------------------------CREATING ROAD-----------------------------------------
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

    // ---------------- 0------------------CREATING PLAYER CAR -----------------------------------------------

    sf::Texture carTexture;

    if (!carTexture.loadFromFile("assets//playercar.png"))
    {
        return -1;
    }

    sf::Sprite playerCar(carTexture);

    playerCar.setPosition({ 375.f, 400.f });
    playerCar.setScale({ 0.12f, 0.15f });

    //-------------------------CREATING ENEMY CARS---------------------------------------------------------

    //LOADING SEVEN DIFF ENEMYCAR TEXTURES
    sf::Texture enemyTexture[7];


    //CHECK WHETHER EACH NEW TEXTURE LOADS
    for (int i = 0; i < 7; i++)
    {
        std::string fileName = "assets/enemycar" + std::to_string(i + 1) + ".png";

        if (!enemyTexture[i].loadFromFile(fileName))
        {
            return -1;
        }
    }

    //CREATING THREE ENEMY CAR SPRITES USING THE FIRST THREE TEXTURES
    sf::Sprite enemyCar[3] = { sf::Sprite(enemyTexture[0]), sf::Sprite(enemyTexture[1]), sf::Sprite(enemyTexture[2]) };

    //RESIZING THE 3 ENEMY CARS
    enemyCar[0].setScale({ 0.12f, 0.14f });
    enemyCar[1].setScale({ 0.12f, 0.14f });
    enemyCar[2].setScale({ 0.12f, 0.14f });

    //INITIAL POS OF ENEMY CARS
    enemyCar[0].setPosition({ 180.f, -170.f });
    enemyCar[1].setPosition({ 350.f, -400.f });
    enemyCar[2].setPosition({ 520.f, -650.f });

    float enemySpeed = 3.f;

    //VARIABLES USED FOR RANDOM LANE SELECTION
    int lane = 0;
    int randomNumber = 0;

    //INITIALIZING RANDOM NUMBER GENERATOR
    srand(static_cast<unsigned int>(time(0)));



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

        //----------------------------Moving PLAYER car----------------------------------------------

        //MOVING PLAYER CAR LEFT USING LEFT ARROW KEY
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            if (playerCar.getPosition().x > 110.f)
            {
                playerCar.move({ -playerCarSpeed, 0.f });
            }
        }

        //MOVING PLAYER CAR LEFT USING A KEY
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            if (playerCar.getPosition().x > 110.f)
            {
                playerCar.move({ -playerCarSpeed, 0.f });
            }
        }

        //MOVING PLAYER CAR RIGHT USING RIGHT ARROW KEY
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            if (playerCar.getPosition().x < 590.f)
            {
                playerCar.move({ playerCarSpeed, 0.f });
            }
        }

        //MOVING PLAYER CAR RIGHT USING D KEY
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            if (playerCar.getPosition().x < 590.f)
            {
                playerCar.move({ playerCarSpeed, 0.f });
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

        // ---------------- ENEMY MOVEMENT ----------------

        for (int i = 0; i < 3; i++)
        {
            enemyCar[i].move({ 0.f, enemySpeed });

            if (enemyCar[i].getPosition().y > 600.f)
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

                // SELECTING RANDOM ENEMY GRAPHIC
                int randomTexture = rand() % 7;

                enemyCar[i].setTexture(enemyTexture[randomTexture]);

                // RESETTING ENEMY POSITION
                enemyCar[i].setPosition({static_cast<float>(lane), -170.f});
            }
        }

        // DRAWING
        window.clear(sf::Color::Green);

        window.draw(road1);
        window.draw(road2);

        for (int i = 0; i < 3; i++)
        {
            window.draw(enemyCar[i]);
        }

        window.draw(playerCar);


        window.display();
    }

    return 0;
}