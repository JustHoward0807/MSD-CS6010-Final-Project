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
        // clear the window with black color
        window.clear(sf::Color::Black);
        int i = 1200, j = 300;
        while (i <= 1500) {
            CreateWalls(window, i);
            CreateWalls(window, j);
            i += 100;
            j -= 100;
        }
        CreateBall(window, ball);
        window.display();
    }
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
//    sf::RectangleShape line1(sf::Vector2f(window.getSize().x, 10));
//    line1.rotate(0);
//    line1.setPosition(0, 300);
//    line1.setFillColor(sf::Color(100, 100, 100));

//    sf::RectangleShape line2(sf::Vector2f(window.getSize().x, 10));
//    line2.rotate(0);
//    line2.setPosition(0, 1300);
//    line2.setFillColor(sf::Color(100, 100, 100));
    
    int itrCount = window.getSize().x / 200;
    float x = 0;
    for (int i = 0; i < itrCount; i++) {
        window.draw(MakeBrick(x, wallPos));
        //wallPos += 10;
        x += 200;
    }
    //window.draw(line1);
    //window.draw(line2);
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
