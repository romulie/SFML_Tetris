#include "../include/button.h"

Button::Button(const sf::Vector2f &location, const sf::Texture &normal, const sf::Texture &clicked){
    normalSpr.setTexture(normal);
    clickedSpr.setTexture(clicked);
    normalSpr.setPosition(location);
    clickedSpr.setPosition(location);
    currentSpr = &normalSpr;
};


bool Button::checkClick(const sf::Vector2i &mousePos){
    if (mousePos.x >= 0){
        if (static_cast<float>(mousePos.x) > currentSpr->getPosition().x &&
            static_cast<float>(mousePos.x) < currentSpr->getPosition().x + currentSpr->getGlobalBounds().width &&
            static_cast<float>(mousePos.y) > currentSpr->getPosition().y &&
            static_cast<float>(mousePos.y) < currentSpr->getPosition().y + currentSpr->getGlobalBounds().height){
                setState(!isClicked);
                return true;
        }
    }
    /// ???
    return false;
};


void Button::setState(bool clicked){
    isClicked = clicked;
    if (isClicked){
        currentSpr = &clickedSpr;
        return;
    }
    currentSpr = &normalSpr;
    return;
};


sf::Sprite* Button::getSprite(){
    return currentSpr;
};
