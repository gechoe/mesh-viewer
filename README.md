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
![Video_1](https://github.com/gechoe/mesh-viewer/tree/main/videos/nextModel.mov) 
(https://user-images.githubusercontent.com/98035309/228309226-be780d20-aa25-4262-bf36-4a2ed069d759.mov)

2. previous model - p or P goes to the previous model:
![Video_2](https://user-images.githubusercontent.com/98035309/228310120-373e2d19-2a21-452a-8715-2251733ae77e.mov)

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
![Video_3](https://user-images.githubusercontent.com/98035309/228310332-d812e7d8-b48e-426c-b862-ef0cfbe23b54.mov)

4. camera movement - Left-click-drag orbits the camera around the model:
![Video_4](https://user-images.githubusercontent.com/98035309/228310430-acfbacce-b6f9-47cc-a138-f85401cbddbc.mov)

5. z or x - zooms in and out of the model
![Video_5](https://user-images.githubusercontent.com/98035309/228310508-1f361b28-6bd0-45fc-89e3-736b2546fc08.mov)

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
![Video_6](https://user-images.githubusercontent.com/98035309/228310655-1c89c157-9766-408d-b5cb-30dc77b01fc0.mov)

5. Color change shader - Gradients/Changes the color of the object:
![Video_7](https://user-images.githubusercontent.com/98035309/228310749-17aa4e58-e4a6-4abb-b9ea-db804233e8d1.mov)
