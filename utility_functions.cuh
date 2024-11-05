#pragma once
#include "cuda_runtime.h"
#include "device_launch_parameters.h" 
#include <stdio.h>
#include <stdlib.h>
#include "Ball.h"
#include<vector>

namespace Wrapper {
	void wrapper(Ball* balls,const int& N, const float& dt, const int& height, const int& width );
}