//
//  game.cpp
//  MSD-CS6010-Final-Project
//
//  Created by Avishek Choudhury on 9/20/22.
//

#include "game.hpp"
#include "Ball.hpp"
#include "Obstacles.hpp"
#include <SFML/Audio.hpp>
#include "TextBox.cpp"
#include <string>

void RunGame() {
    sf::SoundBuffer soundEffect;
        if (!soundEffect.loadFromFile("music.wav")) {
            std::cout << "No music file found" << std::endl;
        }
    sf::Sound sound;
    sound.setBuffer(soundEffect);
    sound.play();

    //Define screen width and height, so don't need to type out again.
    float screen_width = sf::VideoMode::getDesktopMode().width;
    float screen_height = sf::VideoMode::getDesktopMode().height;
    // create the window
    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Weird Flappy Bird");
    //Set the frame limit
    window.setFramerateLimit(60);
    
    
    //Initialize ball, ice obstacle, fire obstacle and life
    Ball ball = Ball();
    int life = 5;
    bool firstRound = true;
    sf::Vector2f ballPos(screen_width/2, screen_height/2);
    Obstacles obstacle(0.2);
    Obstacles fireObstacle(0.2);
    
    //Set the ball, iceObstacle, fireobstacle position
    ball.SetPosition(ballPos);
    obstacle.setPosition(sf::VideoMode::getDesktopMode().width, screen_height - 1500);
    fireObstacle.setPosition(sf::VideoMode::getDesktopMode().width+500, screen_height-750);
    fireObstacle.rotate(90);
    

    
    // run the program as long as the window is open
    while (window.isOpen())
    {
        if (firstRound) {
            OpeningScreen();
            
            firstRound = false;
        }
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        

        if (IsColliding(ball, obstacle, fireObstacle, screen_height, screen_width)) {
//            sound.stop();
            OpenRestartWindow(ball);
            
        }
        
        
        

        //Clear the window with black color
        window.clear(sf::Color::Black);
        
        if (IsColliding(ball, obstacle, fireObstacle, screen_height, screen_width)) {
            --life;
            if (life < 1) {
                OpenRestartWindow(ball);
                life = 5;
            }
            window.clear(sf::Color::Black);
            ball.SetPosition(ballPos);
            obstacle.setPosition(sf::VideoMode::getDesktopMode().width, screen_height - 1500);
            fireObstacle.setPosition(sf::VideoMode::getDesktopMode().width+500, screen_height-750);
            continue;
        }
        
        //Making brick walls
        int i = screen_height-500, j = screen_height - 1600;
        while (i <= 1500) {
            CreateWalls(window, i);
            CreateWalls(window, j);
            i += 100;
            j -= 100;
        }
        
        DisplayLife(window, life);
        
        //Making the moving ball, ice obstacles and fireobstacles
        //displayLife(window);
        CreateBall(window, ball);
        createIceObstacles( window, obstacle, ball);
        createFireObstacles(window, fireObstacle);
        //Displaying the window
        window.display();
    }
}

void DisplayLife(sf::RenderWindow& window, int star) {
    for (int i = 0; i < star; i++) {
        sf::Texture texture;
        if(!(texture.loadFromFile("Life.png")))
        {
            return;
        }
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setScale(0.2f, 0.2f);
        sprite.setOrigin(sf::Vector2f(50, 50));
        float onePartX = window.getSize().x / 100;
        float onePartY = window.getSize().y / 100;
        sprite.setPosition(onePartX * 3 * i, onePartY * 3);
        window.draw(sprite);
    }
}

void OpeningScreen() {
    sf::RenderWindow startWindow(sf::VideoMode(1000, 1000), "Restart window");
    
    while (startWindow.isOpen()) {
        
        sf::Event event;
        while (startWindow.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                startWindow.close();
        }
        
        startWindow.clear(sf::Color::Black);
        
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            return;
        }
        sf::Text text;
        text.setFont(font);
        std::string displayText = "Hello World!\nWelcome to the U Bird Game!";
        text.setString(displayText);
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::Red);
        text.setStyle(sf::Text::Bold);
        text.setOrigin(200, 200);
        float onePartX = startWindow.getSize().x / 100;
        float onePartY = startWindow.getSize().y / 100;
        text.setPosition(onePartX * 40, onePartY * 40);
        startWindow.draw(text);
        //NameFunction(startWindow);
        CreateStart(startWindow);
        CreateExit(startWindow);
        
        startWindow.display();
    }
}

void CreateStart(sf::RenderWindow& window) {
    
    sf::Texture texture;
    if(!(texture.loadFromFile("Play.png")))
    {
        return;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(0.6f, 0.6f);
    sprite.setOrigin(sf::Vector2f(50, 50));
    float onePartX = window.getSize().x / 100;
    float onePartY = window.getSize().y / 100;
    sprite.setPosition(onePartX * 30, onePartY * 60);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (sf::Mouse::getPosition(window).x > onePartX * 20 && sf::Mouse::getPosition(window).x < onePartX * 40 && sf::Mouse::getPosition(window).y > onePartY * 50 && sf::Mouse::getPosition(window).y < onePartY * 70)) {
        window.close();
    }
    window.draw(sprite);
}

void NameFunction(sf::RenderWindow& window) {
    TextBox textBox(15, sf::Color::White, true);
    textBox.draw(window);
}

void OpenRestartWindow(Ball& ball) {
    sf::RenderWindow restartWindow(sf::VideoMode(1000, 1000), "Restart window");
    
    while (restartWindow.isOpen()) {
        sf::Event event;
        while (restartWindow.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                restartWindow.close();
        }
        
        restartWindow.clear(sf::Color::Black);
        ShowGameDetails(restartWindow, ball);
        restartWindow.display();
    }
}

void ShowGameDetails(sf::RenderWindow& window, Ball& ball) {
    
    CreateScoreBoard(window, ball);
    CreateRestart(window);
    CreateExit(window);
}

void CreateScoreBoard(sf::RenderWindow& window, Ball& ball) {
    std::string playerName = "Player";
    int points = ball.getPoint();
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return;
    }
    sf::Text text;
    text.setFont(font);
    std::string displayText = "Congratulation " + playerName + "! \nYou have scored: " + std::to_string(points);
    text.setString(displayText);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);
    text.setOrigin(200, 200);
    float onePartX = window.getSize().x / 100;
    float onePartY = window.getSize().y / 100;
    text.setPosition(onePartX * 50, onePartY * 40);
    window.draw(text);
}

void CreateExit(sf::RenderWindow& window) {
    sf::Texture texture;
    if(!(texture.loadFromFile("Exit.png")))
    {
        return;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(0.5f, 0.5f);
    sprite.setOrigin(sf::Vector2f(50, 50));
    float onePartX = window.getSize().x / 100;
    float onePartY = window.getSize().y / 100;
    sprite.setPosition(onePartX * 60, onePartY * 60);
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (sf::Mouse::getPosition(window).x > onePartX * 50 && sf::Mouse::getPosition(window).x < onePartX * 70 && sf::Mouse::getPosition(window).y > onePartY * 50 && sf::Mouse::getPosition(window).y < onePartY * 70)) {
        exit(0);
    }
    window.draw(sprite);
}

void CreateRestart(sf::RenderWindow& window) {
    sf::Texture texture;
    if(!(texture.loadFromFile("Restart.png")))
    {
        return;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(0.2f, 0.2f);
    sprite.setOrigin(sf::Vector2f(50, 50));
    float onePartX = window.getSize().x / 100;
    float onePartY = window.getSize().y / 100;
    sprite.setPosition(onePartX * 30, onePartY * 60);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (sf::Mouse::getPosition(window).x > onePartX * 20 && sf::Mouse::getPosition(window).x < onePartX * 40 && sf::Mouse::getPosition(window).y > onePartY * 50 && sf::Mouse::getPosition(window).y < onePartY * 70)) {
        window.close();
        
    }
    
    window.draw(sprite);
}

bool IsColliding(Ball& ball,Obstacles& obstacle,Obstacles& fireObstacle, float screen_height, float screen_width) {
    //If the position of ball got outside the certain range or intersects with the fire/ice intersects, the game stops
    //Change the fix detect size to boundary intersect.
    if (ball.GetPosition().y > screen_height - 600 || ball.GetPosition().y < 300 || obstacle.getBounds().intersects(ball.getBoundary()) ||
        ball.getBoundary().intersects(fireObstacle.getBounds())) {
        return true;
    }
    return false;
}

void createIceObstacles(sf::RenderWindow& window, Obstacles& obstacle, Ball& ball) {
    sf::Texture texture;
    float x = obstacle.getPosition().x;
    //keep moving to the left
    x -= 30;
    
    //Set texture
    obstacle.setPosition(x,obstacle.getPosition().y);
    if (!texture.loadFromFile("Icecles.png")) {
        std::cout << "No pic is loaded" << std::endl;
    }
    obstacle.setTexture(texture);
    
    //if obstacle go outside the screen then back to the right side and change size.
    if (obstacle.getPosition().x < 0) {
        
        double random = rand_range();
        obstacle.setPosition(sf::VideoMode::getDesktopMode().width, obstacle.getPosition().y);
        
        obstacle.setScale(0.2, 0.5);
        
    } else if (obstacle.getPosition().x == sf::VideoMode::getDesktopMode().width/2) {
        ball.increasePoint();
    }
    
    window.draw(obstacle.getObstacle());
}

void createFireObstacles(sf::RenderWindow& window, Obstacles& obstacle) {
    sf::Texture texture;
    float x = obstacle.getPosition().x;
    //Change the speed and moving left
    int random = rand() % 55 + 40;
    x -= random;
    obstacle.setPosition(x,obstacle.getPosition().y);
    
    //Set texture
    if (!texture.loadFromFile("Fire.png")) {
        std::cout << "No pic is loaded" << std::endl;
    }
    obstacle.setTexture(texture);
    
    //if obstacle go outside the screen then back to the right side and change size.
    if (obstacle.getPosition().x < 0) {
        //TODO: Change the fireball height sometimes go outside the wall
        int randomForFireballHeight = rand() % (sf::VideoMode::getDesktopMode().height-800) + 300;
        double random = rand_range();
        obstacle.setPosition(sf::VideoMode::getDesktopMode().width + 500, randomForFireballHeight);
        
        obstacle.setScale(0.2,random);
        
    }
    
    window.draw(obstacle.getObstacle());
}

void CreateBall(sf::RenderWindow& window, Ball& ball) {
    sf::Texture texture;
    if (!texture.loadFromFile("logo.png")) {
        std::cout << "No pic is loaded" << std::endl;
    }
    
    ball.setTexture(texture);
    ball.setScale(0.1, 0.1);

    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        ball.rotate(-3.f);
        ball.Jump();
        
            
    }
    else {
        ball.rotate(1.f);
        sf::Vector2f newBallPos(ball.GetPosition().x, ball.GetPosition().y + 10);
        ball.SetPosition(newBallPos);
    }
    window.draw(ball.GetBall());
}

void CreateWalls(sf::RenderWindow& window, float wallPos) {
    //TODO ADD comments
    int itrCount = window.getSize().x / 190;
    float x = 0;
    for (int i = 0; i < itrCount; i++) {
        window.draw(MakeBrick(x, wallPos));
        x += 200;
    }
}

const sf::RectangleShape MakeBrick(float x, float y) {
    //TODO ADD comments
    sf::RectangleShape brick(sf::Vector2f(200, 100));
    brick.rotate(0);
    brick.setPosition(x, y);
    brick.setFillColor(sf::Color(203, 65, 84));
    brick.setOutlineColor(sf::Color(100, 100, 100));
    brick.setOutlineThickness(10);
    return brick;
}

double rand_range() {
    //Giving random double value
    int random = rand() % 4 + 0;
    double scale[5] = {0.1,0.2,0.3,0.4,0.5};

    return scale[random];
}
