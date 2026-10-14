# Battle Tank game using SDL2

Old school project revived and updated for Linux using [Simple DirectMedia Layer 2](https://wiki.libsdl.org/SDL2/FrontPage).

![SDL logo](/docs/sdl_logo.png)

## Setup

Using OS Linux Ubuntu.

### Install build-essential

GCC, G++, GNU C library development libraries and header files, make, etc.

Run the `setup/install_essential.sh` script.

### Install SDL2

Run the `setup/install_sdl2.sh` script.

More info [here](https://www.libsdl.org/).

## Build and run

```sh
$ make       # Build application
$ make run   # Run application
$ make clean # Clean up
```

## Directories

- `/docs`    - Documentation
- `/include` - Code header files
- `/media`   - Media files for the game
- `/setup`   - Setup scripts for the Linux system
- `/src`     - Code source files

## Demo views

![Splashscreen](/docs/demo_1.png)

![Instructions](/docs/demo_2.png)

![Game play](/docs/demo_3.png)

Example logs

```
[LOG] ##################################################
[LOG] # BATTLE TANK - Game started
[LOG] ##################################################
[LOG] Window splash rendered
[LOG] Window instructions rendered
[LOG] Count down 3
[LOG] Count down 2
[LOG] Count down 1
[LOG] Rocket launched by player
[LOG] Rocket hit enemy 0
[LOG] Rocket launched by player
[LOG] Rocket hit enemy 0
[LOG] Level 1 reached
[LOG] Collision with enemy 0
[LOG] Collision with enemy 1
[LOG] Collision with enemy 2
[LOG] Collision with enemy 0
[LOG] Game over
[LOG] Replaying game...
[LOG] Count down 3
[LOG] Count down 2
[LOG] Count down 1
[LOG] Level 0 reached
[LOG] Rocket launched by player
[LOG] Rocket hit enemy 0
[LOG] Rocket launched by player
[LOG] Rocket hit enemy 1
[LOG] Level 1 reached
[LOG] Collision with enemy 0
[LOG] Rocket launched by player
[LOG] Game stopped by user
[LOG] Game ended with score: 104
```
