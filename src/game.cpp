//
//  game.cpp
//  MSD-CS6010-Final-Project
//
//  Created by Avishek Choudhury on 9/20/22.
//

#include "game.hpp"
#include "Ball.hpp"

void RunGame() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(2000, 2000), "My window");
    
    Ball ball = Ball(50);
    ball.SetBallProp();
    sf::Vector2f ballPos(500, 500);
    ball.SetPosition(ballPos);
    
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
        
        if (IsColliding(ball)) {
            OpenRestartWindow();
        }
        
        //Clear the window with black color
        window.clear(sf::Color::Black);
        
        //Making brick walls
        int i = 1200, j = 300;
        while (i <= 1500) {
            CreateWalls(window, i);
            CreateWalls(window, j);
            i += 100;
            j -= 100;
        }
        
        //Making the moving ball
        CreateBall(window, ball);
        
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

bool IsColliding(Ball& ball) {
    if (ball.GetPosition().y > 1100 || ball.GetPosition().y < 400) {
          //If touch the boundary then stop.
        return true;
    }
    return false;
}

void CreateBall(sf::RenderWindow& window, Ball& ball) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        ball.Jump();
    }
    else {
        sf::Vector2f newBallPos(ball.GetPosition().x, ball.GetPosition().y + 0.1f);
        ball.SetPosition(newBallPos);
    }
    window.draw(ball.GetBall());
}

void CreateWalls(sf::RenderWindow& window, float wallPos) {
    int itrCount = window.getSize().x / 200;
    float x = 0;
    for (int i = 0; i < itrCount; i++) {
        window.draw(MakeBrick(x, wallPos));
        x += 200;
    }
}

const sf::RectangleShape MakeBrick(float x, float y) {
    sf::RectangleShape brick(sf::Vector2f(200, 100));
    brick.rotate(0);
    brick.setPosition(x, y);
    brick.setFillColor(sf::Color(203, 65, 84));
    brick.setOutlineColor(sf::Color(100, 100, 100));
    brick.setOutlineThickness(10);
    return brick;
}
