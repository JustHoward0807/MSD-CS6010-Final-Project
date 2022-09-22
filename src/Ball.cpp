//
//  Snake.cpp
//  MSD-CS6010-Final-Project
//
//  Created by Howard Tung on 9/20/22.
//

#include "Ball.hpp"

Ball::Ball(float rad) {
    radius = rad;
    ball = sf::CircleShape(radius);
}

sf::CircleShape Ball::GetBall() {
    return ball;
}

void Ball::SetBallProp() {
    ball.setFillColor(sf::Color(100, 250, 50));
    ball.setOrigin(0, 0);
}

void Ball::SetPosition(sf::Vector2f position) {
    ball.setPosition(position.x, position.y);
}

sf::Vector2f Ball::GetPosition() {
    return ball.getPosition();
}

void Ball::Jump() {
    sf::Vector2f position = ball.getPosition();
    position.y += -0.3f;
    ball.setPosition(position.x, position.y);
}
