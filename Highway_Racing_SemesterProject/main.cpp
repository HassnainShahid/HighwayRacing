#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include <string>

//FUNCTION TO CREATE TEXT
sf::Text makeText(const sf::Font& font, std::string str, int size, sf::Color color, float x, float y, bool centered)
{
    sf::Text text(font);

    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);

    if (centered)
    {
        sf::FloatRect bounds = text.getLocalBounds();

        text.setOrigin({ bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f });
    }

    text.setPosition({ x, y });

    return text;
}

// FUNCTION TO CREATE GREY TRANSPARENT BOX
sf::RectangleShape makeBox(float width, float height, float x, float y)
{
    sf::RectangleShape box({ width, height });

    box.setPosition({ x, y });
    box.setFillColor(sf::Color(100, 100, 100, 155));
    box.setOutlineColor(sf::Color(220, 220, 220, 180));
    box.setOutlineThickness(1.5f);

    return box;
}

// FUNCTION TO CREATE COLLISION HITBOX
sf::FloatRect makeHitbox(const sf::Sprite& sprite, float xInset, float topInset, float bottomInset)
{
    sf::FloatRect hitbox = sprite.getGlobalBounds();

    hitbox.position.x += xInset;
    hitbox.position.y += topInset;

    hitbox.size.x -= xInset * 2.0f;
    hitbox.size.y -= topInset + bottomInset;
    hitbox.size.x *= 0.96;
    hitbox.size.y *= 0.96;

    return hitbox;
}

int main()
{
    float playerCarSpeed = 5.f;

    //CREATING GAME WINDOW
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Highway Racing");

    window.setFramerateLimit(60);

    //GAME STATES
    enum GameState
    {
        MAIN_MENU,
        PLAYING,
        INSTRUCTIONS,
        PAUSED,
        GAME_OVER
    };

    GameState currentState = MAIN_MENU;

    //-------------CREATING ROAD-------------------------------------------------

    sf::Texture roadTexture;

    if (!roadTexture.loadFromFile("assets//f1.png"))
    {
        return -1;
    }

    sf::Sprite road1(roadTexture);
    sf::Sprite road2(roadTexture);

    road1.setScale({ 0.5525f, 0.5525f });
    road2.setScale({ 0.5525f, 0.5525f });

    road1.setPosition({ 0.f, 0.f });
    road2.setPosition({ 0.f, -600.f });

    float roadSpeed = 5.f;

    //--------------------CREATING PLAYER CAR-----------------------------------

    sf::Texture carTexture;

    if (!carTexture.loadFromFile("assets//playercar.png"))
    {
        return -1;
    }

    sf::Sprite playerCar(carTexture);

    playerCar.setPosition({ 375.f, 400.f });
    playerCar.setScale({ 0.12f, 0.15f });

    //--------------------------------SCORE SYSTEM-------------------------------

    sf::Font font;

    if (!font.openFromFile("fonts/Orbitron-VariableFont_wght.ttf"))
    {
        return -1;
    }

    sf::Text scoreText = makeText(font, "SCORE: 0", 26, sf::Color::White, 30.f, 20.f, false);

    sf::RectangleShape scoreBox({ 230.f, 50.f });
    scoreBox.setPosition({ 10.f, 10.f });
    scoreBox.setFillColor(sf::Color(20, 20, 20, 200));
    scoreBox.setOutlineColor(sf::Color::White);
    scoreBox.setOutlineThickness(2.f);

    //-------------------------CREATING ENEMY CARS-------------------------------

    sf::Texture enemyTexture[7];

    if (!enemyTexture[0].loadFromFile("assets/enemycar1.png")) return -1;
    if (!enemyTexture[1].loadFromFile("assets/enemycar2.png")) return -1;
    if (!enemyTexture[2].loadFromFile("assets/enemycar3.png")) return -1;
    if (!enemyTexture[3].loadFromFile("assets/enemycar4.png")) return -1;
    if (!enemyTexture[4].loadFromFile("assets/enemycar5.png")) return -1;
    if (!enemyTexture[5].loadFromFile("assets/enemycar6.png")) return -1;
    if (!enemyTexture[6].loadFromFile("assets/enemycar7.png")) return -1;

    sf::Sprite enemyCar[3] =
    {
        sf::Sprite(enemyTexture[0]),
        sf::Sprite(enemyTexture[1]),
        sf::Sprite(enemyTexture[2])
    };

    for (int i = 0; i < 3; i++)
    {
        enemyCar[i].setScale({ 0.12f, 0.14f });
    }

    enemyCar[0].setPosition({ 180.f, -170.f });
    enemyCar[1].setPosition({ 350.f, -400.f });
    enemyCar[2].setPosition({ 520.f, -650.f });

    float enemySpeed = 3.f;

    int lane = 0;
    int randomNumber = 0;

    int score = 0;

    bool enemyPassed[3] = { false, false, false };

    srand(static_cast<unsigned int>(time(0)));

    //-------------------------CREATING OBSTACLE--------------------------------

    sf::Texture tireTexture;

    if (!tireTexture.loadFromFile("assets/tire.png")) return -1;

    sf::Sprite obstacle(tireTexture);

    obstacle.setScale({ 0.20f, 0.20f });

    obstacle.setOrigin({
        obstacle.getLocalBounds().size.x / 2.f,
        obstacle.getLocalBounds().size.y / 2.f
        });

    bool obstacleActive = false;

    int obstacleLane = 0;
    float obstacleTimer = 0.f;
    float obstacleSpawnDelay = 4.f;
    sf::Clock obstacleClock;


    //-------------------------MAIN MENU BACKGROUND------------------------------

    sf::Texture menuBackgroundTexture;

    if (!menuBackgroundTexture.loadFromFile("assets/mainmenuf1.png"))
    {
        return -1;
    }

    sf::Sprite menuBackground(menuBackgroundTexture);

    menuBackground.setScale({ 800.f / menuBackgroundTexture.getSize().x,600.f / menuBackgroundTexture.getSize().y });

    sf::Font formula1WideFont;
    sf::Font formula1BoldFont;

    if (!formula1WideFont.openFromFile("Fonts/Formula1-Wide-SFML.ttf"))
    {
        return -1;
    }

    if (!formula1BoldFont.openFromFile("Fonts/Formula1-Bold-SFML.ttf"))
    {
        return -1;
    }

    //-------------------------MAIN MENU TEXT------------------------------------

    sf::Text menuTitle = makeText(formula1WideFont, "HIGHWAY RACING", 36, sf::Color::White, 400.f, 115.f, true);

    sf::RectangleShape startBox = makeBox(360.f, 60.f, 220.f, 255.f);
    sf::RectangleShape instructionsBox = makeBox(360.f, 60.f, 220.f, 345.f);
    sf::RectangleShape exitBox = makeBox(360.f, 60.f, 220.f, 435.f);

    sf::Text startText = makeText(formula1BoldFont, "S  -  START", 28, sf::Color::White, 400.f, 285.f, true);

    sf::Text instructionsMenuText = makeText(formula1BoldFont, "I  -  INSTRUCTIONS", 24, sf::Color::White, 400.f, 375.f, true);

    sf::Text exitText = makeText(formula1BoldFont, "ESC  -  EXIT", 24, sf::Color::White, 400.f, 465.f, true);

    //-------------------------INSTRUCTIONS SCREEN------------------------------------------

    sf::Text instructionsTitle = makeText(font, "INSTRUCTIONS", 45, sf::Color::White, 190.f, 105.f, false);

    instructionsTitle.setOutlineColor(sf::Color::White);
    instructionsTitle.setOutlineThickness(1.f);

    sf::Text instructionsDetails = makeText(font, "LEFT / A  -  MOVE LEFT\nRIGHT / D  -  MOVE RIGHT\n\nPASS ENEMY CARS TO EARN POINTS\nAVOID CARS AND ROAD OBSTACLES\n\nESC  -  EXIT GAME\nB  -  BACK TO MAIN MENU", 22, sf::Color::White, 125.f, 220.f, false);

    //-------------------------GAME OVER SCREEN----------------------

    sf::RectangleShape darkOverlay({ 800.f, 600.f });
    darkOverlay.setPosition({ 0.f, 0.f });
    darkOverlay.setFillColor(sf::Color(0, 0, 0, 145));

    sf::Text gameOverTitle = makeText(font, "GAME OVER", 58, sf::Color::Red, 195.f, 155.f, false);

    sf::Text finalScoreText = makeText(font, "", 30, sf::Color::Yellow, 255.f, 255.f, false);

    sf::Text gameOverInstructions = makeText(font, "R  -  RESTART\n\nM  -  MAIN MENU\n\nESC  -  EXIT", 28, sf::Color::White, 400.f, 405.f, true);

    //-------------------------PAUSE SCREEN-----------------------------------

    sf::Text pauseTitle = makeText(font, "GAME PAUSED", 55, sf::Color::White, 400.f, 230.f, true);

    sf::Text pauseInstructions = makeText(font, "R  -  RESUME", 28, sf::Color::White, 400.f, 365.f, true);

    //-------------------------SOUNDS--------------------------------------

    sf::SoundBuffer clickBuffer;
    sf::SoundBuffer crashBuffer;
    sf::SoundBuffer gameOverBuffer;

    if (!clickBuffer.loadFromFile("sounds/click.wav")) return -1;
    if (!crashBuffer.loadFromFile("sounds/crash.wav")) return -1;
    if (!gameOverBuffer.loadFromFile("sounds/gameover.wav")) return -1;

    sf::Sound clickSound(clickBuffer);
    sf::Sound crashSound(crashBuffer);
    sf::Sound gameOverSound(gameOverBuffer);

    sf::Music backgroundMusic;

    if (!backgroundMusic.openFromFile("sounds/background.wav"))
    {
        return -1;
    }

    backgroundMusic.setLooping(true);
    backgroundMusic.setVolume(40.f);

    //-------------------------RESET GAME FUNCTION----------------------------------------------------------------------/

    auto resetGame = [&]()
        {
            // RESETTING SCORE AND SPEED
            score = 0;
            scoreText.setString("SCORE: 0");

            enemySpeed = 3.f;
            roadSpeed = 5.f;

            // RESETTING ROAD AND PLAYER POSITIONS
            road1.setPosition({ 0.f, 0.f });
            road2.setPosition({ 0.f, -600.f });

            playerCar.setPosition({ 375.f, 400.f });

            // RESETTING ENEMY CARS
            float enemyX[3] = { 180.f, 350.f, 520.f };
            float enemyY[3] = { -170.f, -400.f, -650.f };

            for (int i = 0; i < 3; i++)
            {
                enemyCar[i].setTexture(enemyTexture[i]);
                enemyCar[i].setPosition({ enemyX[i], enemyY[i] });
                enemyPassed[i] = false;
            }

            // RESETTING OBSTACLE
            obstacleActive = false;
            obstacleTimer = 0.f;
            obstacle.setTexture(tireTexture, true);
            obstacle.setScale({ 0.20f, 0.20f });

            obstacle.setOrigin({ obstacle.getLocalBounds().size.x / 2.f, obstacle.getLocalBounds().size.y / 2.f });
        };

    //---------------------MAIN GAME LOOP----------------

    while (window.isOpen())
    {
        sf::Time frameTime = obstacleClock.restart();

        // HANDLING WINDOW AND KEYBOARD EVENTS
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>())
            {
                // MAIN MENU KEYS
                if (currentState == MAIN_MENU)
                {
                    if (keyEvent->code == sf::Keyboard::Key::S)
                    {
                        clickSound.play();
                        backgroundMusic.play();
                        currentState = PLAYING;
                    }
                    else if (keyEvent->code == sf::Keyboard::Key::I)
                    {
                        clickSound.play();
                        currentState = INSTRUCTIONS;
                    }
                    else if (keyEvent->code == sf::Keyboard::Key::Escape)
                    {
                        clickSound.play();
                        sf::sleep(sf::milliseconds(150));
                        window.close();
                    }
                }

                // INSTRUCTIONS SCREEN KEYS
                else if (currentState == INSTRUCTIONS)
                {
                    if (keyEvent->code == sf::Keyboard::Key::B)
                    {
                        clickSound.play();
                        currentState = MAIN_MENU;
                    }
                    else if (keyEvent->code == sf::Keyboard::Key::Escape)
                    {
                        clickSound.play();
                        sf::sleep(sf::milliseconds(150));
                        window.close();
                    }
                }

                // GAMEPLAY KEYS
                else if (currentState == PLAYING)
                {
                    if (keyEvent->code == sf::Keyboard::Key::P)
                    {
                        clickSound.play();
                        backgroundMusic.pause();
                        currentState = PAUSED;
                    }
                    else if (keyEvent->code == sf::Keyboard::Key::Escape)
                    {
                        clickSound.play();
                        sf::sleep(sf::milliseconds(150));
                        window.close();
                    }
                }

                // PAUSE SCREEN KEYS
                else if (currentState == PAUSED)
                {
                    if (keyEvent->code == sf::Keyboard::Key::R)
                    {
                        clickSound.play();
                        backgroundMusic.play();
                        currentState = PLAYING;
                    }
                }

                // GAME OVER SCREEN KEYS
                else if (currentState == GAME_OVER)
                {
                    // RESTARTING THE GAME
                    if (keyEvent->code == sf::Keyboard::Key::R)
                    {
                        resetGame();

                        clickSound.play();
                        backgroundMusic.play();

                        currentState = PLAYING;
                    }

                    // RETURNING TO MAIN MENU
                    else if (keyEvent->code == sf::Keyboard::Key::M)
                    {
                        resetGame();

                        clickSound.play();

                        currentState = MAIN_MENU;
                    }

                    else if (keyEvent->code == sf::Keyboard::Key::Escape)
                    {
                        clickSound.play();
                        sf::sleep(sf::milliseconds(150));
                        window.close();
                    }
                }
            }
        }

        // ONLY UPDATE THE GAME WHILE PLAYING
        if (currentState == PLAYING)
        {
            // MOVING PLAYER CAR LEFT
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {
                if (playerCar.getPosition().x > 120.f)
                {
                    playerCar.move({ -playerCarSpeed, 0.f });
                }
            }

            // MOVING PLAYER CAR RIGHT
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            {
                if (playerCar.getPosition().x < 580.f)
                {
                    playerCar.move({ playerCarSpeed, 0.f });
                }
            }

            road1.move({ 0.f, roadSpeed });
            road2.move({ 0.f, roadSpeed });

            if (road1.getPosition().y >= 600.f)
            {
                road1.setPosition({ 0.f, road2.getPosition().y - 600.f });
            }

            if (road2.getPosition().y >= 600.f)
            {
                road2.setPosition({ 0.f, road1.getPosition().y - 600.f });
            }

            // HITBOX OF PLAYER CAR
            sf::FloatRect playerHitbox = makeHitbox(playerCar, 8.f, 20.f, 20.f);

            //------------------------MOVING ENEMY CARS---------------------------

            for (int i = 0; i < 3; i++)
            {
                enemyCar[i].move({ 0.f, enemySpeed });

                sf::FloatRect enemyHitbox = makeHitbox(enemyCar[i], 8.f, 20.f, 15.f);

                if (playerHitbox.findIntersection(enemyHitbox))
                {
                    currentState = GAME_OVER;

                    finalScoreText.setString("FINAL SCORE: " + std::to_string(score));

                    backgroundMusic.stop();
                    crashSound.play();

                    sf::sleep(sf::milliseconds(700));

                    gameOverSound.play();

                    break;
                }

                if (enemyCar[i].getPosition().y > 600.f && enemyPassed[i] == false)
                {
                    score = score + 10;
                    enemyPassed[i] = true;

                    scoreText.setString("SCORE: " + std::to_string(score));
                }

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

                    int randomTexture = rand() % 7;
                    enemyCar[i].setTexture(enemyTexture[randomTexture]);

                    enemyCar[i].setPosition({ static_cast<float>(lane), -170.f });

                    enemyPassed[i] = false;
                }
            }

            //------------------------MOVING OBSTACLE-----------------------------

            if (obstacleActive == false)
            {
                obstacleTimer += frameTime.asSeconds();
            }

            if (currentState == PLAYING)
            {
                if (obstacleActive == false && obstacleTimer >= obstacleSpawnDelay)
                {
                    obstacle.setTexture(tireTexture, true);

                    obstacle.setOrigin({ obstacle.getLocalBounds().size.x / 2.f,obstacle.getLocalBounds().size.y / 2.f });

                    obstacle.setScale({ 0.20f, 0.20f });

                    obstacleLane = rand() % 2;

                    if (obstacleLane == 0)
                    {
                        obstacle.setPosition({ 300.f, -50.f });
                    }
                    else
                    {
                        obstacle.setPosition({ 500.f, -50.f });
                    }

                    obstacleActive = true;
                }

                if (obstacleActive == true)
                {
                    obstacle.move({ 0.f, roadSpeed });

                    sf::FloatRect obstacleHitbox = makeHitbox(obstacle, 12.f, 12.f, 12.f);

                    if (playerHitbox.findIntersection(obstacleHitbox))
                    {
                        currentState = GAME_OVER;

                        finalScoreText.setString("FINAL SCORE: " + std::to_string(score));

                        backgroundMusic.stop();
                        crashSound.play();

                        sf::sleep(sf::milliseconds(700));

                        gameOverSound.play();
                    }
                    else if (obstacle.getPosition().y > 650.f)
                    {
                        obstacleActive = false;
                        obstacleTimer = 0.f;
                    }
                }
            }

            enemySpeed = 3.f + (score / 200) * 0.5f;
            roadSpeed = 5.f + (score / 200) * 0.5f;
        }

        //-------------------------DRAWING SCREENS-------------------------------

        window.clear(sf::Color::Black);

        // MAIN MENU
        if (currentState == MAIN_MENU)
        {
            window.draw(menuBackground);

            window.draw(startBox);
            window.draw(instructionsBox);
            window.draw(exitBox);

            window.draw(menuTitle);
            window.draw(startText);
            window.draw(instructionsMenuText);
            window.draw(exitText);
        }

        // INSTRUCTIONS SCREEN
        else if (currentState == INSTRUCTIONS)
        {
            window.draw(menuBackground);
            window.draw(darkOverlay);
            window.draw(instructionsTitle);
            window.draw(instructionsDetails);
        }

        // GAMEPLAY, PAUSE AND GAME OVER BACKGROUND
        else if (currentState == PLAYING ||
            currentState == PAUSED ||
            currentState == GAME_OVER)
        {
            window.draw(road1);
            window.draw(road2);

            for (int i = 0; i < 3; i++)
            {
                window.draw(enemyCar[i]);
            }

            if (obstacleActive == true)
            {
                window.draw(obstacle);
            }

            window.draw(scoreBox);
            window.draw(scoreText);
            window.draw(playerCar);

            // PAUSE SCREEN
            if (currentState == PAUSED)
            {
                window.draw(darkOverlay);
                window.draw(pauseTitle);
                window.draw(pauseInstructions);
            }

            // GAME OVER SCREEN
            else if (currentState == GAME_OVER)
            {
                window.draw(darkOverlay);
                window.draw(gameOverTitle);
                window.draw(finalScoreText);
                window.draw(gameOverInstructions);
            }
        }

        window.display();
    }

    return 0;
}
