#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// float vertices[] = {
//     -0.5f,  -0.5f,  0.0f,
//      0.5f,  -0.5f,  0.0f,
//      0.0f,   0.5f,  0.0f
// };

// float vertices[] = {
//      0.5f,  0.5f, 0.0f,
//      0.5f, -0.5f, 0.0f,
//     -0.5f, -0.5f, 0.0f,
//     -0.5f,  0.5f, 0.0f
// };


float verticesA[] = {
    -1.0f, -1.0f, 0.0f,
    -0.5f, 0.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
};

float verticesB[] = {

    0.0f, -1.0f, 0.0f,
    0.5f, 0.0f, 0.0f,
    1.0f, -1.0, 0.0f
};


unsigned int indices[] = {
    0,1,2,3,4,5
};

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec3 aPosOut;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x,aPos.y,aPos.z, 1.0);\n"
"aPosOut = aPos;\n"
"}\0";


const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 aPosOut;"
"void main()\n"
"{\n"
// "FragColor = vec4(gl_PointCoord.x,gl_PointCoord.y,0.5,1.0f);\n"
"FragColor = vec4(aPosOut.x+0.5f,aPosOut.y+0.5f,aPosOut.z+0.5f,1.0f);\n"
// "FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
"}\0";
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow* window = glfwCreateWindow(800,600,"LearnOpenGL",NULL,NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0,0,800,600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //
    // BUFFERS!
    //


    // vertex array object, stores calls to VBO and EBO
    // so we dont have to keep binding and sending data
    unsigned int VAOa;
    glGenVertexArrays(1, &VAOa);
    glBindVertexArray(VAOa);


    // element buffer object, stores the indices of the vertexes in the VBO for drawing
    // unsigned int EBO;
    // glGenBuffers(1, &EBO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // stores the vertices used in drawing
    unsigned int VBOa; //this is the buffer ID that relates to the buffer behind the scenes
    glGenBuffers(1, &VBOa); //this creates that buffer and sets VBO to its ID
    glBindBuffer(GL_ARRAY_BUFFER, VBOa); // this binds the buffer's ID to GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesA), verticesA, GL_STATIC_DRAW); //copy the data
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0); //tell it how to interpet the data
    glEnableVertexAttribArray(0); //turn on vertex attribute array (?)


    unsigned int VAOb;
    glGenVertexArrays(1, &VAOb);
    glBindVertexArray(VAOb);

    unsigned int VBOb;
    glGenBuffers(1, &VBOb);
    glBindBuffer(GL_ARRAY_BUFFER,VBOb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesB),verticesB, GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //
    // SHADERS!
    //

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //
    // SHADER PROGRAM
    //

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAOa);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES,0,3);
        glBindVertexArray(VAOb);
        glDrawArrays(GL_TRIANGLES,0,3);
        // glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
        // glClearColor(0.2f,0.3f,0.3f,1.0);
        // glClear(GL_COLOR_BUFFER_BIT);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0,0,width,height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}