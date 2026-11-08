
#include<SFML/Graphics.hpp>
#include<cstdlib>    //for rand() and srand()
#include<ctime>      //for time()
#include<string>     //for converting score to string

int main()
{

    float playerCarSpeed = 5.f;

    // CREATING GAME WINDOW
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Highway Racing");

    //SETTING GAME FRAME RATE TO 60 FPS
    window.setFramerateLimit(60);

    //-------------CREATING ROAD-------------------------------------------------------------------

    //LOADING ROAD IMAGE
    sf::Texture roadTexture;

    if (!roadTexture.loadFromFile("assets//f1.png"))
    {
        return -1; //EXITT IF IMAGE DOESNT LOAD
    }

    //CREATE 2 ROAD SPRITES SAME TEXTURE
    sf::Sprite road1(roadTexture);
    sf::Sprite road2(roadTexture);


    //RESIZING ROAD SPRITES
    road1.setScale({ 0.5525f, 0.5525f });
    road2.setScale({ 0.5525f, 0.5525f });


    //INITIAL POSITION OF BOTH ROADS
    road1.setPosition({ 0.f, 0.f });
    road2.setPosition({ 0.f, -600.f });


    float roadSpeed = 5.f;


    //--------------------CREATING PLAYER CAR--------------------------------------------------------------

    //LOADING PLAYER CAR IMAGE
    sf::Texture carTexture;


    if (!carTexture.loadFromFile("assets//playercar.png"))
    {
        return -1; // EXIT IF CANT LOAD CAR IMAGE
    }

    //CREATING PLAYERCAR SPRITE
    sf::Sprite playerCar(carTexture);

    //SET INITIAL POSITION AND SIZE OF PLAYER CAR
    playerCar.setPosition({ 375.f, 450.f });
    playerCar.setScale({ 0.12f,0.11f });

    //------------------------------------------SCORE SYSTEM------------------------------------------------

    //LOADING FONT FOR SCORE DISPLAY
    sf::Font font;

    if (!font.openFromFile("fonts/Orbitron-VariableFont_wght.ttf"))
    {
        return -1;  //EXIT IF FONT CANNOT BE LOADED
    }


    //CREATING SCORE TEXT
    sf::Text scoreText(font);

    //SCORE TEST APPEARANCE
    scoreText.setCharacterSize(26);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({ 30.f, 20.f });
    scoreText.setString("SCORE: 0");

    //BACKGROUND BOX FOR SCORE TEXT
    sf::RectangleShape scoreBox({ 230.f, 50.f });

    //SCORE BOX APPEARANCE AND POSITION
    scoreBox.setPosition({ 10.f, 10.f });
    scoreBox.setFillColor(sf::Color(20, 20, 20, 200));
    scoreBox.setOutlineColor(sf::Color::White);
    scoreBox.setOutlineThickness(2.f);

    //-------------------------CREATING ENEMY CARS---------------------------------------------------------

    //LOADING SEVEN DIFF ENEMYCAR TEXTURES
    sf::Texture enemyTexture[7];


    //CHECK WHETHER EACH NEW TEXTURE LOADS
    if (!enemyTexture[0].loadFromFile("assets/enemycar1.png"))
    {
        return -1;
    }

    if (!enemyTexture[1].loadFromFile("assets/enemycar2.png"))
    {
        return -1;
    }

    if (!enemyTexture[2].loadFromFile("assets/enemycar3.png"))
    {
        return -1;
    }

    if (!enemyTexture[3].loadFromFile("assets/enemycar4.png"))
    {
        return -1;
    }

    if (!enemyTexture[4].loadFromFile("assets/enemycar5.png"))
    {
        return -1;
    }

    if (!enemyTexture[5].loadFromFile("assets/enemycar6.png"))
    {
        return -1;
    }

    if (!enemyTexture[6].loadFromFile("assets/enemycar7.png"))
    {
        return -1;
    }


    //CREATING THREE ENEMY CAR SPRITES USING THE FIRST THREE TEXTURES
    sf::Sprite enemyCar[3] = {sf::Sprite(enemyTexture[0]), sf::Sprite(enemyTexture[1]), sf::Sprite(enemyTexture[2])};

    //RESIZING THE 3 ENEMY CARS
    enemyCar[0].setScale({0.12f, 0.11f});
    enemyCar[1].setScale({ 0.12f, 0.11f });
    enemyCar[2].setScale({ 0.12f, 0.11f });

    //INITIAL POS OF ENEMY CARS
    enemyCar[0].setPosition({180.f, -170.f});
    enemyCar[1].setPosition({ 350.f, -400.f });
    enemyCar[2].setPosition({ 520.f, -650.f });

    float enemySpeed = 3.f;


    //VARIABLES USED FOR RANDOM LANE SELECTION
    int lane = 0;
    int randomNumber = 0;


    //INITIALIZING PLAYER SCORE VARIABLE
    int score = 0;


    //TO TRACK WETHER EACH ENEMY CAR HAS ALREADY BEEN SCORED
    bool enemyPassed[3] = { false, false, false };


    //INITIALIZING RANDOM NUMBER GENERATOR
    srand(static_cast<unsigned int>(time(0)));


    //---------------------MAIN GAME LOOP---------------------------------------------------------------
    while (window.isOpen())
    {
        //HANDLING WINDOW EVENTS
        while (const auto event = window.pollEvent())
        {
            //CLOSING GAME WHEN CLOSE BUTTON PRESSED
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

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

        // MOVE BOTH ROAD SPRITES DOWNWARD
        road1.move({ 0.f, roadSpeed });
        road2.move({ 0.f, roadSpeed });

        // RESET ROAD 1 WHEN IT LEAVES THE SCREEN
        if (road1.getPosition().y >= 600.f)
        {
            // PLACING ROAD 1 ABOVE ROAD 2
            road1.setPosition({ 0.f, road2.getPosition().y - 600.f });
        }

        // RESET ROAD 2 WHEN IT LEAVES THE SCREEN
        if (road2.getPosition().y >= 600.f)
        {
            // PLACING ROAD 2 ABOVE ROAD 1
            road2.setPosition({ 0.f, road1.getPosition().y - 600.f });
        }

       
        // ------------------------MOVING ENEMY CARS-------------------------------------------------------


        for (int i = 0; i < 3; i++)
        {
            //MOVING CURRENT ENEMY CAR DOWNWARD
            enemyCar[i].move({ 0.f, enemySpeed });

            //CHECKING IF ENEMY HAS LEFT THE SCREEN AND HAS NOT BEEN SCORED
            if (enemyCar[i].getPosition().y > 600.f && enemyPassed[i] == false)
            {
                //AWARDING 10 POINTS FOR SUCCESSFULLY PASSING
                score = score + 10;

                //MARKING ENEMY AS ALREADY SCORED
                enemyPassed[i] = true;
            }


            //CHECKING IF ENEMY CAR HAS LEFT THE SCREEN
            if (enemyCar[i].getPosition().y > 600.f)
            {
                //GENERATING RANDOM NUMBER BETWEEN 0 AND 2
                randomNumber = rand() % 3;

                //SELECTING A LANE BASED ON RANDOM NUMBER
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

                //SELECT RANDOM VEHICLE GRAPHIC
                int randomTexture = rand() % 7;
                enemyCar[i].setTexture(enemyTexture[randomTexture]);


                //RESETTING ENEMY CAR POSITION TO THE SELECTED LANE
                enemyCar[i].setPosition({static_cast<float>(lane),-170.f});

                
                //RESETING THE SCORING STATUS WHEN AN ENEMY RESPAWNS
                enemyPassed[i] = false;


                // PDATING SCORE TEXT WITH CURRENT SCORE
                scoreText.setString("SCORE: " + std::to_string(score));
            }
        }


        window.clear(sf::Color::Green);
        window.draw(road1);
        window.draw(road2);
 

        for (int i = 0; i < 3; i++)
        {
            window.draw(enemyCar[i]);
        }

        window.draw(scoreBox);
        window.draw(scoreText);
        window.draw(playerCar);
        window.display();

    }

    return 0;
}
