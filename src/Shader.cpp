//
// Created by Maxwell Kozlov on 1/24/25.
//
#include <iostream>
#include <fstream>
#include "../headers/Shader.h"

#include <glad/glad.h>

Shader::Shader(const std::string& filePath, GLenum shaderType) {
    this->filePath = filePath;
    this->shaderType = shaderType;
    readShaderToString(&this->shaderText,filePath);
    this->ID = glCreateShader(shaderType);
}


void Shader::readShaderToString(std::string *shaderText, const std::string& filepath){
    std::ifstream shaderFile(filepath);
    std::string line = "";
    if (shaderFile.is_open()) {
        while (std::getline(shaderFile,line)) {
            shaderText->append(line);
            shaderText->append("\n");
        }
    }
}

void Shader::Source() {
    const char* shaderTextBuffer = this->shaderText.c_str();
    glShaderSource(this->ID, 1, &shaderTextBuffer, nullptr);
}

void Shader::Compile() {
    glCompileShader(this->ID);
    glGetShaderiv(this->ID, GL_COMPILE_STATUS, &this->compileStatus);
    // return this->compileStatus;
}

void Shader::PrintShaderInfoLog() {
    char infoLog[512];
    glGetShaderInfoLog(this->ID, 512, nullptr, infoLog);
    std::cout << infoLog << std::endl;

}
