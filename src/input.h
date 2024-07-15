#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <unordered_map>

class Input {
public:
    void beginNewFrame();
    void keyUpEvent(const SDL_Event& event);
    void keyDownEvent(const SDL_Event& event);
    bool wasKeyPressed(SDL_Scancode key);
    bool wasKeyReleased(SDL_Scancode key);
    bool isKeyHeld(SDL_Scancode key);

private:
    std::unordered_map<SDL_Scancode, bool> heldKeys;
    std::unordered_map<SDL_Scancode, bool> pressedKeys;
    std::unordered_map<SDL_Scancode, bool> releasedKeys;
};

#endif // INPUT_H
