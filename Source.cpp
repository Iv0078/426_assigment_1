#include <iostream>
#include <vector>
#include <thread>
#include "functions.h"
#include "Ball.h"





int main()
{
	//  Width of the screen
	const unsigned int SCREEN_WIDTH = 1200;
	//  height of the screen
	const unsigned int SCREEN_HEIGHT = 800;
	// gravity used
	const float GRAVITY = 0.25f;



	int num_balls = numOfBalls();

	std::vector<Ball*> balls_vector;
	for (int i = 0; i < num_balls; i++) {
		Ball* ball = new Ball(generateBallColour(), SCREEN_WIDTH, SCREEN_HEIGHT, GRAVITY);
		balls_vector.push_back(ball);
	}
	std::thread control_thread(controlThread, balls_vector, num_balls, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (control_thread.joinable()) { control_thread.join(); }
	std::cout << "Complete";


	return 0;
}
















