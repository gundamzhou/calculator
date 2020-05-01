#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "formula.hpp"
#include "textField.hpp"
#include "functions.hpp"
#include <SFML/Window/Mouse.hpp>

int main()
{
    int sizeX = 700, sizeY = 700;
    float centerX = sizeX / 2, centerY = sizeY / 2;
    float ratio_ = 10, unit = 1;//3.1415/2;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(sizeX, sizeY), "computation");
    window->setFramerateLimit(60);
    sf::String buffer;

    //event holder
    sf::Event event;

    //textholder
    textField texte(0, (int)sizeY-(sizeX/8), (int)sizeX/8, sizeY);

    //first print
    Formula *sinusoidal;
    sinusoidal = new Formula();

    drawCoordinateSystem(ratio_, unit, centerX, centerY, sizeX, sizeY, window);
    drawFunction(sinusoidal, ratio_, centerX, centerY, sizeX, sizeY, window);
    texte.reveal(window);

    //coordinate line
        //block
        sf::RectangleShape* field;

        //absicia axis
        sf::RectangleShape xLine(sf::Vector2f(sizeX, 1));
        xLine.setFillColor(sf::Color::Red);

        //ordinate axis
        sf::RectangleShape yLine(sf::Vector2f(1, sizeY));
        yLine.setFillColor(sf::Color::Red);
    sf::Vector2i bufferVector;
    sf::Text* coordinates = new sf::Text();
    while (window->isOpen())
    {
        while (window->pollEvent(event))
        {
            sinusoidal = texte.eventget(event, window, sinusoidal, ratio_, unit, centerX, centerY, sizeX, sizeY);
            drawCoordinateSystem(ratio_, unit, centerX, centerY, sizeX, sizeY, window);
            drawFunction(sinusoidal, ratio_, centerX, centerY, sizeX, sizeY, window);
            texte.reveal(window);

            bufferVector = sf::Mouse::getPosition() - window->getPosition();
            //Event::MouseButtonPressed
            while(sf::Mouse::isButtonPressed(sf::Mouse::Left) && bufferVector.y < texte.getY() )
            {
                bufferVector = sf::Mouse::getPosition() - window->getPosition();

                //line
                yLine.setPosition(sf::Vector2f(bufferVector.x,0));
                xLine.setPosition(sf::Vector2f(0,bufferVector.y));
                drawCoordinateSystem(ratio_, unit, centerX, centerY, sizeX, sizeY, window);
                drawFunction(sinusoidal, ratio_, centerX, centerY, sizeX, sizeY, window);
                window->draw(yLine);
                window->draw(xLine);

                //fonts
                sf::Font font;
                if (!font.loadFromFile("consolas.ttf"))
                {
                    std::cout << "error no consolas" << std::endl;
                }

                //field
                field = new sf::RectangleShape(sf::Vector2f(sizeY, (int)sizeX/8));
                field->setFillColor(sf::Color::White);
                field->setPosition(sf::Vector2f(0, (int)sizeY-(sizeX/8)));
                window->draw(*field);

                //coordinates
                coordinates->setFont(font);
                coordinates->setPosition(sf::Vector2f(0, (int)sizeY-(sizeX/8)));
                coordinates->setFillColor(sf::Color::Black);
                buffer = "x : " + std::to_string((bufferVector.x-centerX)/ratio_) + "; y : " + std::to_string((bufferVector.y-centerY)/ratio_);
                coordinates->setString(buffer);
                window->draw(*coordinates);
                window->display();
            }
            switch(event.type)
            {
                case sf::Event::EventType::Closed :
                    window->close();
                    break;
                case sf::Event::EventType::KeyPressed :
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Key::Escape:
                            window->close();
                            break;
                    case sf::Keyboard::Key::PageUp:
                            ratio_*=2;
                            drawCoordinateSystem(ratio_, unit, centerX, centerY, sizeX, sizeY, window);
                            drawFunction(sinusoidal, ratio_, centerX, centerY, sizeX, sizeY, window);
                            break;
                    case sf::Keyboard::Key::PageDown:
                            ratio_ *= (ratio_ * 0.5 < 1) ? 1:0.5;
                            drawCoordinateSystem(ratio_, unit, centerX, centerY, sizeX, sizeY, window);
                            drawFunction(sinusoidal, ratio_, centerX, centerY, sizeX, sizeY, window);
                            break;
                    case sf::Keyboard::Key::Right:
                            centerX-=10;
                            drawCoordinateSystem(ratio_, unit, centerX, centerY, sizeX, sizeY, window);
                            drawFunction(sinusoidal, ratio_, centerX, centerY, sizeX, sizeY, window);
                            break;
                    case sf::Keyboard::Key::Left:
                            centerX+= 10;
                            drawCoordinateSystem(ratio_, unit, centerX, centerY, sizeX, sizeY, window);
                            drawFunction(sinusoidal, ratio_, centerX, centerY, sizeX, sizeY, window);
                            break;
                    case sf::Keyboard::Key::Down:
                            centerY-= 10;
                            drawCoordinateSystem(ratio_, unit, centerX, centerY, sizeX, sizeY, window);
                            drawFunction(sinusoidal, ratio_, centerX, centerY, sizeX, sizeY, window);
                            break;
                    case sf::Keyboard::Key::Up:
                            centerY+= 10;
                            drawCoordinateSystem(ratio_, unit, centerX, centerY, sizeX, sizeY, window);
                            drawFunction(sinusoidal, ratio_, centerX, centerY, sizeX, sizeY, window);
                            break;
                    default:
                            break;
                    }
                default:
                    break;
            }
        }
    }
    return 0;
}
