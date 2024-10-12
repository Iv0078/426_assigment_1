#include "Program.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Ball.h"
#include<GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <thread>
#include <mutex>

#include <iostream>

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
    ResourceManager::GetShader("ShaderFile").Use().SetInteger("", 0);
    ResourceManager::GetShader("ShaderFile").SetMatrix4("projection", projection);
    // set render-specific controls
    Rend = new Renderer(ResourceManager::GetShader("ShaderFile"));

}

void Program::Update(float dt)
{
    threads.clear(); // used to free up unused  space
    //std::cout << threads.size() << std::endl;
   
    for (Ball* ball : balls) {
        threads.push_back(std::thread(&Ball::Move,ball,dt, this->width, this->height));
    }
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }
    std::cout << threads.size() << std::endl;
    //threads.clear();
    for (Ball* id : balls) {
        threads.push_back(std::thread(&Program::resolveCollision,this,id)); 
    }
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }
    //std::cout << threads.size() << std::endl;
}


bool Program::CheckCollision(Ball& one, Ball& two) 
{
    // collision x-axis?
    bool collisionX = one.getPosition().x + one.getSize().x >= two.getPosition().x &&
        two.getPosition().x + two.getSize().x >= one.getPosition().x;
    // collision y-axis?
    bool collisionY = one.getPosition().y + one.getSize().y >= two.getPosition().y &&
        two.getPosition().y + two.getSize().y >= one.getPosition().y;
    // collision only if on both axes
    return collisionX && collisionY;
}

void Program::resolveCollision(Ball* ball_one){
  
    bool collision = false;
    for (Ball* ball_two : balls) {
        if (!(ball_one == ball_two)) {
            collision = this->CheckCollision(*ball_one, *ball_two);
        }
        
        if (collision) {
            ball_mutex.lock();
            (*ball_one).setCollision(true);
            (*ball_two).setCollision(true);
            ball_mutex.unlock();
            break;
        }
    }
    if ((*ball_one).getCollision()) {
        (*ball_one).resolveCollision();
    }

}



void Program::Render()
{
    for (Ball* ball : balls) {
        ball->Draw(*Rend);
    }

}
