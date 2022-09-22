//
//  game.hpp
//  MSD-CS6010-Final-Project
//
//  Created by Avishek Choudhury on 9/20/22.
//

#ifndef game_hpp
#define game_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "Ball.hpp"

void RunGame();
void CreateBall(sf::RenderWindow& window, Ball& ball);
void CreateWalls(sf::RenderWindow& window, float position);
bool IsColliding(Ball& ball);
void ShowGameDetails();
void OpenRestartWindow();
const sf::RectangleShape MakeBrick(float x, float y);

#endif /* game_hpp */
