//
//  Obstacles.cpp
//  MSD-CS6010-Final-Project
//
//  Created by Howard Tung on 9/20/22.
//

#include "Obstacles.hpp"

const sf::Sprite& Obstacles::getObstacle() {
    return _obstacle;
}

const sf::Vector2f& Obstacles::getPosition() {
    return _obstacle.getPosition();
}

const sf::Vector2f& Obstacles::getScale() {
    return _obstacle.getScale();
}

const void Obstacles::setPosition(const float& x,const float& y) {
    return _obstacle.setPosition(x,y);
}

const void Obstacles::setTexture(const sf::Texture& texture) {
    _obstacle.setTexture(texture);
}

const void Obstacles::setScale(const float& x, const float& y) {
    _obstacle.setScale(x,y);
}
const sf::FloatRect Obstacles::getBounds() {
    return _obstacle.getGlobalBounds();
}

const void Obstacles::setOrigin(const float& x,const float& y) {
    _obstacle.setOrigin(x, y);
}
const void Obstacles::rotate(const float& x) {
    _obstacle.rotate(x);
    
}

