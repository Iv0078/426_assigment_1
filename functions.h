#pragma once
#include <string>
#include <vector>
#include "Ball.h"
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <mutex>



// control thread
bool controlThread(std::vector<Ball*> ball_vector, const int& num_balls,
	const unsigned int& SCREEN_WIDTH, const unsigned int& SCREEN_HEIGHT);
// computation thread 
//bool computationThread(GLFWwindow* window);
// utility functions
int numOfBalls();
std::string generateBallColour();
glm::vec2 startingCoordiantes(const int& width,const int& height);
glm::vec2 startingVelocity();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);