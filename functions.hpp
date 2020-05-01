#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <SFML/Graphics.hpp>
#include "formula.hpp"

void drawFunction(Formula* formula, float ratio_, float centerX, float centerY, int sizeX, int sizeY, sf::RenderWindow* window) ;
void drawCoordinateSystem(float ratio_, float unit, float centerX, float centerY, int sizeX, int sizeY, sf::RenderWindow* window) ;

#endif // FUNCTIONS_H
