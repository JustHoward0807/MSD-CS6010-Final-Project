//
//  Obstacles.hpp
//  MSD-CS6010-Final-Project
//
//  Created by Howard Tung on 9/20/22.
//

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Obstacles {
private:
    sf::Sprite _obstacle;
    
public:
    Obstacles(float y) {
        _obstacle.scale(0.2,y);
    }
    
    const sf::Sprite& getObstacle();
    
    const sf::Vector2f& getPosition();
    
    const sf::Vector2f& getScale();
    
    const void setTexture(const sf::Texture& texture);
    
    const void setPosition(const float& x,const float& y);
    
    const void setScale(const float& x, const float& y);
    const sf::FloatRect getBounds();
    
    const void setOrigin(const float& x,const float& y);
    
    const void rotate(const float& x);
};


