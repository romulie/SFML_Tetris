#ifndef SOUNDS_H_INCLUDED
#define SOUNDS_H_INCLUDED

#include <string>
#include <unordered_map>
#include<SFML/Audio.hpp>
#include "asset_manager.h"

class Sounds{
private:
    std::vector<sf::Sound> GameSounds;
public:
    Sounds();
    void play(int index);
    void stop(int index);
    void stopAll();
};

#endif // SOUNDS_H_INCLUDED
