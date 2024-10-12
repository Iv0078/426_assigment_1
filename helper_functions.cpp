#include "functions.h"
#include <iostream>
#include <stdlib.h>
#include <string>



int numOfBalls() {
	// gets number of balls inputed by the user
	bool numObtained = false;
	int numBalls{};

	do {
		std::cout << "Enter a number of balls between 3 and 10: ";
		std::cin >> numBalls;
		if (numBalls >= 3 && numBalls <= 10) {
			return numBalls;
		}
		else {
			std::cout << "Invalid input";
		}

	} while (!numObtained);
	return -1;
}


std::string generateBallColour() {
	// generates a random colour for the ball
	int randRange = rand() % 100000; // large range allows for more diversity since rand is very limited
	randRange = randRange % 10;// takes the last digit for simplicity
	//std::cout << randRange << std::endl;;
	if (randRange < 3) {
		return "red";
	}
	else if (randRange < 6)
	{
		return "green";
	}
	else {
		return "blue";
	}
}


glm::vec2 startingCoordiantes(const int& width, const int& height){
	// limits possible coordiantes to the size of the screen
	int x_coordiante{ (rand() % 100000)% width };
	int y_coordiante{ (rand() % 100000)% height };
	return glm::vec2(x_coordiante, y_coordiante);
}


glm::vec2 startingVelocity() {
	// limits possible velocities to 99
	int x_velocity{ (rand() % 100000) % 100 };
	int y_velocity{(rand() % 100000)%100}; 
	//std::cout << x_velocity << " " << y_velocity << std::endl;
	return glm::vec2(x_velocity, -y_velocity);
}



void framebuffer_size_callback(GLFWwindow* window, int width, int height) {

	glViewport(0, 0, width, height);// make sure the viewport matches the new window dimensions;
}

