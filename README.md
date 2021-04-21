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

