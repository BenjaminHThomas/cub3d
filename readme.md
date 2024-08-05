# CUB3D

A group project by Okan Koca and Ben Thomas.

Cub3d is a 3D doom-like walking simulator made in C, which uses the minilibx X11 API to render 3D environments from a user-supplied text file.

Okan handled the ray tracing and I handled the input parsing. My contributions are a lot less exciting than Okan's but regardless it was a fun little project.

## Getting started
```
make
./cub3d /Path/to/map.cub
```
Run make to compile the program and ./cub3d to launch the executable.
You have to provide a map file with the extension .cub.
We have some examples of this in the maps folder.
Within the .cub file you also have to provide textures for the walls. These can be found in the textures folder.

## Controls
- W/A/S/D controls the walking
- Arrow keys / clicking the left or right of the screen controls the rotation.
- Escape / 'x' button to close the program.

