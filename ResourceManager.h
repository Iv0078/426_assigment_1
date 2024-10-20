#pragma once
#include <map>
#include <string>
#include <glad/glad.h>
#include "Shader.h"
#include "Texture.h"


class ResourceManager
{
public:

  
    ResourceManager();

    static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);  // loads (and generates) a shader program
    static Shader& GetShader(std::string name);  // retrieves a stored sader
    static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);  // loads and generates a shader from file

    static Texture loadTextureFromFile(const char* file, bool alpha);
    static Texture LoadTexture(const char* file, bool alpha, std::string name);   // loads (and generates) a texture from fil
    static Texture GetTexture(std::string name); // retrieves a stored texture 
    
    static void  Clear(); // properly de-allocates all loaded resources
   
private:
    static std::map<std::string, Shader>    Shaders;    // resource storage
    static std::map<std::string, Texture> Textures;



};

