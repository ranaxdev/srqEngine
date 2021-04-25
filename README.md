# srqEngine
A DOOM-style 3D Graphics rendering engine created with modern OpenGL and C++

## Libraries Used

- [GLFW](https://www.glfw.org/)

Used in windows context created and input callbacks
```cpp
// Window creation
GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "title");
glfwMakeContextCurrent(window);

// Callback mapping
// 1. Declare callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
// 2. Bind callback to GLFW
glfwSetKeyCallback(mainWindow, key_callback);
// 3. Define callback
void key_callback(...){}
```

- [GLAD](https://github.com/Dav1dde/glad)

Binds OpenGL function names
```cpp
// Have to load with GLFW's context reference and include the lib 
gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
```

- [GLM](https://github.com/g-truc/glm)

Perform operations on matrices and vectors and provide data structs for them
```cpp
// A 3D Vector struct
glm::vec3(1.0f, 1.0f, 1.0f);
// A 4x4 identity matrix
glm::mat4(1.0f);
// Translation transformation
glm::translate(glm::mat4(1.0f), glm::vec3(1.0f,1.0f,1.0f));
```

- [STB Image Loader](https://github.com/nothings/stb)

Used for importing textures in PNG format
```cpp
// Loading a texture object using its filepath, width, height and bits per pixel (BPP) vals
localBuffer = stbi_load(Texture::filepath, &(Texture::width), &(Texture::height), &(Texture::BPP), 4);
```


## Renderer API 

##### VBO/VAO

Typical binding of data in OpenGL requires manual setup of attribute pointers and data

```cpp
float data[] = {...}; // Array of vertices
unsigned int VAO, VBO;
glGenBuffers(1, &VBO); // Generate VBO with ID 1 and assign to obj
// VAO generated and bound, following layouts/configs will be associated with this now
glGenVertexArrays(1, &VAO);
glBindVertexArray(VAO);

glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind VBO to work on it
// Information on the data - how it is intended to be used
glBufferData(GL_ARRAY_BUFFER, sizeof(data), (const void*)data, GL_STATIC_DRAW);

// Define the layout - interpretation of vertices
// args: generic vertex attrib index, number of components per attrib (3 for 3 coordinates in this case),
// data type (floats), normalization (bool), stride in bytes, pointer to first component
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (const void*)0);
glEnableVertexAttribArray(0); // Enables layout to be bound to the VAO

```

All this manual calculation of strides and pointers is automated through the API calls
to the VAO/VBO object.
Equivalent code using the API:
```cpp
float data[] = {...};
va = VertexArray();
std::shared_ptr<VertexBuffer> vb = std::make_shared<VertexBuffer>(data);
vb->setlayout(
    {DataType::Float3, "pos"}
);
va.addVBO(vb);
// Other data types defined too e.g. mat4, mat3, float2
```
Now the draw call only needs a shader bound + this VertexArray object bound
```cpp
shader.bind();
va.bind();
glDrawArrays(...);
```
<hr/>

##### Shaders

In OpenGL steps to setup shaders include:
```cpp
// Defining shader src codes
const char* vertex_shader_src = " ... "
const char* fragment_shader_src = " ... "
// Initializing shaders
unsigned int vertex_shader, fragment_shader;
glCreateShader(...); // (for both)
// Compiling shaders
glShaderSource(...);
glCompileShader(...);
// Creating a shader program and linking it (omitted)
.
.
// Setting uniforms
glUniform1i(...); // Manual data type entry i.e. 1i, 3f
// Binding shader for use
glUseProgram(...);
```


In the renderer API, the shader class handles all this shader creation, compilation, linking, setting uniforms and manual binding. You should create a directory with files that contain GLSL code (this would be the equivalant of passing the shader src in form of a string but that is handled by the shader class). All you need to do to intialize, compile and link it is to provide the file paths to the GLSL code on intialization. Predefined data types for uniforms can be set and binding method is provided.
```cpp
// Equivalant with Shader class
// Setup shader
Shader s = Shader("path-to-vertex-shader", "path-to-fragment-shader");
// Set uniforms if you wish
s.setMat4("uniform-name", glm::mat4(1.0f));
// Bind it before drawing
s.bind();
```

<hr/>

##### Textures
Textures in OpenGL require quite a bit of setup as well
```cpp
// Initialize texture object
unsigned int ID;
glGenTextures(1, &ID);
// Set texture settings for interpolation, clamping etc.
glTexParameteri(...);
glTexParameteri(...);
.
.
// Process texture with a buffer of image data
int img_buffer[] = {...}
// Provide details on textures such as width, height color mode, the actual buffer 
glTexImage2D(GL_TEXTURE_2D ,..., img_buffer);
glGenerateMipMaps(GL_TEXTURE_2D);
// Bind texture and free buffer from memory
// Currently bound & active texture used in fragment shader
.
.
.
```

Simplified to a texture object that has predefined settings suitable for the models that are generated in srqEngine. No need to define an image buffer either, just provide a path to the texture with PNG format and you can bind it with a method call when you wish to use it
```cpp
// Entire texture setup
Texture t = Texture("path-to-texture.png");
// Bind before drawing if you wish to use it
// Make sure to bind appropriate fragment shader with it though
t.bind()
```

<hr/>

##### Models

The model class initializes a model and fully prepares it for rendering. It contains a model importer which parses Wavefront object files, you can initialize a textured model or a plain one. It handles the VBO/VAO setup internally after parsing the Wavefront file into vectors. Simply bind it before the draw call if you wish to render the model.

```cpp
// Initialize textured model
// ARGS: Path to wavefront object file, path to texture file, vec3 size in each axis, collidable, position
Model m1 = Model("model.obj", "texture.png", glm::vec3(1.0f), true, glm::vec3(0.0f));
// Initialize plain model
// Same arguments minus the texture path plus a color value in vec3 form for the fragment shader
Model m2 = Model("model.obj", ..., glm::vec3(1.0f))
// To use a model simply bind it before the draw call
m1.bind();
m2.bind();

```

<hr/>

##### Skybox

The skybox class is made from a cube model and requires 6 textures for each face of the cube in order to be rendered. When initializing a skybox object, you can pass the path to the directory that contains the face objects (make sure they are named right/left/top/bottom/front/back and in jpg format - both of these options can be changed within the class). It will use the stb image loader lirary to load in the textures, and bind them to the cube faces appropriately. In order to use the skybox, bind it once before the draw call.

```cpp
// Initialize skybox object 
// Args : Path to the directory that contains the 6 face textures
Skybox s = Skybox("path-to-directory");
// Bind before draw call to activate it, the depth and view matrix are set within the class itself so you dont have to modify anything
s.bind();
glDrawArrays(...);
```

<hr/>

##### Lighting

The engine provides shaders that simulate Phong-lighting for model objects. Define a plain model that you wish to use as a light source and place it in the scene. Use the lit-shader on the models, setting uniforms for the light source position and camera position (to get the specular highlights right). Here is how you would do it

```cpp
// First define and setup a lit model and a light source model
Model affected = Model(...);
Model light_source = Model(...);
light_source.bind();
affected.bind();

// Get a generic shader for the light source & Phong-lighting shadre for the lit model
Shader generic = Shader("path-to-generic-vertex-shader", "path-to-generic-fragment-shader");
Shader lit = Shader("path-to-lit-vertex-shader", "path-to-lit-fragment-shader");

// Bind lit-model shader and set uniforms
lit.setVec3("obj_color", affect.getColor());
lit.setVec3("light_color" ...); // And so on for light pos, view pos, intensity etc.

// Finally bind the shaders and models together in pairs and draw them (renderer handles drawing)
generic.bind();
Renderer::render(light_source);

lit.bind();
Renderer::render(affected);


```

<hr/>


##### Collision Models
Mark the collision flag to `true` on model initialization. It automatically generates the AABB and adds it to the collidable data structure to query for collisions. Ensure to update in the game loop.

```cpp
Model m = (..., true); // Last param is collidable flag
// Game loop - Update collisions
while(gameloop){
    // Pass camera position (the point which is checked for intersection with AABBs)
    Collision::updateCollisions(cam);
}
```

<hr/>

##### Particle Generator
The particle generator will create rectangular particles with random position values in the x/z plane and a large y-value (to simulate falling particles).

```cpp
// Create particle generator intance
ParticleGen p = ParticleGen();
// Create and bind shader for particles
Shader s = Shader("path-to-particle-vertex-shader", "path-to-particle-fragment-shader");
s.bind();
// Update particles in game loop
p.update(delta);
// Send particles to renderer to draw
Renderer::renderParticle(...);
```

<hr/>

## Camera

Camera class has a function to recalcuate and return view-projection matrix, the calculations are handled internally. Camera position can be accessed and updated through methods as well. Use the view-projection matrix in shader uniforms to transform them to camera space and view them in perspective.
```cpp
// View matrix, uses camera coordinate space vectors to calculate it
view = glm::lookAt(Camera::camPos, Camera::camPos + Camera::camFront, Camera::camUp);
// Perspective projection matrix, defining FOV, far/near planes and their width/heights
perspective = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
// View-projection
vp = perspective * view;

// To use it simply initialize the camera and get the VP (recalculation is automatic on every return call)
Camera cam = Camera();
glm::mat4 vp = cam.getVP();
```
