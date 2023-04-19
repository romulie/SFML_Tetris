#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>

class Button{
public:
    Button(const sf::Vector2f &location, const sf::Texture &normal, const sf::Texture &clicked);
    bool checkClick(const sf::Vector2i &mousePos = sf::Vector2i(-1, -1));
    sf::Sprite* getSprite();
private:
    sf::Sprite normalSpr;
    sf::Sprite clickedSpr;
    sf::Sprite* currentSpr;
    bool isClicked = false;
    void setState(bool clicked);
};

#endif // BUTTON_H_INCLUDED
