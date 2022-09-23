//
//  Snake.cpp
//  MSD-CS6010-Final-Project
//
//  Created by Howard Tung on 9/20/22.
//

#include "Ball.hpp"
#include <SFML/Audio.hpp>


//Return a Sprite class ball
sf::Sprite Ball::GetBall() {
    return ball;
}

void Ball::SetPosition(sf::Vector2f position) {
    ball.setPosition(position.x, position.y);
}

sf::Vector2f Ball::GetPosition() {
    return ball.getPosition();
}

void Ball::Jump() {
//    sf::SoundBuffer soundEffect;
//        if (!soundEffect.loadFromFile("wing.wav")) {
//            std::cout << "No music file found" << std::endl;
//        }
//    sf::Sound sound;
//    sound.setBuffer(soundEffect);
//    sound.play();

    sf::Vector2f position = ball.getPosition();
    position.y -=30;
    ball.setPosition(position.x, position.y);
}

const sf::FloatRect Ball::getBoundary() const {
    return ball.getGlobalBounds();
}

void Ball::setTexture(const sf::Texture& texture) {
    ball.setTexture(texture);
}
void Ball::setScale(const float& x, const float& y) {
    ball.setScale(x,y);
}

void Ball::rotate(const float& rotate) {
    ball.rotate(rotate);
}
