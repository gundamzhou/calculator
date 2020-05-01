#include <iostream>
#include <stdlib.h>
#include "textField.hpp"
#include "formula.hpp"
#include "functions.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Mouse.hpp>

textField::textField()
{
    x = 0;
    y = 0;
    width = 200;
    length = 100;
    field = new sf::RectangleShape(sf::Vector2f(length, width));
    field->setFillColor(sf::Color::White);
    entered = "";
    show = false;
}

textField::textField(int n_x, int n_y, int n_sizeX, int n_sizeY)
{
    text = new sf::Text();
    x = n_x;
    y = n_y;
    width = n_sizeX;
    length = n_sizeY;
    field = new sf::RectangleShape(sf::Vector2f(length, width));
    field->setFillColor(sf::Color::White);
    entered = "";
    show = false;
}

void textField::reveal(sf::RenderWindow* window){
        field->setPosition(sf::Vector2f(x, y));
        sf::Font font;
        if (!font.loadFromFile("consolas.ttf"))
        {
            std::cout << "error no consolas" << std::endl;
        }
        text->setFont(font);
        text->setPosition(sf::Vector2f(x, y));
        text->setFillColor(sf::Color::Black);
        text->setString(" Enter formula here");
        window->draw(*field);
        window->draw(*text);
    //window's update
    window->display();
}

Formula* textField::eventget(sf::Event event, sf::RenderWindow* window, Formula*formula,float ratio_, float unit, float centerX, float centerY, int sizeX, int sizeY){
    show = false;
    bool ok = true;
    sf::Vector2i buffer = sf::Mouse::getPosition() - window->getPosition();
    //Event::MouseButtonPressed
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && buffer.y >= y ){
        drawCoordinateSystem(ratio_, unit, centerX, centerY, sizeX, sizeY, window);
        drawFunction(formula, ratio_, centerX, centerY, sizeX, sizeY, window);
        window->draw(*field);
        //window's update
        window->display();
        while(ok)
        {
            while (window->pollEvent(event))
            {
                    if(event.type == sf::Event::EventType::KeyPressed){
                        if(event.key.code == sf::Keyboard::Key::Return){
                            show = true;
                            ok = false;
                        }else if(event.key.code == sf::Keyboard::Key::Escape){
                            show = false;
                            ok = false;
                        }
                    }

                    if(event.type == sf::Event::EventType::KeyPressed && event.key.code == sf::Keyboard::Key::BackSpace){
                            sf::Font font;
                            if (!font.loadFromFile("consolas.ttf"))
                            {
                                std::cout << "error no consolas" << std::endl;
                            }
                            text->setFont(font);
                            text->setPosition(sf::Vector2f(x, y));
                            text->setFillColor(sf::Color::Black);
                            sf:String bufferStr = "";
                            for ( int i = 0; i < entered.getSize()-1 ; i++){
                                bufferStr += entered[i];
                            }
                            entered = bufferStr;
                            text->setString(entered);
                            drawCoordinateSystem(ratio_, unit, centerX, centerY, sizeX, sizeY, window);
                            drawFunction(formula, ratio_, centerX, centerY, sizeX, sizeY, window);
                            window->draw(*field);
                            window->draw(*text);
                            window->display();
                    }
                    else if(event.type == sf::Event::EventType::TextEntered){
                        sf::Font font;
                        if (!font.loadFromFile("consolas.ttf"))
                        {
                            std::cout << "error no consolas" << std::endl;
                        }
                        text->setFont(font);
                        text->setPosition(sf::Vector2f(x, y));
                        text->setFillColor(sf::Color::Black);
                        entered += event.text.unicode;
                        text->setString(entered);
                        drawCoordinateSystem(ratio_, unit, centerX, centerY, sizeX, sizeY, window);
                        drawFunction(formula, ratio_, centerX, centerY, sizeX, sizeY, window);
                        window->draw(*field);
                        window->draw(*text);
                        window->display();
                    }
                }
            }
    }
    if(show){
            show = false;
            Formula* buffer = new Formula(entered.toAnsiString());
            entered = "";
            sf::Font font;
            if (!font.loadFromFile("consolas.ttf"))
            {
                std::cout << "error no consolas" << std::endl;
            }
            text->setString(entered);
            text->setFont(font);
            text->setPosition(sf::Vector2f(x, y));
            text->setFillColor(sf::Color::Black);
            window->draw(*field);
            window->draw(*text);
            return buffer;
    }
    entered = "";
    return formula;
}

sf::String textField::Getentered(sf::RenderWindow* window) {
    show = false;
    sf::String buffer = entered;
    entered = "";
    sf::Font font;
    if (!font.loadFromFile("consolas.ttf"))
    {
        std::cout << "error no consolas" << std::endl;
    }
    text->setString(entered);
    text->setFont(font);
    text->setPosition(sf::Vector2f(x, y));
    text->setFillColor(sf::Color::Black);
    window->draw(*field);
    window->draw(*text);
    return buffer;
    }
