#pragma once
#include <string>
#include <glad/glad.h>
#include "glm/glm.hpp"
#include "Renderer.h"

class Ball
{

public:
	Ball();
	Ball(std::string ball_colour, int height, int width,float gravity);
	

	virtual void Draw(Renderer& renderer);
	// moves the ball
	glm::vec2 Move(float dt, unsigned int window_width, unsigned int window_height);
	glm::vec2  resolveCollision(const int& weight);
	void  isStopped(glm::vec2 position, glm::vec2 velocity);
	

	int getBallWeight()const;
	int getBallPixels()const;
	float getRadius() const;


	glm::vec2 getPosition();
	glm::vec2 getVelocity();
	glm::vec2 getSize();

	bool getCollision();
	void setCollision(const bool& collision_state);

	
private:

	glm::vec2 position, size, velocity;
	glm::vec3 colour;
	float rotation;
	float  radius;
	float gravity;
	int weight;
	int pixels;
	bool stopped;
	bool collision;



};

