#include "input.h"

void Input::update() {
    beginNewFrame();
    pollEvents();
}

void Input::beginNewFrame() {
    this->pressedKeys.clear();
    this->releasedKeys.clear();
    this->quitEvent = false;
}

void Input::keyUpEvent(const SDL_Event& event) {
    this->releasedKeys[event.key.keysym.scancode] = true;
    this->heldKeys[event.key.keysym.scancode] = false;
}

void Input::keyDownEvent(const SDL_Event& event) {
    this->pressedKeys[event.key.keysym.scancode] = true;
    this->heldKeys[event.key.keysym.scancode] = true;
}

bool Input::wasKeyPressed(SDL_Scancode key) {
    return this->pressedKeys[key];
}

bool Input::wasKeyReleased(SDL_Scancode key) {
    return this->releasedKeys[key];
}

bool Input::isKeyHeld(SDL_Scancode key) {
    return this->heldKeys[key];
}

bool Input::shouldQuit() {
    return quitEvent || this->heldKeys[SDL_SCANCODE_ESCAPE];
}

void Input::processEvent(const SDL_Event& event) {
    switch (event.type) {
        case SDL_QUIT:
            quitEvent = true;
            break;
        case SDL_KEYDOWN:
            keyDownEvent(event);
            break;
        case SDL_KEYUP:
            keyUpEvent(event);
            break;
        default:
            break;
    }
}

void Input::pollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        processEvent(event);
    }
}
