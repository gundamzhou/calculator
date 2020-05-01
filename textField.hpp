#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <SFML/Graphics.hpp>
#include "formula.hpp"

class textField
{
    public:
        textField();
        textField(int x, int y, int sizeX, int sizeY);

        void reveal(sf::RenderWindow* window);
        Formula* eventget(sf::Event event,sf::RenderWindow* window, Formula*formula,float ratio_, float unit, float centerX, float centerY, int sizeX, int sizeY);

        bool Getshow() { return show; }
        void Setshow(bool val) { show = val; }
        int getY(){return y;}
        sf::String Getentered(sf::RenderWindow* window);
        void Setentered(sf::String val) { entered = val; }

    protected:

    private:
        int x, y, width, length;
        sf::String entered;
        sf::RectangleShape *field;
        sf::Text* text;
        bool show;
};

#endif // TEXTFIELD_H
