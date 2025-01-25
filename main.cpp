#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <fstream>
#include "headers/Shader.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
int initGlfw(GLFWwindow** window);


float verticesA[] = {
    -1.0f, 1.0f, 0.0f, //top left
    -1.0f, -1.0f, 0.0f,  //bottom left
    1.0f, 1.0f, 0.0f,  //top right
};

float verticesB[] = {

    1.0f, 1.0f, 0.0f, //top right
    1.0f, -1.0f, 0.0f, //bottom right
    -1.0f, -1.0, 0.0f //bottom left
};


unsigned int indices[] = {
    0,1,2,3,4,5
};


const std::string vertexShaderPath = "/Users/maxwell/Desktop/Spring 2025/COMP565/Enviornment Setup/shaders/vertex_shader.glsl";
const std::string fragmentShaderPath = "/Users/maxwell/Desktop/Spring 2025/COMP565/Enviornment Setup/shaders/fragment_shader.glsl";
int main(){

    GLFWwindow* window = nullptr;
    if (initGlfw(&window) == -1) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


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

    Shader vertexShader(vertexShaderPath,GL_VERTEX_SHADER);
    vertexShader.Source();
    vertexShader.Compile();
    vertexShader.PrintShaderInfoLog();

    Shader fragmentShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
    fragmentShader.Source();
    fragmentShader.Compile();
    fragmentShader.PrintShaderInfoLog();

    //
    // SHADER PROGRAM
    //

    unsigned int shaderProgram;
    int success;
    char infoLog[512];
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader.ID);
    glAttachShader(shaderProgram, fragmentShader.ID);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // uniforms
    unsigned int uniformLocation = glGetUniformLocation(shaderProgram, "time");
    float color_offset = 0.0f;
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glUseProgram(shaderProgram);
        glUniform1f(uniformLocation, color_offset);
        glBindVertexArray(VAOa);
        glDrawArrays(GL_TRIANGLES,0,3);

        glBindVertexArray(VAOb);
        glDrawArrays(GL_TRIANGLES,0,3);
        color_offset+=0.01f;
        glfwSwapBuffers(window);
        glfwPollEvents();
        glClearColor(0.2f,0.3f,0.3f,1.0);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    glDeleteShader(vertexShader.ID);
    glDeleteShader(fragmentShader.ID);
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

int initGlfw(GLFWwindow** window) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    *window = glfwCreateWindow(800,600,"LearnOpenGL",NULL,NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(*window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    glViewport(0,0,800,600);
    glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);
    return 1;
}

// void readShaderToString(std::string *shaderText, const std::string& filepath){
//     std::ifstream shaderFile(filepath);
//     std::string line = "";
//     if (shaderFile.is_open()) {
//         while (std::getline(shaderFile,line)) {
//             shaderText->append(line);
//             shaderText->append("\n");
//         }
//     }
// }