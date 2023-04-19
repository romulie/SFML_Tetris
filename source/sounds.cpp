#include "../include/sounds.h"

Sounds::Sounds(){
    std::vector<std::string> sndFileNames{
        "sound/backgroundSnd.ogg",
        "sound/deadlineSnd.ogg",
        "sound/gameoverSnd.ogg",
        "sound/moveSnd.ogg",
        "sound/whistleSnd.ogg"};
    for (const auto &s : sndFileNames){
        sf::Sound currSnd;
        currSnd.setBuffer(AssetManager::GetSoundBuffer(s));
        GameSounds.push_back(currSnd);
    }
    GameSounds.front().setLoop(true);
};

void Sounds::play(int index){
    if (GameSounds[index].getStatus() == sf::SoundSource::Status::Stopped)
        GameSounds[index].play();
};

void Sounds::stop(int index){
    if (GameSounds[index].getStatus() == sf::SoundSource::Status::Playing)
        GameSounds[index].stop();
};

void Sounds::stopAll(){
    for (auto &snd : GameSounds){
        if (snd.getStatus() == sf::SoundSource::Status::Playing)
            snd.stop();
    }
};
