#include "utility_functions.cuh"


bool CheckCollision(Ball* one, Ball* two);
void resolveCollisions( int i, Ball* balls,  int* N);


void resolveCollision(Ball* a, int& weight);
void Move(Ball* a,float* dt,  int* window_width,  int* window_height);


__global__ void update_program_kernel(Ball* a,  int* N,  float* dt,  int* height,  int* width) {
    
    int i = threadIdx.x;
    if (i < *N) {
        printf("Integer: %d\n", i);
        Move(&(a[i]),dt, width, height);
        //resolveCollisions(i, a, N);
    }
    
    
        //printf("start\n" );
  
        
    
    
}

namespace Wrapper {
	void wrapper(Ball* balls, const int& N, const float& dt, const int& height, const  int& width )
	{

       /* for (int i{ 0 }; i < N; i++) {
            float x = (balls[i].position.x);
            printf("weidght %f\n",x );
        }*/

        //printf("start");
        /*for (int i{ 0 }; i < N; i++) {
            printf("weidght %i\n", balls[i].weight);
            
        }*/


        size_t sz = N * sizeof(Ball);
        

        int o_N = N;
        float o_dt = dt;
        int o_height = height;
        int o_width = width;



        
        //Ball** ball_inst;
        Ball* arr_d_a = new Ball[N];

        int* d_N;
        float* d_dt ;
        int* d_height;
        int* d_width;
        
        Ball* arr_f_a = new Ball[N];

        //cudaMalloc(&ball_inst, 2*sz);
        cudaMalloc((void**)&arr_d_a, sz);

        cudaMalloc((void**)&d_N, sizeof(int));
        cudaMalloc((void**)&d_dt, sizeof(float));
        cudaMalloc((void**)&d_height, sizeof(int));
        cudaMalloc((void**)&d_width, sizeof(int));


       
        cudaMemcpy(arr_d_a,&balls, sz, cudaMemcpyHostToDevice);
        cudaMemcpy(d_N, &o_N, sizeof(int), cudaMemcpyHostToDevice);
        cudaMemcpy(d_dt, &o_dt, sizeof(float), cudaMemcpyHostToDevice);
        cudaMemcpy(d_height, &o_height, sizeof(int), cudaMemcpyHostToDevice);
        cudaMemcpy(d_width, &o_width, sizeof(int), cudaMemcpyHostToDevice);


        update_program_kernel <<<1, N >> > (arr_d_a, d_N, d_dt, d_height, d_width);
        cudaDeviceSynchronize();

        cudaMemcpy(&balls, arr_d_a, sz, cudaMemcpyDeviceToHost);

        


		cudaFree(arr_d_a);

        cudaFree(d_N);
        cudaFree(d_dt);
        cudaFree(d_height);
        cudaFree(d_width);

   
        
	}
}



__host__ __device__  bool CheckCollision(Ball* one, Ball* two)
{
    const float adjt{ 4.0f };
    // collision x-axis?
    bool collisionX = (*one).position.x + (*one).size.x - adjt >= (*two).position.x &&
        (*two).position.x + (*two).size.x - adjt >= (*one).position.x;
    // collision y-axis?
    bool collisionY = (*one).position.y + (*one).size.y - adjt >= (*two).position.y &&
        (*two).position.y + (*two).size.y - adjt >= (*one).position.y;
    // collision only if on both axes
    return collisionX && collisionY;
}

__host__ __device__  void resolveCollisions( int i, Ball* balls,  int* N) {

    bool collision = false;
    int ballweight{ 5 };

    for (size_t j{ 0 }; j < *N; j++) {
        if (i != j) {
            collision = CheckCollision(&(balls[i]), (&balls[j]) );
        }
        if (collision) {
            ballweight = (balls[j]).weight;
            (balls[i]).collision = true;
            break;
        }
    }

    if ((balls[i]).getCollision()) {
        (balls[i]).resolveCollision(ballweight);
    }

}


__device__  void  resolveCollision(Ball * a,  int* weight) {
    if ((*a).collision) {
        float ratio = 1 - 2 * ((*a).weight - *weight) / 100;
        (*a).velocity.x = -ratio * (*a).velocity.x;
        (*a).velocity.y = -ratio * (*a).velocity.y;
        (*a).collision = false;
    }
    return;
}


__device__  void Move(Ball* a, float* dt,  int* window_width,  int* window_height) {
    /*std::cout << "x: " << position.x << std::endl;
    std::cout << "y: " << position.y << std::endl;
    std::cout << "x_vel: " << velocity.x << std::endl;
    std::cout << "yLvec: " << velocity.y << std::endl;
    velocity.x += 1;*/
  
        // move the ball
    //printf("vel: %f\n", (*a).velocity.x);
    (*a).position += (*a).velocity * (*dt);
    if ((*a).position.x <= 0.0f)
    {
        (*a).velocity.x = -(*a).velocity.x;
        (*a).position.x = 0.0f;
    }
    else if ((*a).position.x + (*a).size.x >= *window_width)
    {
        (*a).velocity.x = -(*a).velocity.x;
        (*a).position.x = *window_width - (*a).size.x;
    }
    if ((*a).position.y <= 0.0f)
    {
        (*a).velocity.y = -(*a).velocity.y;
        (*a).position.y = 0.0f;
    }
    else if ((*a).position.y + (*a).size.y >= *window_height)
    {
        (*a).velocity.y = -(*a).velocity.y;
        (*a).position.y = *window_height - (*a).size.y;
        /* (*a).velocity.y = 0;
            (*a).velocity.x = 0;
            (*a).stopped = true;*/
    }

    // gravity
    if (!((*a).position.y == *window_height && (*a).velocity.y == 0)) {
        (*a).velocity.y = (*a).velocity.y + (*a).gravity; // set to .25 for convinence
    }
    //printf("vel: %f\n", (*a).velocity.x);
    return;
}