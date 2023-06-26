# README
docker command line exe:

    docker run -it --rm --volume="/tmp/.X11-unix:/tmp/.X11-unix" --env="DISPLAY" joshuazimm/lorenz-attractor

lorenz compile in wsl with SDL installed:

    g++ -std=c++17 lorenz.cpp -o dc -lSDL2 -ldl

Overview:


This program is a simulation of a lorenz system of equations being drawn in 3D space, estimated by line segments of a set timestep drawn using a linked list structure. Each segment is assigned a color based on a HSV color gradient and it's given length in relation to the longest known segment. Linked list segments are deleted after a set amount of new segments are added, giving the program a disappearing trail.

Functionality:


Using WASD, you can navigate the open space by moving the camera, and if you get lost, you can use R to return to the starting position. If the screen becomes too full and you would like the drawing to start from scratch, you can press C to clear the current render. You can left click drag to spin around the lorenz structure and lastly use the scroll wheel to zoom in and out. The camera is preset to rotate around the center of the structure, so if using WASD, know the rotation point will change to not be at the center of the object, and that you can reset it by pressing R.



#