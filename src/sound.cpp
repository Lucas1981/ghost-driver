#include "sound.h"
#include <iostream>

Sound::Sound() {
    initialize();
}

Sound::~Sound() {
    cleanup();
}

bool Sound::initialize() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    if (!loadSound(SoundType::START_ENGINE, "../assets/sounds/start-engine.wav")) return false;
    if (!loadSound(SoundType::CRASH, "../assets/sounds/crash.wav")) return false;
    if (!loadSound(SoundType::LOST, "../assets/sounds/lost.wav")) return false;
    if (!loadSound(SoundType::WON, "../assets/sounds/won.wav")) return false;

    return true;
}

bool Sound::loadSound(SoundType soundType, const std::string& filePath) {
    Mix_Chunk* sound = Mix_LoadWAV(filePath.c_str());
    if (sound == nullptr) {
        std::cerr << "Failed to load sound: " << filePath << " SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    sounds[soundType] = sound;
    return true;
}

void Sound::playSound(SoundType sound) {
    Mix_PlayChannel(-1, sounds[sound], 0);
}

void Sound::enqueueSound(SoundType sound) {
    soundQueue.push(sound);
}

void Sound::handleQueue() {
    while (!soundQueue.empty()) {
        playSound(soundQueue.front());
        soundQueue.pop();
    }
}

void Sound::cleanup() {
    for (auto& soundPair : sounds) {
        Mix_FreeChunk(soundPair.second);
    }
    sounds.clear();
    Mix_CloseAudio();
}
