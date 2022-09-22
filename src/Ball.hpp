//
//  Ball.hpp
//  MSD-CS6010-Final-Project
//
//  Created by Avishek Choudhury on 9/21/22.
//

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Ball {
private:
    sf::Sprite ball;
    
public:

    sf::Sprite GetBall();
    void SetPosition(sf::Vector2f position);
    sf::Vector2f GetPosition();
    void Jump();
    const sf::FloatRect getBoundary() const;
    void setTexture(const sf::Texture& texture);
    void setScale(const float& x, const float& y);
    void rotate(const float& rotate);
};
