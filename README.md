# Ghost Driver

<img width="641" alt="Screenshot 2024-07-24 at 21 46 54" src="https://github.com/user-attachments/assets/1d2fb855-d397-4d39-a997-d8d934e14bd4">

I had an itch to make something again. I started out in Rust. But Rust kinda sucks so far, imho. So I went with C++. I got a car and opponent cars going. I then figured oh wait, that means he's driving against the grain, so in Dutch that's a ghost driver. Great title!

My challenge was to have a scrolling background. The objective will be pretty simple though: limited time to make it to the finish, every time you crash into a car it will slow you down. Crash too many times and you won't make it on time.

## Architecture

So, the main.cpp file is just the entry point that kicks everything into gear. The main files that keep the game going are `game-loop.cpp`, `state.cpp` and `play.cpp`. The game-loop module just makes sure the loop is kept going, takes a look at the current state of the game with a big switch and then delegates to the appropriate handler for the state. At the end of the loop it always presents what is rendered onto the screen and plays the whole sound queue.

The handlers take care of delegating to other functions and also manipulate the state when it's time, for instance from the crashed state back to the running state. The `play.cpp` module is where most of the action takes place, where we check if we should issue a new car, by how much all the cars should move, if two cars collide, etc.

The whole thing is build with SDL2 as an engine for input, graphics, sound and collision detection. 

## Todo

- [x] Add collision
- [x] Add title screen
- [x] Add UI
- [x] Expand game states:
    - [x] TITLE
    - [x] READY
    - [x] RUNNING
    - [x] CRASHED
    - [x] LOST
    - [x] WON
- [x] Add timer
- [x] Add sounds
