#include <iostream>
#include <vector>
#include "functions.h"
#include "Ball.h"
#include <tbb/tbb.h>
#include <thread>




int main()
{
	//  Width of the screen
	const unsigned int SCREEN_WIDTH = 1200;
	//  height of the screen
	const unsigned int SCREEN_HEIGHT = 800;
	// gravity used
	const float GRAVITY = 0.25f;
	


	int num_balls = numOfBalls(); // gets the number of ball from the user by calling numOfBalls

	std::vector<Ball*> balls_vector;
	// creates a ball and insers it in ball_vector
	tbb::mutex countMutex;
	tbb::parallel_for(tbb::blocked_range<int>(0, num_balls),
		[&](tbb::blocked_range<int> r)
		{
			for (int i = r.begin(); i < r.end(); i++) {
				Ball* ball = new Ball(generateBallColour(), SCREEN_WIDTH, SCREEN_HEIGHT, GRAVITY);
				countMutex.lock();
				balls_vector.push_back(ball);
				countMutex.unlock();
			}
		});

	std::thread control_thread(controlThread, balls_vector, num_balls, SCREEN_WIDTH, SCREEN_HEIGHT); // creates control thread
	if (control_thread.joinable()) { control_thread.join(); } // joins the thread once progrma is complete 
	std::cout << "Complete"; // termination message


	return 0;
}
















