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


