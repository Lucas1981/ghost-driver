#ifndef INPUT_H
#define INPUT_H

#include <SDL_events.h>    // for SDL_Event
#include <SDL_scancode.h>  // for SDL_Scancode
#include <map>             // for map

class Input {
public:
    void update();

    void keyUpEvent(const SDL_Event& event);
    void keyDownEvent(const SDL_Event& event);
    void processEvent(const SDL_Event& event);
    void pollEvents();

    bool wasKeyPressed(SDL_Scancode key);
    bool wasKeyReleased(SDL_Scancode key);
    bool isKeyHeld(SDL_Scancode key);

    bool shouldQuit();

private:
    void beginNewFrame();

    std::map<SDL_Scancode, bool> pressedKeys;
    std::map<SDL_Scancode, bool> releasedKeys;
    std::map<SDL_Scancode, bool> heldKeys;

    bool quitEvent = false;
};

#endif // INPUT_H
