#pragma once
#include <map>
#include <string>
#include <glad/glad.h>
#include "Shader.h"


class ResourceManager
{
public:
    // resource storage
    static std::map<std::string, Shader>    Shaders;
    // loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
    static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
    // retrieves a stored sader
    static Shader& GetShader(std::string name);
    // properly de-allocates all loaded resources
    static void  Clear();
private:
    // private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
    ResourceManager() { }
    // loads and generates a shader from file
    static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);

};

