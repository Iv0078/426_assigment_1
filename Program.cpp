#include "Program.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Ball.h"
#include<GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include <tbb/tbb.h>

std::mutex ball_mutex;

Program::Program(unsigned int width, unsigned int height,std::vector<Ball*> balls)
    : width(width), height(height)
{
    for (Ball* i : balls) {
        this->balls.push_back(i);
    }

}

Program::~Program()
{}



void Program::Init()
{
    
    // load shaders
    ResourceManager::LoadShader("vShaderFile.vs", "fShaderFile.fs", nullptr, "ShaderFile");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width),
        static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("ShaderFile").Use().SetInteger("image", 0);
    ResourceManager::GetShader("ShaderFile").SetMatrix4("projection", projection);
    
    Rend = new Renderer(ResourceManager::GetShader("ShaderFile")); // set render-specific controls
    ResourceManager::LoadTexture("circle.png", true, "circle");

}

void Program::Update(float dt)
{
    // gives the maximum number of threads 
    //std::cout << oneapi::tbb::info::default_concurrency() << std::endl;
    tbb::parallel_for(tbb::blocked_range<int>(0, balls.size()),
        [&](tbb::blocked_range<int> r)
        {
            for (int i = r.begin(); i < r.end(); i++) {
                balls.at(i)->Move(dt, width, height);
                resolveCollision(balls.at(i));
            }
        });

}


bool Program::CheckCollision(Ball& one, Ball& two) 
{
    const float adjt{ 4.0f };
    // collision x-axis?
    bool collisionX = one.getPosition().x + one.getSize().x - adjt >= two.getPosition().x &&
        two.getPosition().x + two.getSize().x - adjt >= one.getPosition().x;
    // collision y-axis?
    bool collisionY = one.getPosition().y + one.getSize().y - adjt >= two.getPosition().y &&
        two.getPosition().y + two.getSize().y - adjt >= one.getPosition().y;
    // collision only if on both axes
    return collisionX && collisionY;
}

void Program::resolveCollision(Ball* ball_one){
  
    bool collision = false;
    int ballweight{ 5 };
    tbb::parallel_for(tbb::blocked_range<int>(0, balls.size()),
        [&](tbb::blocked_range<int> r)
        {
            for (Ball* ball_two : balls) {
                if (!(ball_one == ball_two)) {
                    collision = this->CheckCollision(*ball_one, *ball_two);
                }
                if (collision) {
                    ballweight = (*ball_two).getBallWeight();
                    (*ball_one).setCollision(true);
                    break;
                }
            }
        });
    if ((*ball_one).getCollision()) {
        (*ball_one).resolveCollision(ballweight);
    }
    
}



void Program::Render()
{
    for (Ball* ball : balls) {
        ball->Draw(*Rend);
    }

}

