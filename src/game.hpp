//
//  game.hpp
//  MSD-CS6010-Final-Project
//
//  Created by Avishek Choudhury on 9/20/22.
//

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "Ball.hpp"

#include "Obstacles.hpp"
void RunGame();
void CreateBall(sf::RenderWindow& window, Ball& ball);
void CreateWalls(sf::RenderWindow& window, float position);
bool IsColliding(Ball& ball,Obstacles& obstacle,Obstacles& fireObstacle, float screen_height, float screen_width);
void ShowGameDetails();
void OpenRestartWindow();
const sf::RectangleShape MakeBrick(float x, float y);
void createIceObstacles(sf::RenderWindow& window, Obstacles& obstacle);
void createFireObstacles(sf::RenderWindow& window, Obstacles& obstacle);

double rand_range();
