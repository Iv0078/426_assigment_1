#include "Ball.h"
#include <stdlib.h>
#include "functions.h"
#include <iostream>

glm::vec2 position, size, velocity;
glm::vec3 colour;
float rotation;
int weight{};
int pixels{};
float   radius;
bool    stopped;


Ball::Ball()
	:position{ 0.0f,0.0f },size{ 1.0f,1.0f },velocity{ 0.0f,0.0f },colour{ 1.0f,0.0f,0.0f },
	rotation{ 0.0f }, weight{ 5 }, pixels{ 50 }, radius{ 0.0f }, gravity{0.25f}, stopped{ true }, collision{ false }
{

}

Ball::Ball( std::string ball_colour,int width,int height,float gravity):
	rotation{ 0.0f }, gravity{gravity}, stopped{ false }, collision{ false }
{
	
	if (ball_colour == "blue") {
		weight = 15;
		pixels = 150;
		colour = glm::vec3(0.0f, 0.0f, 1.0f);
		
	}
	else if (ball_colour == "green") {
		weight = 10;
		pixels = 100;
		colour = glm::vec3(0.0f, 1.0f, 0.0f);
	}
	else {
		weight = 5;
		pixels = 50;
		colour = glm::vec3(1.0f, 0.0f, 0.0f);
	}
	radius = weight;
	size = glm::vec2(radius *5.0f, radius*5.0f);
	position = startingCoordiantes(width, height);
	velocity = startingVelocity();

}


void Ball::Draw(Renderer& renderer) {
	renderer.DrawRender( this->position, this->size, this->rotation, this->colour);
}

 glm::vec2 Ball::Move(float dt, unsigned int window_width,unsigned int window_height) {
	 //std::cout << position.x << std::endl;
	 if (!this->stopped)
	 {
		 // move the ball
		 this->position += this->velocity * dt;
		 if (this->position.x <= 0.0f)
		 {
			 this->velocity.x = -this->velocity.x;
			 this->position.x = 0.0f;
		 }
		 else if (this->position.x + this->size.x >= window_width)
		 {
			 this->velocity.x = -this->velocity.x;
			 this->position.x = window_width - this->size.x;
		 }
		 if (this->position.y <= 0.0f)
		 {
			 this->velocity.y = -this->velocity.y;
			 this->position.y = 0.0f;
		 }
		 else if (this->position.y + this->size.y >= window_height)
		 {
			 this->velocity.y = -this->velocity.y;
			 this->position.y = window_height - this->size.y;
			/* this->velocity.y = 0;
			 this->velocity.x = 0;
			 this->stopped = true;*/
		 }
			
		 // gravity
		 if (!(this->position.y == window_height && this->velocity.y == 0)) {
			 this->velocity.y = this->velocity.y + this->gravity; // set to .25 for convinence
		 }
	 }
	 return this->position;
 }

 glm::vec2  Ball::resolveCollision() {
	 //std::cout << "collision" << std::endl;
	 if (collision) {
		 this->velocity.y = -this->velocity.y;
		 this->velocity.x = -this->velocity.x;
		 collision = false;
	 }

	 return this->position;
 }

// resets the ball to original state with given position and velocity
 void  Ball::isStopped(glm::vec2 position, glm::vec2 velocity) {
	 
 }

 int Ball::getBallWeight()const { return weight; }
 int Ball::getBallPixels()const { return pixels; }

 glm::vec2 Ball::getPosition() { return position;}
 glm::vec2 Ball::getVelocity() { return velocity; }
 glm::vec2 Ball::getSize() { return size; }


 bool Ball::getCollision() { return collision; }
 void Ball::setCollision(const bool& collision_state) {
	 this->collision = collision_state;
 }
