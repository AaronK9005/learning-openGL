#include <iostream>

#include <glad/gl.h>
#include <glfw/glfw3.h>

/**
 * @brief VBO = Vertex Buffer Object
 * It stores raw data (like vertex position)
 */

 /**
  * @brief VAO = Vertex Array Object
  * It stores how a VBO should be used (interpreted)
  */

  /**
   * @brief EBO = Element Buffer Object
   * Stores indexes to use for rendering
   */

    #pragma region |> window data and callbacks <|
    constexpr int startWidth = 800;
    constexpr int startHeight = 600;
    constexpr const char* windowName = "learning OpenGL";

    void framebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
    #pragma endregion

    #pragma region |> input <|
    void processInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

    }
    #pragma endregion

    #pragma region |> shader src <|
    const char* vertShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{ gl_Position = vec4(aPos.xyz, 1.0); }\0";

    const char* fragShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{  FragColor = vec4(1.0f, 0.05f, 0.2f, 1.0f); }\0";
    #pragma endregion

int main()
{
#pragma region |-> basically boilerplate <-|

    #pragma region |> glfw init <|
    if (glfwInit() != GLFW_TRUE)
    {
        std::cerr << "glfwInit() failed" << std::endl;
        return 1;
    }
    atexit(glfwTerminate);
    #pragma endregion

    #pragma region |> window creation <|
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow* window = glfwCreateWindow(startWidth, startHeight, windowName, nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        return 1;
    }
    glfwMakeContextCurrent(window);
    #pragma endregion

    #pragma region |> glad loading <|
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        std::cerr << "Failed to init GLAD" << std::endl;
        return 1;
    }
    #pragma endregion

    #pragma region |> setting window callbacks <|
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    #pragma endregion

    #pragma region |> setting gl stuff <|
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    #pragma endregion

    #pragma region |> maximum vertex attributes <|
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum number of vertex attributes supported: " << nrAttributes << std::endl;
    #pragma endregion
    
    #pragma region |> vertices <|
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    #pragma endregion

    #pragma region |> square vetices <|
    float sqVertices[] = {
         0.5f,  0.5f, 0.0f, // top right
        -0.5f,  0.5f, 0.0f, // top left
        -0.5f, -0.5f, 0.0f, // bottom left
         0.5f, -0.5f, 0.0f  // bottom right
    };

    unsigned sqIndices[] = {
        0, 1, 3,
        1, 2, 3
    };
    #pragma endregion

    #pragma region |> shader compilation <|
    unsigned vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    if (!vertexShader)
    {
        std::cerr << "ERROR::SHADER::VERTEX::CREATION" << std::endl;
        return 1;
    }
    glShaderSource(vertexShader, 1, &vertShaderSource, nullptr);
    glCompileShader(vertexShader);
    {
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, sizeof(infoLog) / sizeof(infoLog[0]), nullptr, infoLog);
            std::cerr << "ERROR::SHADER::VERTEX::COMPILATION::FAILED\n" << infoLog << std::endl;
            return 1;
        }
    }

    unsigned fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!fragmentShader)
    {
        std::cerr << "ERROR::SHADER::VERTEX::CREATION" << std::endl;
        return 1;
    }
    glShaderSource(fragmentShader, 1, &fragShaderSource, nullptr);
    glCompileShader(fragmentShader);
    {
        int success;
        char infoLog[512];
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, sizeof(infoLog) /  sizeof(infoLog[0]), nullptr, infoLog);
            std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION::FAILED\n" << infoLog << std::endl;
        }
    }
    #pragma endregion

    #pragma region |> shader program <|
    unsigned shaderProgram;
    shaderProgram = glCreateProgram();
    if (!shaderProgram)
    {
        std::cerr << "ERROR::SHADER::PROGRAM::CREATION" << std::endl;
        return 1;
    }
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    {
        int success;
        char infoLog[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shaderProgram, sizeof(infoLog) / sizeof(infoLog[0]), nullptr, infoLog);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING::FAILED\n" << infoLog << std::endl;
            return 1;
        }
    }

    glUseProgram(shaderProgram);
    #pragma endregion

    #pragma region |> shader deletion <|
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    vertexShader = 0;
    fragmentShader = 0;
    #pragma endregion

#pragma endregion

#pragma region |> triangle <|
/*
    // steps
    // 1. bind Vertex Array Object
    // 2. copy vertices array in a buffer for OpenGL to use
    // 3. set vertex attribute pointers

    // declare ids
    unsigned VBO, VAO;

    // generate on GPU
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    // bind and then copy data
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //* define how is should be used
    // rn i only have vertex 3d pos in vertices (current VBO)
    // if i had more, like lets say color, that would be at index 1
    // and i would also need vertAttribPtr to say what is it
    // and also enabelVertAttribArray for it to be used
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
*/
#pragma endregion

#pragma region |> square <|
    unsigned VAO, VBO;
    unsigned EBO; // Element Buffer Object

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sqVertices), sqVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sqIndices), sqIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

#pragma endregion

    #pragma |> region render loop <|
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

        // triangle
        // glDrawArrays(GL_TRIANGLES, 0, 3);

        // square
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    #pragma endregion

    return 0;
}