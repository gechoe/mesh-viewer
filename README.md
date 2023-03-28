# mesh-viewer

Implements a simple PLY viewer

TODO: Add a representative image for your project here

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
mesh-viewer $ mkdir build
mesh-viewer $ cd build
mesh-viewer/build $ cmake ..
mesh-viewer/build $ start mesh-viewer.sln
```

Your solution file should contain two projects: `mesh-viewer` and `test-ply-mesh`.
To run from the git bash command shell, 

```
mesh-viewer/build $ ../bin/Debug/test-ply-mesh.exe
mesh-viewer/build $ ../bin/Debug/mesh-viewer.exe
```

*macOS*

Open terminal to the directory containing this repository.

```
mesh-viewer $ mkdir build
mesh-viewer $ cd build
mesh-viewer/build $ cmake ..
mesh-viewer/build $ make
```

To run each program from build, you would type

```
mesh-viewer/build $ ../bin/mesh-viewer
```

## Demo of basic features

TODO: Document the core features of your viewer (shaders + models)

Features:
1. next model - n or N goes to the next model:
https://user-images.githubusercontent.com/98035309/228308413-e56ba036-ab8a-49a2-87ba-9feb50231dd8.mov

2. previous model - p or P goes to the previous model:
![Video_2](videos/previousModel.mov)

3. go through shaders - s or S cycles through different shaders:
    normals
    per-vertex phong
    per-pixel phong
    toon
    jellofy
    glass
    vroom
    wiggle
    color-change
![Video_3](videos/allShaders.mov)

4. camera movement - Left-click-drag orbits the camera around the model:
![Video_4](videos/camMove.mov)

5. z or x - zooms in and out of the model
![Video_5](videos/zoom.mov)

## Unique features 

TODO: Show the unique features you made

Unique Features:
1. Toon shader - A cartoon shader:
![Image_1](videos/toon.png)

2. Jellofy shader - A transparent green shader:
![Image_2](videos/jello.png)

3. Glass shader - A clear shader:
![Image_3](videos/glass.png)

4. Vroom shader - Vertices animated to move mesh forwards:
![Video_6](videos/vroom.mov)

5. Color change shader - Gradients/Changes the color of the object:
![Video_7](videos/colorChange.mov)
