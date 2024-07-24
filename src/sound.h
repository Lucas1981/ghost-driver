#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL_mixer.h>
#include <string>
#include <unordered_map>
#include <queue>

enum class SoundType {
    START_ENGINE,
    CRASH,
    LOST,
    WON
};

class Sound {
public:
    Sound();
    ~Sound();

    bool initialize();
    void playSound(SoundType sound);
    void enqueueSound(SoundType sound);
    void handleQueue();
    void cleanup();

private:
    std::unordered_map<SoundType, Mix_Chunk*> sounds;
    std::queue<SoundType> soundQueue;

    bool loadSound(SoundType soundType, const std::string& filePath);
};

#endif // SOUND_H
