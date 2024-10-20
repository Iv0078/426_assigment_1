#pragma once
#include "glm/glm.hpp"
#include "Shader.h"


class Renderer
{
public:
    Renderer(Shader& shader);
    ~Renderer();

    void DrawRender(glm::vec2 position,
        glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
        glm::vec3 color = glm::vec3(1.0f));
private:
    Shader       shader;
    unsigned int quadVAO;

    void initRenderData();
};

