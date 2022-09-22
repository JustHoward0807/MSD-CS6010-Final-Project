//
//  Ball.hpp
//  MSD-CS6010-Final-Project
//
//  Created by Avishek Choudhury on 9/21/22.
//

#ifndef Ball_hpp
#define Ball_hpp

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Ball {
private:
    float radius;
    sf::CircleShape ball;
    
public:
    Ball(float rad);
    sf::CircleShape GetBall();
    void SetBallProp();
    void SetPosition(sf::Vector2f position);
    sf::Vector2f GetPosition();
    void Jump();
};

#endif /* Ball_hpp */
