#include <iostream>
#include "functions.hpp"
#include "formula.hpp"

void drawCoordinateSystem(float ratio_, float unit, float centerX, float centerY, int sizeX, int sizeY, sf::RenderWindow* window) {
    //graduations
    sf::RectangleShape graduationX(sf::Vector2f(2, 9));
    graduationX.setFillColor(sf::Color::Yellow);

    sf::RectangleShape graduationY(sf::Vector2f(9, 2));
    graduationY.setFillColor(sf::Color::Yellow);

    //absicia axis
    sf::RectangleShape abscissia(sf::Vector2f(sizeX, 2));
    abscissia.setPosition(sf::Vector2f(0, centerY));
    abscissia.setFillColor(sf::Color::Yellow);

    //ordinate axis
    sf::RectangleShape ordinate(sf::Vector2f(2, sizeY));
    ordinate.setPosition(sf::Vector2f(centerX, 0));
    ordinate.setFillColor(sf::Color::Yellow);

    window->clear(sf::Color(0, 0, 0, 255));
    window->draw(abscissia);
    window->draw(ordinate);

    //math variable
    float mathX = -1 * centerX * (1 / ratio_);

    //X graduation
    int i = centerX;
    while (i < sizeX)
    {
        i += ratio_ * unit;

        //std::cout << "i : " << i << "; i - centerX : " << i-centerX << "; ratio_ : " << ratio_ << std::endl;
        graduationX.setPosition(i, centerY-4);
        window->draw(graduationX);
    }
    i = centerX;
    while (i > 0)
    {
        i -= ratio_ * unit;
        graduationX.setPosition(i, centerY-4);
        window->draw(graduationX);
    }

    //Y graduation
    i = centerY;
    while (i < sizeY)
    {
        i += ratio_ * unit;
        graduationY.setPosition(centerX-4, i);
        window->draw(graduationY);
    }
    i = centerY;
    while (i > 0)
    {
        i -= ratio_ * unit;
        graduationY.setPosition(centerX-4, i);
        window->draw(graduationY);
    }
}

void drawFunction(Formula* formula, float ratio_, float centerX, float centerY, int sizeX, int sizeY, sf::RenderWindow* window) {

    //curve
    sf::CircleShape circle(2);
    circle.setFillColor(sf::Color::White);
    circle.setOrigin(sf::Vector2f(0, 0));

    //math variable
    float y = 0;
    float mathX = -1 * centerX * (1 / ratio_);

    //curve
    for (int i = 0; i < sizeX; i++)
    {
        mathX += 1/ratio_;
        y = centerY - ratio_ * (formula->getY(mathX));
        circle.setPosition(sf::Vector2f(i-1, y-1));
        window->draw(circle);
    }
}
