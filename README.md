# ACEEngine
A simple 3d engine using glfw and opengl to introduce the ideas of objects, cameras and scenes.
This repo is just a simple example for the general shape of a project that uses ACE.

## Building
I personally like mingw gcc more than any other way of compiling c so that is what you'll have to use (maybe you can use something else).

You simply have to use this command (Present in build.bat):
``` 
gcc -o main.exe ACE/glad.c ACE/utils/utils.c ACE/shaders/shader.c ACE/acescene.c ACE/awsscool3dengine.c main.c -lm -lmingw32 -lglfw3dll -lopengl32
```
## Usage

You'll first have to initialize ACE using the `ACEInit(int, int);` function that takes two integers fo width and height.  
All of this is subject to change (although unlikely).

### Scenes

ACEScenes are just an object array and a default shader (For easier object creation).

#### Creation
The only current way to create a scene is using:  
`ACEMakeSceneEx(const char*, const char*, float, float, float, int);`  
It takes two paths to the default vertex and fragment shaders, 3 floats specifying the bgcolor of the scene and the maximum amount of objects (The Ex indicates that a more simplified version of this function is a TODO).

#### Enabling
ACE allows for more than one scene.  
You can switch between scenes using `ACEUseScene(ACEScene*);`

### Objects

Scenes up to now are just empty that's why we have to add objects.

An Object is in its core just a vertex array, a materiel and a model matrix (Which allows for scaling, translation and rotation).

#### Creation
There are lots of ways to create objects.
You can use:  
`ACEMakeObjectEx(float*, int, int*, int, ACEMateriel, Mat4);`

It takes:
1. A float buffer containing vertex information.  
2. The size of said buffer in floats.
3. A format (Discussed later).
4. The format length in ints.
5. A materiel (Also discussed later).
6. A model matrix.

##### Formats

Just a way to further increase the usability of the object creation code.  
A format is just an array of ints that specify the number of floats per vertex attribute.  
Eg.
* [3] would mean that a vertex only has a vec3 attribute.  
* [3, 3, 2] is the default used in ACE, it specifies the position (vec3), the normal (vec3) and the texture coordinates (vec2).  

##### Materiels

An object must ofcourse have a materiel so we can be able to draw it.  
An ACEMateriel contains a default color, a textures array and a shader.

For and example for ace shaders you can check the `defvert.glsl` and `deffrag.glsl` in `ACE/shaders/`.

The simplest way of creating a materiel is to use `ACEMakeColorMateriel(float, float, float, ACEScene*);`.  
It takes an rgb color value and gives back an ACEMateriel using the specified scene's default shader.

Textures are not currently implemented.

#### Back To Creation

All this complexity can be dodged by using one of the other object creation functions.

* `ACEMakeSimpleObject(float*, int, ACEScene*);` It just takes the float buffer and its length and a scene to use its default shader.
* `ACEMakePrimitive(ACEPrimitive, ACEScene*);` It is pretty self-explanatory. For now the primitives are:
    * `ACETRIG` A simple triange.
    * `ACECUBE` A simple cube.

#### Enabling

You can add an object to a scene using `ACEAddObject(ACEObject*, ACEScene*);`.\
You can render an object manually by using `ACERenderObject(ACEObject*);` even if it is not in the current scene.

### Cameras

An ACECamera just has a position, direction, and a projection matrix (For perspective and orthogonal support).

#### Creation

You can create a camera using `ACEMakeCamera(Vec3, Vec3, Mat4);`.\
It takes the pos, dir, and projection.

#### Enabling

ACE also allows for multiple cameras.  
To use a certain camera just specify it to the `ACEUseCamera(ACECamera*);` function.

### Rendering Loop

To check if the ACE app should close you must use `ACEShouldClose();` which returns true if the window should close.  
You can also render the current scene by using `ACERender();`.\
ACE supports basic input via the funtions:
* `ACEMousePos();` The current mouse position, you can lock and hide the mouse using `ACELockMouse();`.
* `ACEIsKeyDown(GLFW_KEY)` Returns true if the specified key is down, keys are specified with the glfw enums.

### Quiting

You can use `ACEQuit();` to terminate ACE. But, you'll still have to clean up all the cameras, objects and scenes you created.
