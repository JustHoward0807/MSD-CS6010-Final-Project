//
//  game.cpp
//  MSD-CS6010-Final-Project
//
//  Created by Avishek Choudhury on 9/20/22.
//

#include "game.hpp"
#include "Ball.hpp"
#include "Obstacles.hpp"

void RunGame() {
    //Define screen width and height, so don't need to type out again.
    float screen_width = sf::VideoMode::getDesktopMode().width;
    float screen_height = sf::VideoMode::getDesktopMode().height;
    // create the window
    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Weird Flappy Bird");
    //Set the frame limit
    window.setFramerateLimit(60);
    
    //Initialize ball, ice obstacle and fire obstacle
    Ball ball = Ball();
    Obstacles obstacle(0.2);
    Obstacles fireObstacle(0.2);
    sf::Vector2f ballPos(screen_width/2, screen_height/2);
    
    //Set the ball, iceObstacle, fireobstacle position
    ball.SetPosition(ballPos);
    obstacle.setPosition(sf::VideoMode::getDesktopMode().width, 300);
    fireObstacle.setPosition(sf::VideoMode::getDesktopMode().width+500, screen_height-750);
    fireObstacle.rotate(90);
    
    //Assert ball x,y position is at the middle of the screen
    assert(ball.GetPosition().x == screen_width/2);
    assert(ball.GetPosition().y == screen_height/2);
    
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        if (IsColliding(ball, obstacle, fireObstacle, screen_height, screen_width)) {
            OpenRestartWindow();
            
        }
        
        
        
        //Clear the window with black color
        window.clear(sf::Color::Black);
        
        //Making brick walls
        int i = screen_height-500, j = 200;
        while (i <= 1500) {
            CreateWalls(window, i);
            CreateWalls(window, j);
            i += 100;
            j -= 100;
        }
        
        //Making the moving ball, ice obstacles and fireobstacles
        CreateBall(window, ball);
        createIceObstacles( window, obstacle);
        createFireObstacles(window, fireObstacle);
        //Displaying the window
        window.display();
    }
}

void OpenRestartWindow() {
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
        ShowGameDetails();
    }
}

void ShowGameDetails() {
    //    CreateRestart();
    //    CreateExit();
    //    sf::Texture texture;
    //            if(!texture.loadFromFile("button1.png"))
    //            {
    //                    return 1;
    //            }
    //            sf::Sprite sprite;
    //            sprite.setTexture(texture);
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

void createIceObstacles(sf::RenderWindow& window, Obstacles& obstacle) {
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
        
        //TODO: Create Random double number
        //        float random = rand() % 0.9+0.1;
        obstacle.setPosition(sf::VideoMode::getDesktopMode().width, obstacle.getPosition().y);
        
        //TODO: y should be random number
        obstacle.setScale(0.2,0.4);
        
    }
    
    window.draw(obstacle.getObstacle());
    
}

void createFireObstacles(sf::RenderWindow& window, Obstacles& obstacle) {
    sf::Texture texture;
    float x = obstacle.getPosition().x;
    //Change the speed and moving left
    x -= 40;
    obstacle.setPosition(x,obstacle.getPosition().y);
    
    //Set texture
    if (!texture.loadFromFile("Fire.png")) {
        std::cout << "No pic is loaded" << std::endl;
    }
    obstacle.setTexture(texture);
    
    //if obstacle go outside the screen then back to the right side and change size.
    if (obstacle.getPosition().x < 0) {
        //TODO: Create another random double number for scale
        //TODO: Change the fireball height sometimes go outside the wall
        int randomForFireballHeight = rand() % (sf::VideoMode::getDesktopMode().height-600) + 300;
        obstacle.setPosition(sf::VideoMode::getDesktopMode().width + 500, randomForFireballHeight);
        
        //TODO: y should be random number
        obstacle.setScale(0.2,0.4);
        
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
        ball.rotate(-4.f);
        ball.Jump();
    }
    else {
        ball.rotate(1.f);
        sf::Vector2f newBallPos(ball.GetPosition().x, ball.GetPosition().y + 7);
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
