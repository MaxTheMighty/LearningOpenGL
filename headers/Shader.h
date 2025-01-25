//
// Created by Maxwell Kozlov on 1/24/25.
//

#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>

class Shader {
    public:
        std::string filePath;
        unsigned int ID;
        int compileStatus;
        GLenum shaderType;
        std::string shaderText;
        Shader(const std::string& filePath, GLenum shaderType);
        void Source();
        void Compile();
        void PrintShaderInfoLog();
        static void readShaderToString(std::string *shaderText, const std::string &filepath);
};
#endif //SHADER_H
