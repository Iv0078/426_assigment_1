#pragma once
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Ball.h"
#include <vector>
#include <thread>

class Program
{
public:

    unsigned int width, height;
    std::vector<Ball*> balls;
    Renderer* Rend;
    std::vector<std::thread> threads;

    // constructor/destructor
    Program(unsigned int width, unsigned int height,std::vector<Ball*> balls);
    ~Program();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    bool CheckCollision(Ball& one, Ball& two);
    void Update(float dt);
    void Render();
    void resolveCollision(Ball* ball_one);
};