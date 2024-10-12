#include "functions.h"
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>
#include "functions.h"
#include "Program.h"
#include "Ball.h"
#include "ResourceManager.h"






bool controlThread(std::vector<Ball*> ball_vector, const int& num_balls, 
    const unsigned int& SCREEN_WIDTH, const unsigned int& SCREEN_HEIGHT) {

    Program program(SCREEN_WIDTH, SCREEN_HEIGHT, ball_vector);


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // OpenGL configuration
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // initialize game
    program.Init();
  

    // delta time variables
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        // calculate delta time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

 
            
        // update state
        program.Update(deltaTime);
        // render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        program.Render();

        glfwSwapBuffers(window);
    }

    // delete loaded resources
    ResourceManager::Clear();

    glfwTerminate();

	return true;
}



